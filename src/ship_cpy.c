/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:23:51 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 10:49:54 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			init_ship(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = FLAT;
	fract->color_inside = WHITE;
	fract->color_inside_mode = FLAT;
	fract->name = "Burning ship";
	fract->zoom = 10000;
	fract->inv_zoom = 1 / fract->zoom;
	fract->iter_max = 40;
	fract->min.x = -1.812;
	fract->min.y = -0.085;
	fract->move.x = 0;
	fract->move.y = 0;
	fract->incr = 8;
	fract->maj_incr = 40;
	return (0);
}

static void	iterate_z(t_complex z, t_complex c, t_coord2 pos, t_fract *fract)
{
	double	xtemp;

	while (z.r * z.r + z.i * z.i < 4
			&& fract->iter < fract->iter_max)
	{
		xtemp = z.r * z.r - z.i * z.i;
		z.i = fabs(2 * z.r * z.i + c.i);
		z.r = fabs(xtemp + c.r);
		fract->iter++;
	}
	if (fract->iter == fract->iter_max)
		color_inside(pos.x, pos.y, fract);
	else
		color(pos.x, pos.y, fract);
}

static void	*calc_ship(void *param)
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
			iterate_z(c, z, pos, fract);
			pos.x++;
		}
		pos.y++;
	}
	return (NULL);
}

void		ship(t_fract *fract)
{
	pthread_t	thread[8];
	t_fract		ship[8];
	int			i;

	i = 0;
	while (i < 8)
	{
		ft_memcpy(&ship[i], fract, sizeof(t_fract));
		ship[i].end = 1024 / 8 * (i + 1);
		ship[i].start = 1024 / 8 * i;
		pthread_create(&thread[i], NULL, calc_ship, &ship[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	put_fractal_to_window(fract);
}
