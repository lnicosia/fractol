/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:58:01 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/18 12:22:00 by lnicosia         ###   ########.fr       */
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
		fract->window.img.str[x + y * 1920] = 65536 * div + 256 * div + div;
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
	/*unsigned int	max_blue;
	unsigned int	max_green;
	unsigned int	max_red;*/
	unsigned int	col;
	/*unsigned int	col_blue;
	unsigned int	col_green;
	unsigned int	col_red;*/

	y = 0;
	max = 0;
	/*max_blue = 0;
	max_green = 0;
	max_red = 0;*/
	while (y < 1024)
	{
		x = 0;
		while (x < 1024)
		{
			if (fract->window.img.str[y + x * 1024] > max)
				max = fract->window.img.str[y + x * 1024];
			/*if (fract->window.img.str[y + x * 1024] / 65536 > max_red)
				max_red = fract->window.img.str[y + x * 1024] / 65536;
			if (fract->window.img.str[y + x * 1024] / 256  > max_green)
				max_green = fract->window.img.str[y + x * 1024];
			else if (fract->window.img.str[y + x * 1024] > max_blue)
				max_blue = fract->window.img.str[y + x * 1024];*/
			x++;
		}
		y++;
	}
	y = 0;
	ft_printf("Max count = %u\n", max);
	/*ft_printf("Max red = %u\n", max_red);
	ft_printf("Max green = %u\n", max_green);
	ft_printf("Max blue = %u\n", max_blue);*/
	while (y < 1024)
	{
		x = 0;
		while (x < 1024)
		{
			//col = 255 * sqrt(fract->window.img.str[y + x * 1024]) / sqrt(max);
			if (fract->color_mode == FLAT)
				col = 255 * (pow(fract->window.img.str[y + x * 1024] / (double)max, 1/2.0));
			else if (fract->color_mode == SIN)
				col = 255 * fract->window.img.str[y + x * 1024] / (double)max;
			//ft_printf("col = %u\n", col);
			if (fract->color_mode == COS)
			{
				/*col_red = 255 * (pow(fract->window.img.str[y + x * 1024] / (double)max_red, 1/2.0));
				col_green = 255 * (pow(fract->window.img.str[y + x * 1024] / (double)max_green, 1/2.0));
				col_blue = 255 * (pow(fract->window.img.str[y + x * 1024] / (double)max_blue, 1/2.0));
				fract->window.img.str[y + x * 1024] = 65536 * col_red + 256 * col_green + col_blue;*/
				/*if (col < 12)
					fract->window.img.str[y + x * 1024] = col;
				else if(col >= 12 && col < 51)
					fract->window.img.str[y + x * 1024] = col * 256;
				else if(col >= 51 && col < 256)
					fract->window.img.str[y + x * 1024] = col * 65536;*/
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
			fract->window.img.str[y + x * 1024] += mul * 65536;
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
			fract->window.img.str[y + x * 1024] += mul * 65536 + mul * 256 + mul;
		if (fract->color_base == RED)
			fract->window.img.str[y + x * 1024] += mul * 65536;
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
