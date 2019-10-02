/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:29:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/02 18:53:30 by lnicosia         ###   ########.fr       */
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
	fract->zoom = 400;
	fract->inv_zoom = 1 / fract->zoom;
	fract->iter_max = 50;
	fract->min.x = -2.7;
	fract->min.y = -1.35;
	fract->move.x = 0;
	fract->move.y = 0;
	fract->pow = 2;
	return (0);
}

static void	*calc_tricorn(void *param)
{
	int			x;
	int			y;
	//double		xtemp;
	t_complex	z;
	t_complex	c;
	t_fract		*fract;

	fract = (t_fract*)param;
	y = fract->start;
	while (y < fract->end)
	{
		x = 0;
		while (x < 1920)
		{
			c.r = x * fract->inv_zoom + fract->min.x + fract->move.x;
			c.i = y * fract->inv_zoom + fract->min.y + fract->move.y;
			z.r = 0;
			z.i = 0;
			fract->iter = 0;
			while (z.r * z.r + z.i * z.i < 4
					&& fract->iter < fract->iter_max)
			{
				/*xtemp = z.r * z.r - z.i * z.i;
				z.i = -2 * z.r * z.i + c.i;
				z.r = xtemp + c.r;*/
				z = ft_cadd(ft_cpow(ft_cconj(z), fract->pow), c);
				fract->iter++;
			}
			if (fract->iter == fract->iter_max)
				color_inside(x, y, fract);
			else
				color(x, y, fract);
			x++;
		}
		y++;
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
		tricorn[i].end = 1080 / 8 * (i + 1);
		tricorn[i].start = 1080 / 8 * i;
		pthread_create(&thread[i], NULL, calc_tricorn, &tricorn[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 10, 0xFFFFFF, "Iterations: ");
	str = ft_sitoa(fract->iter_max);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 10, 0xFFFFFF, str);
	print_color_data(fract);
}
