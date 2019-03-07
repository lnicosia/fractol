/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:59:27 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/07 15:01:54 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	init_julia(t_fract *fract)
{
	fract->nb = 0;
	fract->iter_max = 64;
	fract->max.x = 2.0;
	fract->max.y = 2.0;
	fract->min.x = -2.0;
	fract->min.y = -2.0;
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
			z.x = (((fract->max.x - fract->min.x) * x) / 1920.0 - fract->center.x) / fract->zoom.x + fract->move.x;
			z.y = (((fract->max.y - fract->min.y) * y) / 1080.0 - fract->center.y) / fract->zoom.x + fract->move.y;
			/*z.x = 2.0 * (x - fract->s_width / 2) / (0.5 * fract->zoom.x * fract->s_width) + fract->move.x;
			  z.y = (y - fract->s_height / 2) / (0.5 * fract->zoom.x * fract->s_height) + fract->move.y;*/
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
