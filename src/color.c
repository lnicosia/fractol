/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:58:01 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/11 18:29:34 by lnicosia         ###   ########.fr       */
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

void		color_buddha(int x, int y, t_fract *fract)
{
	if (fract->color_base == WHITE)
		fract->window.img.str[y + x * 1024] += 25 * 256 * 256 + 25 * 256 + 25;
	if (fract->color_base == RED)
		fract->window.img.str[y + x * 1024] += 25 * 256 * 256;
	if (fract->color_base == GREEN)
		fract->window.img.str[y + x * 1024] += 25 * 256;
	if (fract->color_base == BLUE)
		fract->window.img.str[y + x * 1024] += 25;
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
