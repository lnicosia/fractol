/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:58:01 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/15 18:54:02 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"
#include <math.h>

void		color(int x, int y, t_fract *fract)
{
	float	div;

	div = 255 * fract->iter / fract->iter_max;
	if (fract->color_mode == COS)
		div = cos(div);
	else if (fract->color_mode == SIN)
		div = sin(div);
	if (fract->color_base == WHITE)
		fract->window.img.str[x + y * 1920] = (65536 * div + 256 * div + div);
	if (fract->color_base == RED)
		fract->window.img.str[x + y * 1920] = 65536 * div;
	if (fract->color_base == GREEN)
		fract->window.img.str[x + y * 1920] = 256 * div;
	if (fract->color_base == BLUE)
		fract->window.img.str[x + y * 1920] = div;
}

void		colorize_buddha(t_fract *fract)
{
	int				x;
	int				y;
	unsigned int	max;
	unsigned int	col;

	y = 0;
	max = 0;
	while (y < 1024)
	{
		x = 0;
		while (x < 1024)
		{
			if (fract->window.img.str[y + x * 1024] > max)
				max = fract->window.img.str[y + x * 1024];
			x++;
		}
		y++;
	}
	y = 0;
	ft_printf("Max count = %u\n", max);
	while (y < 1024)
	{
		x = 0;
		while (x < 1024)
		{
			//col = 255 * sqrt(fract->window.img.str[y + x * 1024]) / sqrt(max);
			col = 255 * (pow(fract->window.img.str[y + x * 1024] / (double)max, 1/2.0));
			//col = 255 * fract->window.img.str[y + x * 1024] / (double)max;
			if (fract->color_mode == COS)
			{
				if (fract->iter < fract->iter_max / 20 + 15)
					fract->window.img.str[y + x * 1024] = col * 65536;
				else if(fract->iter >= fract->iter_max / 20 + 15 && fract->iter < fract->iter_max / 5 + 15)
					fract->window.img.str[y + x * 1024] = col * 256;
				else if(fract->iter >= fract->iter_max / 5 + 15 && fract->iter < fract->iter_max)
					fract->window.img.str[y + x * 1024] = col;
			}
			else
			{
				if (fract->color_base == WHITE)
					fract->window.img.str[y + x * 1024] = col + 256 * col + 65536 * col;
				if (fract->color_base == RED)
					fract->window.img.str[y + x * 1024] = 65536 * col;
				if (fract->color_base == GREEN)
					fract->window.img.str[y + x * 1024] = 256 * col;
				if (fract->color_base == BLUE)
					fract->window.img.str[y + x * 1024] = col;
			}
			x++;
		}
		y++;
	}
}

void		color_buddha(int x, int y, t_fract *fract)
{
	double	mul;

	mul = 25;
	if (fract->color_mode == COS)
	{
		//mul = sqrt(mul);
		if (fract->iter < fract->iter_max / 20 + 15)
			fract->window.img.str[y + x * 1024] += mul * 256 * 256;
		else if(fract->iter >= fract->iter_max / 20 + 15 && fract->iter < fract->iter_max / 5 + 15)
			fract->window.img.str[y + x * 1024] += mul * 256;
		else if(fract->iter >= fract->iter_max / 5 + 15 && fract->iter < fract->iter_max)
			fract->window.img.str[y + x * 1024] += mul;
	}
	else if (fract->color_mode == SIN)
		fract->window.img.str[y + x * 1024] += 1;
	else
	{
		if (fract->color_base == WHITE)
			fract->window.img.str[y + x * 1024] += mul * 256 * 256 + mul * 256 + mul;
		if (fract->color_base == RED)
			fract->window.img.str[y + x * 1024] += mul * 256 * 256;
		if (fract->color_base == GREEN)
			fract->window.img.str[y + x * 1024] += mul * 256;
		if (fract->color_base == BLUE)
			fract->window.img.str[y + x * 1024] += mul;
	}
}

void		swap_color_base(int key, t_fract *fract)
{
	if (key == K1_KEY)
		fract->color_base = WHITE;
	else if (key == K2_KEY)
		fract->color_base = RED;
	else if (key == K3_KEY)
		fract->color_base = GREEN;
	else if (key == K4_KEY)
		fract->color_base = BLUE;
	fract->func(fract);
}

void		swap_color_mode(int key, t_fract *fract)
{
	if (key == NK1_KEY)
		fract->color_mode = FLAT;
	else if (key == NK2_KEY)
		fract->color_mode = COS;
	else if (key == NK3_KEY)
		fract->color_mode = SIN;
	fract->func(fract);
}
