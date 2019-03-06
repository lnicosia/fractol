/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:28:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/06 15:16:03 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>
#include <stdio.h>

void	init_ship(t_env *data)
{
	data->fract[2].iter_max = 64;
	data->fract[2].max.x = 2.0;
	data->fract[2].max.y = 2.0;
	data->fract[2].min.x = 2.0;
	data->fract[2].min.y = 2.0;
	data->fract[2].center.x = 1.86;
	data->fract[2].center.y = 0.1;
}

void	ship(t_env *data)
{
	int			x;
	int			y;
	double		xtemp;
	t_fcoord2	z;
	t_fcoord2	c;

	y = 0;
	while (y < data->s_height)
	{
		x = 0;
		while (x < data->s_width)
		{
			c.x = ((0.2 * x) / data->s_width - 1.86) / data->zoom.x + data->move.x / 10;
			c.y = ((0.15 * y) / data->s_height - 0.1) / data->zoom.x + data->move.y / 10;
			z.x = 0;
			z.y = 0;
			data->fract[2].iter = 0;
			while (z.x * z.x + z.y * z.y < 4
					&& data->fract[2].iter < data->fract[2].iter_max)
			{
				xtemp = z.x * z.x - z.y * z.y;
				z.y = fabs(2 * z.x * z.y + c.y);
				z.x = fabs(xtemp + c.x);
				data->fract[2].iter++;
			}
			if (data->fract[2].iter == data->fract[2].iter_max)
				data->fract[2].window.img.str[x + data->s_width * y] = 0;
			else
			{
				data->fract[2].window.img.str[x + data->s_width * y] = 0xFFFFFF * (int)(256 * data->fract[2].iter / data->fract[2].iter_max);
			}
			x++;
		}
		y++;
	}
	mlx_clear_window(data->mlx_ptr, data->fract[2].window.win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->fract[2].window.win_ptr, data->fract[2].window.img_ptr, 0, 0);
}
