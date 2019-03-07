/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:59:27 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/07 22:16:52 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	init_julia(t_fract *fract)
{
	fract->nb = 0;
	fract->zoom = 400;
	fract->iter_max = 64;
	fract->max.x = 1.2;
	fract->min.x = -2.25;
	fract->min.y = -1.4;
	fract->max.y = 2.5;
	fract->center.x = 2.0;
	fract->center.y = 2.0;
}

void	julia(t_fract *fract)
{
	int			x;
	int			y;
	double		xtemp;
	t_fcoord2	z;

	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			z.x = x / fract->zoom + fract->min.x + fract->move.x;
			z.y = y / fract->zoom + fract->min.y + fract->move.y;
			fract->iter = 0;
			while (z.x * z.x + z.y * z.y < 4
					&& fract->iter < fract->iter_max)
			{
				xtemp = z.x * z.x - z.y * z.y;
				z.y = 2 * z.x * z.y + 0.2321 + fract->transfo.x;
				z.x = xtemp + -0.835 + fract->transfo.y;
				fract->iter++;
			}
			if (fract->iter == fract->iter_max)
				fract->window.img.str[x + 1920 * y] = 0;
			else
			{
				fract->window.img.str[x + 1920 * y] = 65536 * (int)(256 * fract->iter / fract->iter_max);
			}
			x++;
		}
		y++;
	}
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr, fract->window.img_ptr, 0, 0);
}
