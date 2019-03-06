/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:28:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/06 16:14:15 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>
#include <stdio.h>

void	init_ship(t_fract *fract)
{
	fract->iter_max = 64;
	fract->max.x = 2.0;
	fract->max.y = 2.0;
	fract->min.x = 2.0;
	fract->min.y = 2.0;
	fract->center.x = 1.86;
	fract->center.y = 0.1;
}

void	ship(t_fract *fract)
{
	int			x;
	int			y;
	double		xtemp;
	t_fcoord2	z;
	t_fcoord2	c;

	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1080)
		{
			c.x = ((0.2 * x) / 1920.0 - 1.86) / fract->zoom.x + fract->move.x / 10;
			c.y = ((0.15 * y) / 1080.0 - 0.1) / fract->zoom.x + fract->move.y / 10;
			z.x = 0;
			z.y = 0;
			fract->iter = 0;
			while (z.x * z.x + z.y * z.y < 4
					&& fract->iter < fract->iter_max)
			{
				xtemp = z.x * z.x - z.y * z.y;
				z.y = fabs(2 * z.x * z.y + c.y);
				z.x = fabs(xtemp + c.x);
				fract->iter++;
			}
			if (fract->iter == fract->iter_max)
				fract->window.img.str[x + 1920 * y] = 0;
			else
			{
				fract->window.img.str[x + 1920 * y] = 0xFFFFFF * (int)(256 * fract->iter / fract->iter_max);
			}
			x++;
		}
		y++;
	}
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr, fract->window.img_ptr, 0, 0);
}
