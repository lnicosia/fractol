/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 11:16:58 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 13:24:20 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			init_koch(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = FLAT;
	fract->color_inside = WHITE;
	fract->color_inside_mode = FLAT;
	fract->name = "Koch snowflake";
	fract->zoom = 400;
	fract->inv_zoom = 1 / fract->zoom;
	fract->iter_max = 0;
	fract->center.x = 512;
	fract->center.y = 512;
	fract->zoom = 0.5;
	fract->move.x = 0;
	fract->move.y = 0;
	fract->incr = 1;
	fract->maj_incr = 1;
	return (0);
}

static void	reset_image(t_fract *fract)
{
	int	i;

	i = -1;
	while (++i < 1048576)
		fract->window.img.str[i] = 0;
}

void		calc_koch(t_coord2 p1, t_coord2 p2, t_fract *fract, int iter)
{
	t_coord2	p3;
	t_coord2	p4;
	t_coord2	p5;

	if (iter > 0)
	{
		p3 = new_coord2((2 * p1.x + p2.x) * 0.3333, (2 * p1.y + p2.y) * 0.3333);
		p5 = new_coord2((2 * p2.x + p1.x) * 0.3333, (2 * p2.y + p1.y) * 0.3333);
		p4 = new_coord2(p3.x + (p5.x - p3.x) * 0.5
				+ (p5.y - p3.y) * SIN_PI_3,
				p3.y - (p5.x - p3.x) * SIN_PI_3 + (p5.y - p3.y) * 0.5);
		calc_koch(p1, p3, fract, iter - 1);
		calc_koch(p3, p4, fract, iter - 1);
		calc_koch(p4, p5, fract, iter - 1);
		calc_koch(p5, p2, fract, iter - 1);
	}
	else
	{
		if (fract->color_mode == COS)
			plot_line_aa(p1, p2, fract, 0xFFFFFF);
		else
			plot_line(p1, p2, fract, 0xFFFFFF);
	}
}

void		koch(t_fract *fract)
{
	t_coord2	p1;
	t_coord2	p2;
	t_coord2	p3;

	p1 = new_coord2(fract->center.x - (200 + fract->move.x) * fract->zoom,
			fract->center.y - (200 + fract->move.y) * fract->zoom);
	p2 = new_coord2(fract->center.x + (200 - fract->move.x) * fract->zoom,
			fract->center.y - (200 + fract->move.y) * fract->zoom);
	p3 = new_coord2(fract->center.x - fract->move.x * fract->zoom,
			fract->center.y + (200 - fract->move.y) * fract->zoom);
	reset_image(fract);
	calc_koch(p1, p2, fract, fract->iter_max);
	calc_koch(p2, p3, fract, fract->iter_max);
	calc_koch(p3, p1, fract, fract->iter_max);
	put_fractal_to_window(fract);
}
