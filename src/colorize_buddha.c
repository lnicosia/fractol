/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.colorize_buddha.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:30:53 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/08 11:49:14 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "colorize_buddha.h"

void			set_color_count(t_fract *fract, int coord, t_color_data *cd)
{
	if (fract->window.img.str[coord] > cd->max)
		cd->max = fract->window.img.str[coord];
	if (fract->color_mode == NASA)
	{
		if (fract->red[coord] > cd->max_red)
			cd->max_red = fract->red[coord];
		if (fract->green[coord] > cd->max_green)
			cd->max_green = fract->green[coord];
		else if (fract->blue[coord] > cd->max_blue)
			cd->max_blue = fract->blue[coord];
	}
}

t_color_data	get_color_count(t_fract *fract)
{
	t_color_data	cd;
	int				coord;
	int				x;
	int				y;

	ft_bzero(&cd, sizeof(t_color_data));
	y = -1;
	while (++y < 1024)
	{
		x = -1;
		while (++x < 1024)
		{
			coord = x + y * 1024;
			set_color_count(fract, coord, &cd);
		}
	}
	if (fract->color_mode == NASA)
	{
		ft_printf("max count = %u\n", cd.max);
		ft_printf("max red = %u\n", cd.max_red);
		ft_printf("max green = %u\n", cd.max_green);
		ft_printf("max blue = %u\n", cd.max_blue);
	}
	return (cd);
}

t_color_data	get_color_value(t_fract *fract, t_color_data cd, int coord,
		int color_coord)
{
	if (fract->color_mode == FLAT)
		cd.col = 255 * (pow(fract->window.img.str[coord] / (double)cd.max,
					0.5));
	else if (fract->color_mode == COS)
		cd.col = 255 * fract->window.img.str[coord] / (double)cd.max;
	if (fract->color_mode == NASA)
	{
		cd.col_red = 255 * (pow(fract->red[color_coord]
					/ (double)cd.max_red,
					0.5));
		cd.col_green = 255 * (pow(fract->green[color_coord]
					/ (double)cd.max_green, 0.5));
		cd.col_blue = 255 * (pow(fract->blue[color_coord]
					/ (double)cd.max_blue, 0.5));
	}
	return (cd);
}

void			set_color_value(t_fract *fract, t_color_data cd, int coord)
{
	if (fract->color_mode == NASA)
		fract->window.img.str[coord] = 65536 * cd.col_red + 256
			* cd.col_green + cd.col_blue;
	else
	{
		if (fract->color_base == WHITE)
			fract->window.img.str[coord] = cd.col + 256 * cd.col + 65536
				* cd.col;
		if (fract->color_base == RED)
			fract->window.img.str[coord] = 65536 * cd.col;
		if (fract->color_base == GREEN)
			fract->window.img.str[coord] = 256 * cd.col;
		if (fract->color_base == BLUE)
			fract->window.img.str[coord] = cd.col;
	}
}

void			colorize_buddha(t_fract *fract)
{
	int				x;
	int				y;
	int				color_coord;
	int				coord;
	t_color_data	cd;

	cd = get_color_count(fract);
	y = -1;
	while (++y < 1024)
	{
		x = -1;
		while (++x < 1024)
		{
			if (x - fract->move.x * 50 < 0 || x - fract->move.x * 50 >= 1024
					|| y - fract->move.y * 60 < 0 || y - fract->move.y * 60
					>= 1024)
				continue;
			coord = x - fract->move.x * 50 + (y - fract->move.y * 60) * 1024;
			color_coord = y + x * 1024;
			cd = get_color_value(fract, cd, coord, color_coord);
			set_color_value(fract, cd, coord);
		}
	}
}
