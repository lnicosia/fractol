/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data->fract[0].c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:28:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/04 12:10:26 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	julia(t_env *data)
{
	int			x;
	int			y;
	double		xtemp;
	t_fcoord2	z;

	y = 0;
	printf("[Julia]..\n");
	init_window(&data->fract[0], data, "[Julia]");
	data->fract[0].iter_max = 1000;
	while (y < data->s_height)
	{
		x = 0;
		while (x < data->s_width)
		{
			z.x = 1.5 * (x - data->s_width / 2) / (0.5 * data->s_width) + data->move.x;
			z.y = (y - data->s_height / 2) / (0.5 * data->s_height) + data->move.y;
			data->fract[0].iter = 0;
			while (z.x * z.x + z.y * z.y < 4
					&& data->fract[0].iter < data->fract[0].iter_max)
			{
				xtemp = z.x * z.x - z.y * z.y;
				z.y = 2 * z.x * z.y + 0.27015;
				z.x = xtemp - 0.7;
				data->fract[0].iter++;
			}
			//printf("[%d][%d] = ", y, x);
			if (data->fract[0].iter == data->fract[0].iter_max)
			{
				data->fract[0].window.img.str[x + data->s_width * y] = 0;
				//printf("black\n");
			}
			else
			{
				data->fract[0].window.img.str[x + data->s_width * y] = 0xFFFFFF / data->fract[0].iter;
				//data->fract[0].window.img.str[x + data->s_width * y] = data->fract[0].iter;
				//printf("white\n");
				//printf("iter = %d\n", data->fract[0].iter);
			}
			x++;
		}
		y++;
	}
	mlx_clear_window(data->mlx_ptr, data->fract[0].window.win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->fract[0].window.win_ptr, data->fract[0].window.img_ptr, 0, 0);
}
