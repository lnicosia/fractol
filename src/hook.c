/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:52:33 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/05 14:24:56 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"
#include "hook.h"
#include <stdio.h>

int		key_release(int key, void *param)
{
	t_env	*data;

	data = (t_env*)param;
	if (key == ESC_KEY)
		quit(data);
	return (0);
}

int		key_press(int key, void *param)
{
	t_env	*data;
	int		i;

	i = 0;
	data = (t_env*)param;
	if (key == UP_KEY)
		data->move.y += 0.1 / (double)data->zoom.x;
	if (key == DOWN_KEY)
		data->move.y -= 0.1 / (double)data->zoom.x;
	if (key == LEFT_KEY)
		data->move.x += 0.1 / (double)data->zoom.x;
	if (key == RIGHT_KEY)
		data->move.x -= 0.1 / (double)data->zoom.x;
	while (i < MAX_FRACT)
	{
		if (data->args[i])
			data->fract_func[i](data);
		i++;
	}
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_env	*data;
	int		i;

	data = (t_env*)param;
	i = 0;
	if (data->movement)
	{
		data->transfo.x = (double)x / (double)data->s_width;
		data->transfo.y = (double)y / (double)data->s_height;
		while (i < MAX_FRACT)
		{
			if (data->args[i])
				data->fract_func[i](data);
			i++;
		}
	}
	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_env	*data;
	int	i;

	i = 0;
	data = (t_env*)param;
	if (button == SCROLLUP_KEY)
	{
		data->center.x = x;
		data->center.y = y;
		data->zoom.x *= 1.5;
	}
	else if (button == SCROLLDOWN_KEY)
	{
		if (data->zoom.x > 1)
		{
			data->center.x = x;
			data->center.y = y;
			data->zoom.x /= 1.5;
		}
	}
	while (i < MAX_FRACT)
	{
		if (data->args[i])
			data->fract_func[i](data);
		i++;
	}
	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_env	*data;

	data = (t_env*)param;
	(void)x;
	(void)y;
	if (button == BUT1_KEY)
		data->movement = data->movement ? 0 : 1;
	return (0);
}
