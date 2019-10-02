/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 11:16:58 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/02 12:12:28 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

int		   init_koch(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = FLAT;
	fract->color_inside = WHITE;
	fract->color_inside_mode = FLAT;
	fract->name = "Koch snowflake";
	fract->zoom = 400;
	fract->iter_max = 0;
	fract->zoom = 0.5;
	fract->move.x = 0;
	fract->move.y = 0;
	return (0);
}

static void	reset_image(t_fract *fract)
{
	int	x;
	int	y;

	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			fract->window.img.str[x + y * 1920] = 0;
			x++;
		}
		y++;
	}
}

void    calc_koch(t_coord2 p1,t_coord2 p2, t_fract *fract, int iter)
{
	t_coord2    p3;
	t_coord2    p4;
	t_coord2    p5;
	double		angle;

	angle = M_PI / 3;
	if (iter > 0)
	{
		p3 = new_coord2((2 * p1.x + p2.x) / 3, (2 * p1.y + p2.y) / 3);
		p5 = new_coord2((2 * p2.x + p1.x) / 3, (2 * p2.y + p1.y) / 3);
		p4 = new_coord2(p3.x + (p5.x - p3.x) * 0.5
				+ (p5.y - p3.y) * sin(angle),
				p3.y - (p5.x - p3.x) * sin(angle) + (p5.y - p3.y) * 0.5);
		calc_koch(p1, p3, fract, iter - 1);
		calc_koch(p3, p4, fract, iter - 1);
		calc_koch(p4, p5, fract, iter - 1);
		calc_koch(p5, p2, fract, iter - 1);
	}
	else
		plot_line(p1, p2, fract, 0xFFFFFF);
}

void    koch(t_fract *fract)
{
	t_coord2    p1;
	t_coord2    p2;
	t_coord2    p3;
	char		*str;

	p1 = new_coord2((960 - (415 + fract->move.x) * fract->zoom),
			(650 - (360 + fract->move.y) * fract->zoom));
	p2 = new_coord2((960 + (415 - fract->move.x) * fract->zoom),
			(650 - (360 + fract->move.y) * fract->zoom));
	p3 = new_coord2(960 - fract->move.x * fract->zoom,
			(650 + (360 - fract->move.y) * fract->zoom));
	reset_image(fract);
	calc_koch(p1, p2, fract, fract->iter_max);
	calc_koch(p2, p3, fract, fract->iter_max);
	calc_koch(p3, p1, fract, fract->iter_max);
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 10, 0xFFFFFF, "Iterations: ");
	str = ft_itoa(fract->iter_max);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 10, 0xFFFFFF, str);
	free(str);
}
