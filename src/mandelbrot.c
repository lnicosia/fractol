/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:29:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/04 17:16:02 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	mandelbrot(t_env *data)
{
	int			x;
	int			y;
	double		xtemp;
	t_fcoord2	z;
	t_fcoord2	c;

	y = 0;
	data->fract[1].iter_max = 100;
	while (y < data->s_height)
	{
		x = 0;
		while (x < data->s_width)
		{
			c.x = x / (data->s_width / 2.7) - 2.1;
			c.y = y / (data->s_height / 2.4) - 1.2;
			z.x = 0;
			z.y = 0;
			data->fract[1].iter = 0;
			while (z.x * z.x + z.y * z.y < 4
					&& data->fract[1].iter < data->fract[1].iter_max)
			{
				xtemp = z.x * z.x - z.y * z.y;
				z.y = 2 * z.x * z.y + c.y;
				z.x = xtemp + c.x;
				data->fract[1].iter++;
			}
			if (data->fract[1].iter == data->fract[1].iter_max)
				data->fract[1].window.img.str[x + data->s_width * y] = 0;
			else
			{
				data->fract[1].window.img.str[x + data->s_width * y] = 0xFFFFFF * (int)(256 * data->fract[1].iter / data->fract[1].iter_max);
			}
			x++;
		}
		y++;
	}
	mlx_clear_window(data->mlx_ptr, data->fract[1].window.win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->fract[1].window.win_ptr, data->fract[1].window.img_ptr, 0, 0);
}
