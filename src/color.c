/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:58:01 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/02 11:29:39 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"
#include <math.h>

void		color(int x, int y, t_fract *fract)
{
	float	div;
	/*float	red;
	float	green;
	float	blue;*/

	div = 255 * fract->iter / fract->iter_max;
	if (fract->color_mode == COS)
	{
		div = cos(fract->iter * 0.01);
	}
	else if (fract->color_mode == SIN)
	{
		div = sin(fract->iter * 0.02);
	}
	if (fract->color_base == BLACK)
		fract->window.img.str[x + y * 1920] = 0;
	if (fract->color_base == WHITE)
		fract->window.img.str[x + y * 1920] = 65536 * div + 256 * div + div;
	if (fract->color_base == RED)
		fract->window.img.str[x + y * 1920] = 65536 * div;
	if (fract->color_base == GREEN)
		fract->window.img.str[x + y * 1920] = 256 * div;
	if (fract->color_base == BLUE)
		fract->window.img.str[x + y * 1920] = div;
}

void		color_inside(int x, int y, t_fract *fract)
{
	if (fract->color_inside == BLACK)
		fract->window.img.str[x + y * 1920] = 0;
	if (fract->color_inside == WHITE)
		fract->window.img.str[x + y * 1920] = 0xFFFFFF;
	if (fract->color_inside == RED)
		fract->window.img.str[x + y * 1920] = 0xFF0000;
	if (fract->color_inside == GREEN)
		fract->window.img.str[x + y * 1920] = 0xFF00;
	if (fract->color_inside == BLUE)
		fract->window.img.str[x + y * 1920] = 0xFF;
	if (fract->color_inside_mode == COS)
		fract->window.img.str[x + y * 1920] *= 255 * cos(fract->iter * 0.01);
	if (fract->color_inside_mode == SIN)
		fract->window.img.str[x + y * 1920] *= 255 * sin(fract->iter * 0.01);
}

void		colorize_buddha(t_fract *fract)
{
	int				x;
	int				y;
	int				color_coord;
	int				coord;
	unsigned int	max;
	unsigned int	max_blue;
	unsigned int	max_green;
	unsigned int	max_red;
	unsigned int	col;
	unsigned int	col_blue;
	unsigned int	col_green;
	unsigned int	col_red;

	max = 0;
	max_blue = 0;
	max_green = 0;
	max_red = 0;
	y = -1;
	while (++y < 1024)
	{
		x = -1;
		while (++x < 1024)
		{
			/*coord = x - fract->move.x * 50 + (y - fract->move.y * 50) * 1024;
			if (x - fract->move.x * 50 < 0 || x - fract->move.x * 50 >= 1024
					|| y - fract->move.y * 50 < 0 || y - fract->move.y * 50 >= 1024)
				continue;*/
			coord = x + y * 1024;
			if (fract->window.img.str[coord] > max)
				max = fract->window.img.str[coord];
			if (fract->color_mode == NASA)
			{
				if (fract->red[coord] > max_red)
					max_red = fract->red[coord];
				if (fract->green[coord]  > max_green)
					max_green = fract->green[coord];
				else if (fract->blue[coord] > max_blue)
					max_blue = fract->blue[coord];
			}
		}
	}
	if (fract->color_mode == NASA)
	{
		ft_printf("Max count = %u\n", max);
		ft_printf("Max red = %u\n", max_red);
		ft_printf("Max green = %u\n", max_green);
		ft_printf("Max blue = %u\n", max_blue);
	}
	y = -1;
	while (++y < 1024)
	{
		x = -1;
		while (++x < 1024)
		{
			coord = x - fract->move.x * 50 + (y - fract->move.y * 60) * 1024;
			color_coord = y + x * 1024;
			if (x - fract->move.x * 50 < 0 || x - fract->move.x * 50 >= 1024
					|| y - fract->move.y * 60 < 0 || y - fract->move.y * 60 >= 1024)
				continue;
			if (fract->color_mode == FLAT)
				col = 255 * (pow(fract->window.img.str[coord] / (double)max, 1/2.0));
			else if (fract->color_mode == COS)
				col = 255 * fract->window.img.str[coord] / (double)max;
			//ft_printf("col = %u\n", col);
			if (fract->color_mode == NASA)
			{
				col_red = 255 * (pow(fract->red[color_coord] / (double)max_red, 1/2.0));
				col_green = 255 * (pow(fract->green[color_coord] / (double)max_green, 1/2.0));
				col_blue = 255 * (pow(fract->blue[color_coord] / (double)max_blue, 1/2.0));
				/*col_red = 255 * fract->red[y + x * 1024] / (double)max_red;
				  col_green = 255 * fract->green[y + x * 1024] / (double)max_green;
				  col_blue = 255 * fract->blue[y + x * 1024] / (double)max_blue;*/
				fract->window.img.str[coord] = 65536 * col_red + 256 * col_green + col_blue;
			}
			else
			{
				if (fract->color_base == WHITE)
					fract->window.img.str[coord] = col + 256 * col + 65536 * col;
				if (fract->color_base == RED)
					fract->window.img.str[coord] = 65536 * col;
				if (fract->color_base == GREEN)
					fract->window.img.str[coord] = 256 * col;
				if (fract->color_base == BLUE)
					fract->window.img.str[coord] = col;
			}
		}
	}
}

void		color_buddha(int x, int y, t_fract *fract)
{
	double	mul;

	mul = 25;
	if (fract->color_mode == NASA)
	{
		if (fract->iter < fract->iter_max / 100 + fract->iter_min)
			fract->red[x + y * 1024]++;
		else if(fract->iter >= fract->iter_max / 100 + fract->iter_min && fract->iter < fract->iter_max / 10 + fract->iter_min)
			fract->green[x + y * 1024]++;
		else if(fract->iter >= fract->iter_max / 10 + fract->iter_min && fract->iter < fract->iter_max)
			fract->blue[x + y * 1024]++;
	}
	if (fract->color_mode == SIN)
	{
		if (fract->iter < fract->iter_max / 20 + fract->iter_min)
			fract->window.img.str[x + y * 1024] += mul * 65536;
		else if(fract->iter >= fract->iter_max / 20 + fract->iter_min && fract->iter < fract->iter_max / 5 + fract->iter_min)
			fract->window.img.str[x + y * 1024] += mul * 256;
		else if(fract->iter >= fract->iter_max / 5 + fract->iter_min && fract->iter < fract->iter_max)
			fract->window.img.str[x + y * 1024] += mul;
	}
	else
		fract->window.img.str[x + y * 1024]++;
}

void		swap_color_base(int key, t_fract *fract)
{
	if (key == K1_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside = BLACK;
		else
			fract->color_base = BLACK;
	}
	if (key == K2_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside = WHITE;
		else
			fract->color_base = WHITE;
	}
	else if (key == K3_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside = RED;
		else
			fract->color_base = RED;
	}
	else if (key == K4_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside = GREEN;
		else
			fract->color_base = GREEN;
	}
	else if (key == K5_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside = BLUE;
		else
			fract->color_base = BLUE;
	}
	fract->func(fract);
}

void		swap_color_mode(int key, t_fract *fract)
{
	if (key == NK1_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside_mode = FLAT;
		else
			fract->color_mode = FLAT;
	}
	else if (key == NK2_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside_mode = COS;
		else
			fract->color_mode = COS;
	}
	if (key == NK3_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside_mode = SIN;
		else
			fract->color_mode = SIN;
	}
	if (key == NK4_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside_mode = NASA;
		else
			fract->color_mode = NASA;
	}
	fract->func(fract);
}
