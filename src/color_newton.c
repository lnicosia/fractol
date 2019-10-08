/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_newton.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:30:44 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/07 17:33:24 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		is_tol(t_complex z, t_complex root, double tolerance)
{
	return (fabs(ft_csub(z, root).r) < tolerance
			&& fabs(ft_csub(z, root).i) < tolerance);
}

void	color_red(int x, int y, t_fract *fract)
{
	if (fract->color_mode == FLAT)
	{
		if (fract->color_base == WHITE)
			fract->window.img.str[x + 1024 * y] = 0xFF0000 *
				(255 * fract->iter / fract->iter_max);
		else if (fract->color_base == BLACK)
			fract->window.img.str[x + 1024 * y] = (255 * fract->iter
			/ fract->iter_max) << 16;
		else if (fract->color_base == RED)
			fract->window.img.str[x + 1024 * y] = ((0xFF
			* fract->iter / fract->iter_max)) << 16
				| ((0x99 * fract->iter / fract->iter_max)) << 8;
		else
			fract->window.img.str[x + 1024 * y] = 0xFF9900 *
				(255 * fract->iter / fract->iter_max);
	}
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
	{
		if (fract->color_base == WHITE)
			fract->window.img.str[x + 1024 * y] = 0xFF00 *
				(255 * fract->iter / fract->iter_max);
		else if (fract->color_base == BLACK)
			fract->window.img.str[x + 1024 * y] = (255 * fract->iter
			/ fract->iter_max) << 8;
		else if (fract->color_base == RED)
			fract->window.img.str[x + 1024 * y] = (0x99
			* fract->iter / fract->iter_max) << 16
				| (0xCC * fract->iter / fract->iter_max) << 8
				| (0xFF * fract->iter / fract->iter_max);
		else
			fract->window.img.str[x + 1024 * y] = 0x99CCFF *
				(255 * fract->iter / fract->iter_max);
	}
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
	{
		if (fract->color_base == WHITE)
			fract->window.img.str[x + 1024 * y] = 0xFF *
				(255 * fract->iter / fract->iter_max);
		else if (fract->color_base == BLACK)
			fract->window.img.str[x + 1024 * y] = (255 * fract->iter
			/ fract->iter_max);
		else if (fract->color_base == RED)
			fract->window.img.str[x + 1024 * y] = (0x33
			* fract->iter / fract->iter_max) << 8
				| (0x66 * fract->iter / fract->iter_max);
		else
			fract->window.img.str[x + 1024 * y] = 0xFF *
				(255 * fract->iter / fract->iter_max);
	}
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
	{
		if (fract->color_base == WHITE)
			fract->window.img.str[x + 1024 * y] = 0xFF * z.r
			+ 0x00FF00 * z.i;
		else
			fract->window.img.str[x + 1024 * y] = 0xFF * z.r
			+ 0x00FF00 * z.i;
	}
	else if (fract->color_mode == COS)
		fract->window.img.str[x + 1024 * y] = 0xFF0000 * fabs(cos(z.r
		* 0.05));
	else if (fract->color_mode == SIN)
		fract->window.img.str[x + 1024 * y] = 0xFF *
			sin(fract->iter * 0.01);
}
