/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:58:01 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/07 17:33:19 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"

void		color(int x, int y, t_fract *fract)
{
	double	div;
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;

	red = 0;
	green = 0;
	blue = 0;
	srand(time(NULL));
	div = fract->iter / (double)fract->iter_max;
	if (fract->color_base == BLACK)
		fract->window.img.str[x + y * 1024] = 0;
	if (fract->color_mode == COS)
	{
		red = 0xFF * ft_fabs(cos(fract->iter));
		blue = 0xFF * ft_fabs(cos(fract->iter));
		green = 0xFF * ft_fabs(cos(fract->iter));
	}
	else if (fract->color_mode == SIN)
	{
		red = 0xFF * ft_fabs(sin(fract->iter));
		blue = 0xFF * ft_fabs(sin(fract->iter));
		green = 0xFF * ft_fabs(sin(fract->iter));
	}
	else if (fract->color_mode == LOG)
	{
		red = 0xFF * log(div);
		blue = 0xFF * log(div);
		green = 0xFF * log(div);
	}
	else if (fract->color_mode == INV_LOG)
	{
		red = 0xFF / log(fract->iter);
		blue = 0xFF / log(fract->iter);
		green = 0xFF / log(fract->iter);
	}
	else
	{
		red = 0xFF * fract->iter / fract->iter_max;
		green = 0xFF * fract->iter / fract->iter_max;
		blue = 0xFF * fract->iter / fract->iter_max;
	}
	if (fract->color_base == MIXED_1)
	{
		red = 0xFF * cos(fract->iter * 0.04);
		green = 0xFF * cos(fract->iter * 0.05);
		blue = 0xFF * cos(fract->iter * 0.06);
	}
	if (fract->color_base == MIXED_2)
	{
		red = 0xFF * ft_fabs(cos(fract->iter * 0.02));
		green = 0xFF * ft_fabs(cos(fract->iter * 0.03));
		blue = 0xFF * ft_fabs(cos(fract->iter * 0.04));
	}
	if (fract->color_base == MIXED_3)
	{
		red = 0xFF * ft_fabs(cos(fract->iter * 0.12));
		green = 0xFF * ft_fabs(cos(fract->iter * 0.13));
		blue = 0xFF * ft_fabs(cos(fract->iter * 0.14));
	}
	if (fract->color_base == MIXED_4)
	{
		red = 0xFF * ft_fabs(cos(fract->iter * 0.20));
		green = 0xFF * ft_fabs(cos(fract->iter * 0.15));
		blue = 0xFF * ft_fabs(cos(fract->iter * 0.10));
	}
	if (fract->color_base == MIXED_5)
	{
		red = 0xFF * ft_fabs(cos(fract->iter * 0.04));
		green = 0xFF * ft_fabs(cos(fract->iter * 0.03));
		blue = 0xFF * ft_fabs(cos(fract->iter * 0.02));
	}
	if (fract->color_base == RED)
	{
		green = 0;
		blue = 0;
	}
	else if (fract->color_base == GREEN)
	{
		red = 0;
		blue = 0;
	}
	else if (fract->color_base == BLUE)
	{
		red = 0;
		green = 0;
	}
	fract->window.img.str[x + y * 1024] = red << 16
		| green << 8
		| blue;
}

void		color_inside(int x, int y, t_fract *fract)
{
	double	div;

	div = 255 * fract->iter / fract->iter_max;
	if (fract->color_inside == WHITE)
		fract->window.img.str[x + y * 1024] = 0xFFFFFF;
	else if (fract->color_inside == RED)
		fract->window.img.str[x + y * 1024] = 0xFF0000;
	else if (fract->color_inside == GREEN)
		fract->window.img.str[x + y * 1024] = 0xFF00;
	else if (fract->color_inside == BLUE)
		fract->window.img.str[x + y * 1024] = 0xFF;
	else
		fract->window.img.str[x + y * 1024] = 0;
	if (fract->color_inside_mode == COS)
		fract->window.img.str[x + y * 1024] *= 255 * ft_fabs(cos(fract->iter
					* 0.01));
	if (fract->color_inside_mode == SIN)
		fract->window.img.str[x + y * 1024] *= 255 * ft_fabs(sin(fract->iter
					* 0.01));
	if (fract->color_inside_mode == LOG)
		fract->window.img.str[x + y * 1024] *= 255 * log(fract->iter);
	if (fract->color_inside_mode == INV_LOG)
		fract->window.img.str[x + y * 1024] *= 255 / log(fract->iter);
}


void		color_buddha_pixel(int x, int y, t_fract *fract)
{
	if (fract->color_mode == NASA)
	{
		if (fract->iter < fract->iter_max / 100 + fract->iter_min)
			fract->red[x + y * 1024]++;
		else if (fract->iter >= fract->iter_max / 100 + fract->iter_min
				&& fract->iter < fract->iter_max / 10 + fract->iter_min)
			fract->green[x + y * 1024]++;
		else if (fract->iter >= fract->iter_max / 10 + fract->iter_min
				&& fract->iter < fract->iter_max)
			fract->blue[x + y * 1024]++;
	}
	if (fract->color_mode == SIN)
	{
		if (fract->iter < fract->iter_max / 20 + fract->iter_min)
			fract->window.img.str[y + x * 1024] += 25 * 65536;
		else if (fract->iter >= fract->iter_max / 20 + fract->iter_min
				&& fract->iter < fract->iter_max / 5 + fract->iter_min)
			fract->window.img.str[y + x * 1024] += 25 * 256;
		else if (fract->iter >= fract->iter_max / 5 + fract->iter_min
				&& fract->iter < fract->iter_max)
			fract->window.img.str[y + x * 1024] += 25;
	}
	else
		fract->window.img.str[y + x * 1024]++;
}
