/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:33:53 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/22 11:58:52 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fill_img(t_coord2 c, t_fract *fract, int color, float brightness)
{
	int	red;
	int	green;
	int blue;

	if (c.x < 0 || c.x >= 1024 || c.y < 0 || c.y >=
			1024)
		return ;
	if (brightness == 1)
	{
		fract->window.img.str[c.x + c.y * 1024] = color;
		return ;
	}
	red = color >> 16 & 0xFF;
	green = color >> 8 & 0xFF;
	blue = color & 0xFF;
	red = red * brightness;
	blue = blue * brightness;
	green = green * brightness;
	fract->window.img.str[c.x + c.y * 1024] = ((red << 16) | (green << 8)
			| blue);
}

void	plot_line_low(t_coord2 c1, t_coord2 c2, t_fract *fract, int color)
{
	int	dx;
	int	dy;
	int	yi;
	int	e;

	dy = c2.y - c1.y;
	dx = c2.x - c1.x;
	yi = dy < 0 ? -1 : 1;
	dy = ft_abs(dy);
	e = 2 * dy - dx;
	while (c1.x <= c2.x)
	{
		fill_img(c1, fract, color, 1);
		c1.y = e > 0 ? c1.y + yi : c1.y;
		e = e > 0 ? e - 2 * dx : e;
		e += 2 * dy;
		c1.x++;
	}
}

void	plot_line_high(t_coord2 c1, t_coord2 c2, t_fract *fract, int color)
{
	int	dx;
	int	dy;
	int	xi;
	int	e;

	dy = c2.y - c1.y;
	dx = c2.x - c1.x;
	xi = dx < 0 ? -1 : 1;
	dx = ft_abs(dx);
	e = 2 * dx - dy;
	while (c1.y <= c2.y)
	{
		fill_img(c1, fract, color, 1);
		c1.x = e > 0 ? c1.x + xi : c1.x;
		e = e > 0 ? e - 2 * dy : e;
		e += 2 * dx;
		c1.y++;
	}
}

void	plot_line(t_coord2 c1, t_coord2 c2, t_fract *fract, int color)
{
	if (ft_abs(c2.y - c1.y) < ft_abs(c2.x - c1.x))
		if (c1.x > c2.x)
			plot_line_low(c2, c1, fract, color);
		else
			plot_line_low(c1, c2, fract, color);
	else
	{
		if (c1.y > c2.y)
			plot_line_high(c2, c1, fract, color);
		else
			plot_line_high(c1, c2, fract, color);
	}
}
