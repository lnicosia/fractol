/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:35:25 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 15:39:13 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"

void	key_release3(int key, t_fract *fract)
{
	if (key == NKMN_KEY)
	{
		if (fract->ctrl_buffer)
		{
			if (fract->pow > 0)
				fract->pow--;
			fract->a -= fract->a > 0 ? 0.1 : 0;
			if (fract->sample > 0)
				fract->sample /= 10;
		}
		else
		{
			if (fract->maj_buffer)
			{
				if (fract->iter_max > fract->maj_incr)
					fract->iter_max -= fract->maj_incr;
			}
			else
			{
				if (fract->iter_max > fract->incr)
					fract->iter_max -= fract->incr;
			}
		}
		fract->func(fract);
	}
}

void	key_release2(int key, t_fract *fract)
{
	if (key == NKPL_KEY)
	{
		if (fract->ctrl_buffer)
		{
			if (fract->pow < 20)
				fract->pow++;
			if (fract->a < 2)
				fract->a += 0.1;
			if (fract->sample < 1000000000000)
				fract->sample *= 10;
		}
		else
		{
			if (fract->maj_buffer)
				fract->iter_max += fract->maj_incr;
			else
				fract->iter_max += fract->incr;
		}
		fract->func(fract);
	}
	key_release3(key, fract);
}

int		reset(int key, t_fract *fract)
{
	if (key == R_KEY)
	{
		if (fract->red)
			ft_memdel((void**)&fract->red);
		if (fract->green)
			ft_memdel((void**)&fract->green);
		if (fract->blue)
			ft_memdel((void**)&fract->blue);
		if (fract->init_func(fract))
			return (-1);
		fract->func(fract);
	}
	return (0);
}

int		key_release(int key, void *param)
{
	t_fract	*fract;

	fract = (t_fract*)param;
	if (key == ESC_KEY)
		free_all(fract);
	if (key == E_KEY)
	{
		if (export_fdf(*fract))
		{
			ft_printf("Could not export\n");
			return (-1);
		}
	}
	if (key >= K1_KEY && key <= K0_KEY)
		swap_color_base(key, fract);
	if (key >= NK0_KEY && key <= NK9_KEY)
		swap_color_mode(key, fract);
	if (key == LSFT_KEY || key == RSFT_KEY)
		fract->maj_buffer = 0;
	if (key == LCTRL_KEY || key == RCTRL_KEY)
		fract->ctrl_buffer = 0;
	key_release2(key, fract);
	if (reset(key, fract))
		return (-1);
	return (0);
}
