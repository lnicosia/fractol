/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barnsley.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:45:55 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/02 12:11:53 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

int			init_barnsley(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = FLAT;
	fract->color_inside = WHITE;
	fract->color_inside_mode = FLAT;
	fract->name = "Barnsley";
	fract->zoom = 10;
	fract->iter_max = 1000000;
	fract->min.x = -2.7;
	fract->min.y = -1.35;
	return (0);
}

static void	reset_image(t_fract *fract)
{
	int	i;

	i = -1;
	while (++i < 2073600)
		fract->window.img.str[i] = 0;
}

void	barnsley(t_fract *fract)
{
	t_fcoord2	c1;
	t_fcoord2	c2;
	t_coord2	pixel;
	int			dice;
	char		*str;

	fract->iter = fract->iter_max;
	c1.x = 0;
	c1.y = 0;
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	reset_image(fract);
	while (fract->iter > 0)
	{
		dice = rand() % 100;
		//ft_printf("rand = %d\n", dice);
		if (!dice)
		{
			c2.x = 0;
			c2.y = 0.16 * c1.y;
		}
		else if (dice > 0 && dice <= 8)
		{
			c2.x = -0.15 * c1.x + 0.28 * c1.y;
			c2.y = 0.26 * c1.x + 0.24 * c1.y + 0.44;
		}
		else if (dice > 7 && dice < 16)
		{
			c2.x = 0.2 * c1.x - 0.26 * c1.y;
			c2.y = 0.23 * c1.x + 0.22 * c1.y + 1.6;
		}
		else
		{
			c2.x = 0.85 * c1.x + 0.04 * c1.y;
			c2.y = -0.04 * c1.x + 0.85 * c1.y + 16;
		}
		pixel.x = (int)(fract->zoom * (c2.x - fract->move.x / 2)) + 960;
		pixel.y = (int)(fract->zoom * (c2.y - fract->move.y / 2)) + 50;
		//ft_printf("[%d][%d]\n", pixel.y, pixel.x);
		if (pixel.x >= 0 && pixel.x < 1920
				&& pixel.y >= 0 && pixel.y < 1080)
		//fract->window.img.str[pixel.x + pixel.y * 1920] += 0xFFFFFF / 100 * dice;
		fract->window.img.str[pixel.x + pixel.y * 1920] = 0x00FF00;
		c1 = c2;
		fract->iter--;
	}
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 10, 0xFFFFFF, "Iterations: ");
	str = ft_itoa(fract->iter_max);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 10, 0xFFFFFF, str);
	free(str);
}
