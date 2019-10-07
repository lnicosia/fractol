/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:58:01 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/07 18:19:33 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"

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
