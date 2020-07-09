/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:52:33 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 11:44:47 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"
#include "hook.h"

void	key_press2(int key, t_fract *fract)
{
	if (key == RIGHT_KEY)
	{
		fract->move.x -= 100 / (double)fract->zoom;
		fract->func(fract);
	}
	if (key == LSFT_KEY || key == RSFT_KEY)
		fract->maj_buffer = 1;
	if (key == LCTRL_KEY || key == RCTRL_KEY)
		fract->ctrl_buffer = 1;
}

int		key_press(int key, void *param)
{
	t_fract	*fract;

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
	key_press2(key, fract);
	return (0);
}
