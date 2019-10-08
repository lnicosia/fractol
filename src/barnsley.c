/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barnsley.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:45:55 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/07 17:33:07 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			init_barnsley(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = FLAT;
	fract->color_inside = WHITE;
	fract->color_inside_mode = FLAT;
	fract->name = "Barnsley";
	fract->zoom = 9;
	fract->inv_zoom = 1 / fract->zoom;
	fract->iter_max = 1500000;
	fract->min.x = 1;
	fract->min.y = -1.35;
	fract->move.x = 0;
	fract->move.y = 0;
	fract->center.x = 512;
	fract->center.y = 50;
	fract->incr = 10000;
	fract->maj_incr = 500000;
	return (0);
}

static void	reset_image(t_fract *fract)
{
	int	i;

	i = -1;
	while (++i < 1048576)
		fract->window.img.str[i] = 0;
}

void		color_barnsley(t_fract *fract, t_coord2 pos, int dice)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;

	red = 0;
	green = 0;
	blue = 0;
	if (fract->color_mode == FLAT)
	{
		green = 0xFF * fract->iter / (double)fract->iter_max;
	}
	if (fract->color_mode == COS)
	{
		red = 0xFF * dice;
		green = 0xFF * dice;
		blue = 0xFF * dice;
	}
	fract->window.img.str[pos.x + pos.y * 1024] = (0xFF & red) << 16
		| (0xFF & green) << 8
		| (0xFF & blue);
}

void		get_barnsley_pixel(int dice, t_fcoord2 *c1, t_fcoord2 *c2)
{
	if (!dice)
	{
		c2->x = 0;
		c2->y = 0.16 * c1->y;
	}
	else if (dice > 0 && dice < 8)
	{
		c2->x = -0.15 * c1->x + 0.28 * c1->y;
		c2->y = 0.26 * c1->x + 0.24 * c1->y + 0.44;
	}
	else if (dice > 7 && dice < 16)
	{
		c2->x = 0.2 * c1->x - 0.26 * c1->y;
		c2->y = 0.23 * c1->x + 0.22 * c1->y + 1.6;
	}
	else
	{
		c2->x = 0.85 * c1->x + 0.04 * c1->y;
		c2->y = -0.04 * c1->x + 0.85 * c1->y + 16;
	}
}

void		barnsley(t_fract *fract)
{
	t_fcoord2	c1;
	t_fcoord2	c2;
	t_coord2	pixel;
	int			dice;

	fract->iter = fract->iter_max;
	c1 = new_fcoord2(0, 0);
	srand(time(NULL));
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	reset_image(fract);
	while (fract->iter > 0)
	{
		dice = rand() % 100;
		get_barnsley_pixel(dice, &c1, &c2);
		pixel.x = fract->center.x + (c2.x - fract->move.x * 0.5)
			* fract->zoom;
		pixel.y = fract->center.y + (c2.y - fract->move.y * 0.5)
			* fract->zoom;
		if (pixel.x >= 0 && pixel.x < 1024
				&& pixel.y >= 0 && pixel.y < 1024)
			color_barnsley(fract, pixel, dice);
		c1 = c2;
		fract->iter--;
	}
	put_fractal_to_window(fract);
}
