/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:29:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/06 16:10:57 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	init_mandelbrot(t_fract *fract)
{
	fract->iter_max = 64;
	fract->max.x = 2.0;
	fract->max.y = 1.2;
	fract->min.x = -2.0;
	fract->min.y = -1.2;
	fract->center.x = 2.5;
	fract->center.y = 1.2;
}

void	mandelbrot(t_fract *fract)
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
		while (x < 1920)
		{
			c.x = (((fract->max.x - fract->min.x) * x) / 1920.0 - fract->center.x) / fract->zoom.x + fract->move.x;
			c.y = (((fract->max.y - fract->min.y) * y) / 1080.0 - 1.2) / fract->zoom.x + fract->move.y;
			z.x = 0;
			z.y = 0;
			fract->iter = 0;
			while (z.x * z.x + z.y * z.y < 4
					&& fract->iter < fract->iter_max)
			{
				xtemp = z.x * z.x - z.y * z.y;
				z.y = 2 * z.x * z.y + c.y;
				z.x = xtemp + c.x;
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
