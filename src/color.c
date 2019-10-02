/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:58:01 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/02 17:54:44 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"
#include <math.h>

void		color(int x, int y, t_fract *fract)
{
	double	div;
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;

	red = 0;
	green = 0;
	blue = 0;
	div = 255 * fract->iter / fract->iter_max;
	if (fract->color_base == BLACK)
		fract->window.img.str[x + y * 1920] = 0;
	if (fract->color_base == WHITE)
	{
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
		else
		{
			red = 0xFF * fract->iter / fract->iter_max;
			green = 0xFF * fract->iter / fract->iter_max;
			blue = 0xFF * fract->iter / fract->iter_max;
		}
	}
	if (fract->color_base == RED)
	{
		if (fract->color_mode == COS)
			red = 0xFF * ft_fabs(cos(fract->iter));
		else if (fract->color_mode == SIN)
			red = 0xFF * ft_fabs(sin(fract->iter));
		else
			red = 0xFF * fract->iter / fract->iter_max;
	}
	if (fract->color_base == GREEN)
	{
		if (fract->color_mode == COS)
			green = 0xFF * ft_fabs(cos(fract->iter));
		else if (fract->color_mode == SIN)
			green = 0xFF * ft_fabs(sin(fract->iter));
		else
			green = 0xFF * fract->iter / fract->iter_max;
	}
	if (fract->color_base == BLUE)
	{
		if (fract->color_mode == COS)
			blue = 0xFF * ft_fabs(cos(fract->iter));
		else if (fract->color_mode == SIN)
			blue = 0xFF * ft_fabs(sin(fract->iter));
		else
			blue = 0xFF * fract->iter / fract->iter_max;
	}
	if (fract->color_base == MIXED_1)
	{
		if (fract->color_mode == COS)
		{
			red = 0xFF * ft_fabs(cos(fract->iter * 0.03));
			green = 0xFF * ft_fabs(cos(fract->iter * 0.03));
			blue = 0xFF * ft_fabs(cos(fract->iter * 0.02));
		}
		else if (fract->color_mode == SIN)
		{
			red = 0xFF * ft_fabs(sin(fract->iter * 2));
			green = 0xFF * ft_fabs(sin(fract->iter * 2));
			blue = 0xFF * ft_fabs(sin(fract->iter * 2));
		}
		else
		{
			red = 0xFF * fract->iter / fract->iter_max;
			green = 0xFF * fract->iter / fract->iter_max;
			blue = 0xFF * fract->iter / fract->iter_max;
		}
	}
	fract->window.img.str[x + y * 1920] = (0xFF & red) << 16
		| (0xFF & green) << 8
		| (0xFF & blue);
}

void		color_inside(int x, int y, t_fract *fract)
{
	double	div;

	div = 255 * fract->iter / fract->iter_max;
	if (fract->color_mode == COS)
		div = cos(fract->iter * 0.01);
	else if (fract->color_mode == SIN)
		div = sin(fract->iter * 0.02);
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
		//fract->window.img.str[x + y * 1920] *= 65535 * div + 255 * div + div;
	if (fract->color_inside_mode == SIN)
		fract->window.img.str[x + y * 1920] *= 255 * sin(fract->iter * 0.01);
		//fract->window.img.str[x + y * 1920] *= 65535 * div + 255 * div + div;
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
			coord = x + y * 1024;
			if (fract->window.img.str[coord] > max)
				max = fract->window.img.str[coord];
			if (fract->color_mode == NASA)
			{
				if (fract->red[coord] > max_red)
					max_red = fract->red[coord];
				if (fract->green[coord] > max_green)
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
					|| y - fract->move.y * 60 < 0 || y - fract->move.y * 60
					>= 1024)
				continue;
			if (fract->color_mode == FLAT)
				col = 255 * (pow(fract->window.img.str[coord] / (double)max,
							0.5));
			else if (fract->color_mode == COS)
				col = 255 * fract->window.img.str[coord] / (double)max;
			if (fract->color_mode == NASA)
			{
				col_red = 255 * (pow(fract->red[color_coord] / (double)max_red,
							0.5));
				col_green = 255 * (pow(fract->green[color_coord]
							/ (double)max_green, 0.5));
				col_blue = 255 * (pow(fract->blue[color_coord]
							/ (double)max_blue, 0.5));
				fract->window.img.str[coord] = 65536 * col_red + 256
					* col_green + col_blue;
			}
			else
			{
				if (fract->color_base == WHITE)
					fract->window.img.str[coord] = col + 256 * col + 65536
						* col;
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
			fract->window.img.str[y + x * 1024] += mul * 65536;
		else if (fract->iter >= fract->iter_max / 20 + fract->iter_min
				&& fract->iter < fract->iter_max / 5 + fract->iter_min)
			fract->window.img.str[y + x * 1024] += mul * 256;
		else if (fract->iter >= fract->iter_max / 5 + fract->iter_min
				&& fract->iter < fract->iter_max)
			fract->window.img.str[y + x * 1024] += mul;
	}
	else
		fract->window.img.str[y + x * 1024]++;
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
	else if (key == K6_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside = MIXED_1;
		else
			fract->color_base = MIXED_1;
	}
	else if (key == K7_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside = MIXED_2;
		else
			fract->color_base = MIXED_2;
	}
	else if (key == K8_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside = MIXED_3;
		else
			fract->color_base = MIXED_3;
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
