/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:28:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/05 11:09:32 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>
#include <stdio.h>

void	ship(t_env *data)
{
	int			x;
	int			y;
	double		xtemp;
	t_fcoord2	z;
	t_fcoord2	c;

	y = 0;
	data->fract[2].iter_max = 64;
	while (y < data->s_height)
	{
		x = 0;
		while (x < data->s_width)
		{
			c.x = x / (data->s_width / 2.7) - 2.1 + data->move.x;
			c.y = y / (data->s_height / 2.4) - 1.2 + data->move.y;
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
