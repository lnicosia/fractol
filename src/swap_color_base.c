/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_color_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:59:47 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/07 17:11:49 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"

void		swap_color_base4(int key, t_fract *fract)
{
	if (key == K0_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside = MIXED_5;
		else
			fract->color_base = MIXED_5;
	}
}

void		swap_color_base3(int key, t_fract *fract)
{
	if (key == K7_KEY)
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
	else if (key == K9_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside = MIXED_4;
		else
			fract->color_base = MIXED_4;
	}
	else
		swap_color_base4(key, fract);
}

void		swap_color_base2(int key, t_fract *fract)
{
	if (key == K4_KEY)
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
	else
		swap_color_base3(key, fract);
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
	else
		swap_color_base2(key, fract);
	fract->func(fract);
}
