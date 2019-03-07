/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:52:33 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/07 15:02:41 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"
#include "hook.h"
#include <stdio.h>

int		key_release(int key, void *param)
{
	t_fract	*fract;

	fract = (t_fract*)param;
	if (key == ESC_KEY)
		quit(fract);
	return (0);
}

int		key_press(int key, void *param)
{
	t_fract	*fract;
	int		i;

	i = 0;
	fract = (t_fract*)param;
	if (key == UP_KEY)
		fract->move.y += 0.1 / (double)fract->zoom.x;
	if (key == DOWN_KEY)
		fract->move.y -= 0.1 / (double)fract->zoom.x;
	if (key == LEFT_KEY)
		fract->move.x += 0.1 / (double)fract->zoom.x;
	if (key == RIGHT_KEY)
		fract->move.x -= 0.1 / (double)fract->zoom.x;
	fract->func(fract);
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_fract	*fract;
	int		i;

	fract = (t_fract*)param;
	i = 0;
	if (fract->movement)
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
	int	i;

	i = 0;
	fract = (t_fract*)param;
	(void)x;
	(void)y;
	if (button == SCROLLUP_KEY)
	{
		/*fract->center.x = 4.0 * (x - 960.0) / 1920.0;
		fract->center.y = 4.0 * (y - 540.0) / 1080.0;
		printf("x = %f\n", fract->center.x);
		printf("y = %f\n", fract->center.y);*/
		fract->zoom.x *= 1.5;
	}
	else if (button == SCROLLDOWN_KEY)
	{
		if (fract->zoom.x > 1)
		{
			/*fract->center.x = 4.0 * (x - 960.0) / 1920.0;
			fract->center.y = 4.0 * (y - 540.0) / 1080.0;*/
			fract->zoom.x /= 1.5;
		}
	}
	fract->func(fract);
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
