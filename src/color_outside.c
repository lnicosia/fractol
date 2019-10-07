/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_outside.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:18:23 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/07 18:39:04 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		set_color2(t_fract *fract, uint8_t *red, uint8_t *green,
		uint8_t *blue)
{
	if (fract->color_mode == INV_LOG)
	{
		*red = 0xFF / log(fract->iter);
		*blue = 0xFF / log(fract->iter);
		*green = 0xFF / log(fract->iter);
	}
	else
	{
		*red = 0xFF * fract->iter / fract->iter_max;
		*green = 0xFF * fract->iter / fract->iter_max;
		*blue = 0xFF * fract->iter / fract->iter_max;
	}
}

void		set_color(t_fract *fract, uint8_t *red, uint8_t *green,
		uint8_t *blue)
{
	if (fract->color_mode == COS)
	{
		*red = 0xFF * ft_fabs(cos(fract->iter));
		*blue = 0xFF * ft_fabs(cos(fract->iter));
		*green = 0xFF * ft_fabs(cos(fract->iter));
	}
	else if (fract->color_mode == SIN)
	{
		*red = 0xFF * ft_fabs(sin(fract->iter));
		*blue = 0xFF * ft_fabs(sin(fract->iter));
		*green = 0xFF * ft_fabs(sin(fract->iter));
	}
	else if (fract->color_mode == LOG)
	{
		*red = 0xFF * log(fract->iter / (double)fract->iter_max);
		*blue = 0xFF * log(fract->iter / (double)fract->iter_max);
		*green = 0xFF * log(fract->iter / (double)fract->iter_max);
	}
	else
		set_color2(fract, red, blue, green);
}

void		set_mixed_colors2(t_fract *fract, uint8_t *red, uint8_t *green,
		uint8_t *blue)
{
	if (fract->color_base == MIXED_4)
	{
		*red = 0xFF * ft_fabs(cos(fract->iter * 0.20));
		*green = 0xFF * ft_fabs(cos(fract->iter * 0.15));
		*blue = 0xFF * ft_fabs(cos(fract->iter * 0.10));
	}
	if (fract->color_base == MIXED_5)
	{
		*red = 0xFF * ft_fabs(cos(fract->iter * 0.04));
		*green = 0xFF * ft_fabs(cos(fract->iter * 0.03));
		*blue = 0xFF * ft_fabs(cos(fract->iter * 0.02));
	}
}

void		set_mixed_colors(t_fract *fract, uint8_t *red, uint8_t *green,
		uint8_t *blue)
{
	if (fract->color_base == MIXED_1)
	{
		*red = 0xFF * cos(fract->iter * 0.04);
		*green = 0xFF * cos(fract->iter * 0.05);
		*blue = 0xFF * cos(fract->iter * 0.06);
	}
	if (fract->color_base == MIXED_2)
	{
		*red = 0xFF * ft_fabs(cos(fract->iter * 0.02));
		*green = 0xFF * ft_fabs(cos(fract->iter * 0.03));
		*blue = 0xFF * ft_fabs(cos(fract->iter * 0.04));
	}
	if (fract->color_base == MIXED_3)
	{
		*red = 0xFF * ft_fabs(cos(fract->iter * 0.12));
		*green = 0xFF * ft_fabs(cos(fract->iter * 0.13));
		*blue = 0xFF * ft_fabs(cos(fract->iter * 0.14));
	}
	set_mixed_colors2(fract, red, blue, green);
}

void		color(int x, int y, t_fract *fract)
{
	double	div;
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;

	red = 0;
	green = 0;
	blue = 0;
	div = fract->iter / (double)fract->iter_max;
	if (fract->color_base == BLACK)
		fract->window.img.str[x + y * 1024] = 0;
	set_color(fract, &red, &blue, &green);
	set_mixed_colors(fract, &red, &blue, &green);
	if (fract->color_base == RED || fract->color_base == BLUE)
		green = 0;
	if (fract->color_base == GREEN || fract->color_base == BLUE)
		red = 0;
	if (fract->color_base == RED || fract->color_base == GREEN)
		blue = 0;
	fract->window.img.str[x + y * 1024] = red << 16
		| green << 8
		| blue;
}
