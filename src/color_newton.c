/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_newton.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:30:44 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/20 17:40:44 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void	color_red(int x, int y, t_fract *fract)
{
	if (fract->color_mode == FLAT)
		fract->window.img.str[x + 1024 * y] = 0xFF0000 *
			(255 * fract->iter / fract->iter_max);
	else if (fract->color_mode == COS)
		fract->window.img.str[x + 1024 * y] = 0xFF0000 *
			cos(fract->iter * 0.01);
	else if (fract->color_mode == SIN)
		fract->window.img.str[x + 1024 * y] = 0xFF0000 *
			sin(fract->iter * 0.01);
}

void	color_green(int x, int y, t_fract *fract)
{
	if (fract->color_mode == FLAT)
		fract->window.img.str[x + 1024 * y] = 0xFF00 *
			(255 * fract->iter / fract->iter_max);
	else if (fract->color_mode == COS)
		fract->window.img.str[x + 1024 * y] = 0xFF00 *
			cos(fract->iter * 0.01);
	else if (fract->color_mode == SIN)
		fract->window.img.str[x + 1024 * y] = 0xFF00 *
			sin(fract->iter * 0.01);
}

void	color_blue(int x, int y, t_fract *fract)
{
	if (fract->color_mode == FLAT)
		fract->window.img.str[x + 1024 * y] = 0xFF *
			(255 * fract->iter / fract->iter_max);
	else if (fract->color_mode == COS)
		fract->window.img.str[x + 1024 * y] = 0xFF *
			cos(fract->iter * 0.01);
	else if (fract->color_mode == SIN)
		fract->window.img.str[x + 1024 * y] = 0xFF *
			sin(fract->iter * 0.01);
}

void	color_newton(int x, int y, t_fract *fract, t_complex z)
{
	if (fract->color_mode == FLAT)
		fract->window.img.str[x + 1024 * y] = 0xFF * z.r + 0x00FF00 * z.i;
	else if (fract->color_mode == COS)
		fract->window.img.str[x + 1024 * y] = 0xFF0000 * fabs(cos(z.r * 0.05));
	else if (fract->color_mode == SIN)
		fract->window.img.str[x + 1024 * y] = 0xFF *
			sin(fract->iter * 0.01);
}
