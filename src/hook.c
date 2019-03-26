/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:52:33 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/26 13:58:49 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"
#include "hook.h"

int		key_release(int key, void *param)
{
	t_fract	*fract;

	fract = (t_fract*)param;
	if (key == ESC_KEY)
		quit(fract);
	if (key == E_KEY)
		export_fdf(*fract);
	if (key >= K1_KEY && key <= K0_KEY)
		swap_color_base(key, fract);
	if (key >= NK0_KEY && key <= NK9_KEY)
		swap_color_mode(key, fract);
	if (key == NKPL_KEY)
	{
		if (fract->ctrl_buffer)
		{
			if (fract->maj_buffer && fract->iter_min < 2147483642)
				fract->iter_min += 5;
			else if (fract->iter_max < 2147483646)
				fract->iter_min += 1;
		}
		else
		{
			if (fract->maj_buffer && fract->iter_max < 2147483607)
				fract->iter_max += fract->nb != 8 ? 40: 0;
			else if (fract->iter_max < 2147483643)
				fract->iter_max += fract->nb == 8 ? 1 : 4;
		}
		fract->func(fract);
	}
	if (key == NKMN_KEY)
	{
		if (fract->ctrl_buffer)
		{
			if (fract->maj_buffer && fract->iter_min > 4)
				fract->iter_min -= 5;
			else if (fract->iter_min > 0)
				fract->iter_min -= 1;
		}
		else
		{
			if (fract->maj_buffer && fract->iter_max > 40)
				fract->iter_max -= fract->nb != 8 ? 40 : 0;
			else if (fract->iter_max > 4
					|| (fract->nb == 8 && fract->iter_max > 0))
				fract->iter_max -= fract->nb == 8 ? 1 : 4;
		}
		fract->func(fract);
	}
	if (key == LSFT_KEY || key == RSFT_KEY)
		fract->maj_buffer = 0;
	if (key == LCTRL_KEY || key == RCTRL_KEY)
		fract->ctrl_buffer = 0;
	return (0);
}

int		key_press(int key, void *param)
{
	t_fract	*fract;
	int		i;

	i = 0;
	fract = (t_fract*)param;
	if (key == UP_KEY)
	{
		fract->move.y += 100 / (double)fract->zoom;
		fract->func(fract);
	}
	if (key == DOWN_KEY)
	{
		fract->move.y -= 100 / (double)fract->zoom;
		fract->func(fract);
	}
	if (key == LEFT_KEY)
	{
		fract->move.x += 100 / (double)fract->zoom;
		fract->func(fract);
	}
	if (key == RIGHT_KEY)
	{
		fract->move.x -= 100 / (double)fract->zoom;
		fract->func(fract);
	}
	if (key == LSFT_KEY || key == RSFT_KEY)
		fract->maj_buffer = 1;
	if (key == LCTRL_KEY || key == RCTRL_KEY)
		fract->ctrl_buffer = 1;
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_fract	*fract;
	int		i;

	fract = (t_fract*)param;
	i = 0;
	if (fract->movement && fract->nb != 3)
	{
		fract->transfo.x = (double)x / 1920.0;
		fract->transfo.y = (double)y / 1080.0;
		fract->func(fract);
	}
	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_fract	*fract;
	int		i;

	i = 0;
	fract = (t_fract*)param;
	if (button == SCROLLUP_KEY && fract->iter_max < 2147483643)
	{
		//if (fract->nb != 3 && fract->nb != 6)
		//{
		fract->min.x = (x / fract->zoom + fract->min.x)
			- (x / (fract->zoom * 1.5));
		fract->min.y = (y / fract->zoom + fract->min.y)
			- (y / (fract->zoom * 1.5));
		/*}
		  else
		  {
		  fract->min.y = (x / fract->zoom + fract->min.x)
		  - (x / (fract->zoom * 1.5));
		  fract->min.x = (y / fract->zoom + fract->min.y)
		  - (y / (fract->zoom * 1.5));
		  }*/
		fract->zoom *= 1.5;
		fract->iter_max += fract->nb == 8 ? 0 : 1;
		fract->func(fract);
	}
	else if (button == SCROLLDOWN_KEY && (fract->iter_max > 4
				|| fract->nb == 8))
	{
		if ((fract->zoom > 3 && fract->iter_max > 4)
				|| fract->nb == 8)
		{
			//if (fract->nb != 3 && fract->nb != 6)
			//{
			fract->min.x = (x / fract->zoom + fract->min.x)
				- (x / (fract->zoom / 1.5));
			fract->min.y = (y / fract->zoom + fract->min.y)
				- (y / (fract->zoom / 1.5));
			//}
			/*else
			  {
			  fract->min.y = (x / fract->zoom + fract->min.x)
			  - (x / (fract->zoom / 1.5));
			  fract->min.x = (y / fract->zoom + fract->min.y)
			  - (y / (fract->zoom / 1.5));
			  }*/
			fract->zoom /= 1.5;
			fract->iter_max -= fract->nb == 8 ? 0 : 1;
			fract->func(fract);
		}
	}
	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_fract	*fract;

	fract = (t_fract*)param;
	(void)x;
	(void)y;
	if (button == BUT1_KEY)
		fract->movement = fract->movement ? 0 : 1;
	return (0);
}
