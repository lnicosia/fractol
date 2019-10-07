/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_color_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:12:16 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/07 17:13:53 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"

void		swap_color_mode2(int key, t_fract *fract)
{
	if (key == NK4_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside_mode = NASA;
		else
			fract->color_mode = NASA;
	}
	if (key == NK5_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside_mode = LOG;
		else
			fract->color_mode = LOG;
	}
	if (key == NK6_KEY)
	{
		if (fract->maj_buffer)
			fract->color_inside_mode = INV_LOG;
		else
			fract->color_mode = INV_LOG;
	}
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
	else
		swap_color_mode2(key, fract);
	fract->func(fract);
}
