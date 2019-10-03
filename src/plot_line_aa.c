/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_line_aa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:42:59 by lnicosia          #+#    #+#             */
/*   Updated: 2019/02/01 12:20:44 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void	plot_extremes_low(t_coord2 c1, t_coord2 c2, t_fract *fract, int color)
{
	t_coord2	pxl;
	t_fcoord2	d;
	t_fcoord2	end;
	float		gradient;
	float		xgap;

	d.y = c2.y - c1.y;
	d.x = c2.x - c1.x;
	gradient = d.x == 0 ? 1 : d.y / d.x;
	end.x = (float)round_((float)c1.x);
	end.y = (float)c1.y + gradient * (end.x - (float)c1.x);
	xgap = rfpart((float)c1.x + 0.5);
	pxl.x = end.x;
	pxl.y = ipart(end.y);
	fill_img(new_coord2(pxl.x, pxl.y), fract, color, 1);
	fill_img(new_coord2(pxl.x, pxl.y + 1), fract, color, fpart(end.y) * xgap);
	end.x = (float)round_((float)c2.x);
	end.y = (float)c2.y + gradient * (end.x - (float)c2.x);
	xgap = fpart((float)c2.x + 0.5);
	pxl.x = end.x;
	pxl.y = ipart(end.y);
	fill_img(new_coord2(pxl.x, pxl.y), fract, color, rfpart(end.y) * xgap);
	fill_img(new_coord2(pxl.x, pxl.y + 1), fract, color, fpart(end.y) * xgap);
}

void	plot_extremes_high(t_coord2 c1, t_coord2 c2, t_fract *fract, int color)
{
	t_coord2	pxl;
	t_fcoord2	d;
	t_fcoord2	end;
	float		gradient;
	float		ygap;

	d.y = c2.y - c1.y;
	d.x = c2.x - c1.x;
	gradient = d.y == 0 ? 1 : d.x / d.y;
	end.y = (float)round_(c1.y);
	end.x = (float)c1.x + gradient * (end.y - (float)c1.y);
	ygap = rfpart((float)c1.y + 0.5);
	pxl.y = end.y;
	pxl.x = ipart(end.x);
	fill_img(new_coord2(pxl.x, pxl.y), fract, color, 1);
	fill_img(new_coord2(pxl.x + 1, pxl.y), fract, color, fpart(end.x) * ygap);
	end.y = (float)round_(c2.y);
	end.x = (float)c2.x + gradient * (end.y - c2.y);
	ygap = fpart((float)c2.y + 0.5);
	pxl.y = end.y;
	pxl.x = ipart(end.x);
	fill_img(new_coord2(pxl.x, pxl.y), fract, color, rfpart(end.x) * ygap);
	fill_img(new_coord2(pxl.x + 1, pxl.y), fract, color, fpart(end.x) * ygap);
}

void	plot_line_low_aa(t_coord2 c1, t_coord2 c2, t_fract *fract, int color)
{
	t_fcoord2	d;
	int			xpxl1;
	int			xpxl2;
	float		intery;
	float		gradient;

	d.y = c2.y - c1.y;
	d.x = c2.x - c1.x;
	if (d.x == 0)
		gradient = 1.0;
	else
		gradient = d.y / d.x;
	xpxl1 = round_(c1.x);
	xpxl2 = round_(c2.x);
	intery = c1.y + gradient;
	while (xpxl1 < xpxl2)
	{
		fill_img(new_coord2(xpxl1, ipart(intery)), fract, color,
				rfpart(intery));
		fill_img(new_coord2(xpxl1, ipart(intery) + 1), fract, color,
				fpart(intery));
		xpxl1++;
		intery += gradient;
	}
}

void	plot_line_high_aa(t_coord2 c1, t_coord2 c2, t_fract *fract, int color)
{
	t_fcoord2	d;
	int			ypxl1;
	int			ypxl2;
	float		intery;
	float		gradient;

	d.y = c2.y - c1.y;
	d.x = c2.x - c1.x;
	if (d.y == 0)
		gradient = 1.0;
	else
		gradient = d.x / d.y;
	ypxl1 = round_(c1.y);
	ypxl2 = round_(c2.y);
	intery = c1.x + gradient;
	while (ypxl1 < ypxl2)
	{
		fill_img(new_coord2(ipart(intery), ypxl1), fract, color,
				rfpart(intery));
		fill_img(new_coord2(ipart(intery) + 1, ypxl1), fract, color,
				fpart(intery));
		ypxl1++;
		intery += gradient;
	}
}

void	plot_line_aa(t_coord2 c1, t_coord2 c2, t_fract *fract, int color)
{
	if (ft_abs(c2.y - c1.y) < ft_abs(c2.x - c1.x))
		if (c1.x > c2.x)
			plot_line_low_aa(c2, c1, fract, color);
		else
			plot_line_low_aa(c1, c2, fract, color);
	else
	{
		if (c1.y > c2.y)
			plot_line_high_aa(c2, c1, fract, color);
		else
			plot_line_high_aa(c1, c2, fract, color);
	}
}
