/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:46:30 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/08 15:17:00 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

float		fpart(float x)
{
	return (x - (int)x);
}

float		rfpart(float x)
{
	return (1.0 - fpart(x));
}

t_complex	compute_mandelbrot_sequence(t_complex z, t_complex c)
{
	t_complex	res;

	res.i = 2 * z.r * z.i + c.i;
	res.r = z.r * z.r - z.i * z.i + c.r;
	return (res);
}

void		put_buddha_pixel(t_complex z, t_fract *fract)
{
	t_coord2	pos;

	pos.x = (int)((z.r - fract->min.x)
			* fract->zoom);
	pos.y = (int)((z.i - fract->min.y)
			* fract->zoom);
	if (pos.x >= 0 && pos.x < 1024
			&& pos.y >= 0 && pos.y < 1024)
	{
		color_buddha_pixel(pos.x, pos.y, fract);
		pos.y = (int)((-z.i - fract->min.y)
				* fract->zoom);
		if (pos.y >= 0 && pos.y < 1024)
			color_buddha_pixel(pos.x,
					pos.y, fract);
	}
}

void		iterate_valid_point(t_fract *fract, t_complex c)
{
	t_complex	z;

	z = new_complex(0, 0);
	fract->iter = 0;
	while (z.r * z.r + z.i * z.i < 4 && fract->iter < fract->iter_max)
	{
		z = compute_mandelbrot_sequence(z, c);
		put_buddha_pixel(z, fract);
		fract->iter++;
	}
}
