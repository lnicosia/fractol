/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:58:01 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 15:12:11 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"

void	color_inside(int x, int y, t_fract *fract)
{

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

void	color_buddha_sin(int x, int y, t_fract *fract)
{
	x = x - fract->move.y * 60;
	y = y - fract->move.x * 50;
	if (x < 0 || x >= 1024 || y < 0 || y >= 1024)
		return ;
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

void	color_buddha_pixel(int x, int y, t_fract *fract)
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
	else
		color_buddha_sin(x, y, fract);
}

void	reset_img(unsigned int *array)
{
	int	i;

	i = -1;
	while (++i < 1048576)
		array[i] = 0;
}

int		init_color_arrays(t_fract *fract)
{
	if (fract->color_mode == NASA)
	{
		if (!(fract->red = (unsigned int*)malloc(sizeof(unsigned int)
			* 1048576)))
		{
			ft_printf("Could not malloc green array\n");
			free_all(fract);
		}
		reset_img(fract->red);
		if (!(fract->blue = (unsigned int*)malloc(sizeof(unsigned int)
			* 1048576)))
		{
			ft_printf("Could not malloc green array\n");
			free_all(fract);
		}
		reset_img(fract->blue);
		if (!(fract->green = (unsigned int*)malloc(sizeof(unsigned int)
			* 1048576)))
		{
			ft_printf("Could not malloc green array\n");
			free_all(fract);
		}
		reset_img(fract->green);
	}
	return (0);
}
