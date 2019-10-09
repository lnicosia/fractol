/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:29:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 11:48:07 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			init_tricorn(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = FLAT;
	fract->color_inside = WHITE;
	fract->color_inside_mode = FLAT;
	fract->name = "Tricorn";
	fract->zoom = 250;
	fract->inv_zoom = 1 / fract->zoom;
	fract->iter_max = 50;
	fract->min.x = -2.25;
	fract->min.y = -2;
	fract->move.x = 0;
	fract->move.y = 0;
	fract->pow = 2;
	fract->incr = 8;
	fract->maj_incr = 40;
	return (0);
}

static void	iterate_z(t_complex z, t_complex c, t_coord2 pos, t_fract *fract)
{
	while (z.r * z.r + z.i * z.i < 4
			&& fract->iter < fract->iter_max)
	{
		z = ft_cadd(ft_cpow(ft_cconj(z), fract->pow),
				c);
		fract->iter++;
	}
	if (fract->iter == fract->iter_max)
		color_inside(pos.x, pos.y, fract);
	else
		color(pos.x, pos.y, fract);
}

static void	*calc_tricorn(void *param)
{
	t_coord2	pos;
	t_complex	z;
	t_complex	c;
	t_fract		*fract;

	fract = (t_fract*)param;
	pos.y = fract->start;
	while (pos.y < fract->end)
	{
		pos.x = 0;
		while (pos.x < 1024)
		{
			c.r = pos.x * fract->inv_zoom + fract->min.x
				+ fract->move.x;
			c.i = pos.y * fract->inv_zoom + fract->min.y
				+ fract->move.y;
			z = new_complex(0, 0);
			fract->iter = 0;
			iterate_z(z, c, pos, fract);
			pos.x++;
		}
		pos.y++;
	}
	return (NULL);
}

void		tricorn(t_fract *fract)
{
	pthread_t	thread[8];
	t_fract		tricorn[8];
	int			i;
	char		*str;

	i = 0;
	while (i < 8)
	{
		ft_memcpy(&tricorn[i], fract, sizeof(t_fract));
		tricorn[i].end = 1024 / 8 * (i + 1);
		tricorn[i].start = 1024 / 8 * i;
		pthread_create(&thread[i], NULL, calc_tricorn, &tricorn[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	put_fractal_to_window(fract);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 160, 10, 0xFFFFFF,
			"| Power = ");
	str = ft_sitoa(fract->pow);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 260, 10, 0xFFFFFF,
			str);
}
