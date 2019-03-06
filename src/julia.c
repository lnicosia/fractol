/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:59:27 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/06 15:16:18 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	init_julia(t_env *data)
{
	data->fract[0].iter_max = 64;
	data->fract[0].max.x = 2.0;
	data->fract[0].max.y = 2.0;
	data->fract[0].min.x = 2.0;
	data->fract[0].min.y = 2.0;
	data->fract[0].center.x = 2.0;
	data->fract[0].center.y = 2.0;
}

void	julia(t_env *data)
{
	int			x;
	int			y;
	double		xtemp;
	t_fcoord2	z;

	y = 0;
	while (y < data->s_height)
	{
		x = 0;
		while (x < data->s_width)
		{
			//printf("x = %f\n", data->center.x);
			//printf("y = %f\n", data->center.y);
			z.x = ((4.0 * x) / data->s_width - 2.0) / data->zoom.x + data->move.x;
			z.y = ((4.0 * y) / data->s_height - 2.0) / data->zoom.x + data->move.y;
			/*z.x = 2.0 * (x - data->s_width / 2) / (0.5 * data->zoom.x * data->s_width) + data->move.x;
			z.y = (y - data->s_height / 2) / (0.5 * data->zoom.x * data->s_height) + data->move.y;*/
			data->fract[0].iter = 0;
			while (z.x * z.x + z.y * z.y < 4
					&& data->fract[0].iter < data->fract[0].iter_max)
			{
				xtemp = z.x * z.x - z.y * z.y;
				z.y = 2 * z.x * z.y + 0.2321 + data->transfo.x;
				z.x = xtemp + -0.835 + data->transfo.y;
				data->fract[0].iter++;
			}
			if (data->fract[0].iter == data->fract[0].iter_max)
				data->fract[0].window.img.str[x + data->s_width * y] = 0;
			else
			{
				data->fract[0].window.img.str[x + data->s_width * y] = 65536 * (int)(256 * data->fract[0].iter / data->fract[0].iter_max);
			}
			x++;
		}
		y++;
	}
	mlx_clear_window(data->mlx_ptr, data->fract[0].window.win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->fract[0].window.win_ptr, data->fract[0].window.img_ptr, 0, 0);
}
