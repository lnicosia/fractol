/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:52:33 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/04 12:26:31 by lnicosia         ###   ########.fr       */
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
	(void)key;
	(void)param;
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_env	*data;

	data = (t_env*)param;
	printf("[%d][%d]\n", y, x);
	data->move.x = (double)x / (double)data->s_width;
	data->move.y = (double)y / (double)data->s_height;
	printf("move.x = %f move.y = %f\n", data->move.x, data->move.y);
	printf("julia\n");
	//julia(data);
	return (0);
}

int		mouse_press(int x, int y, void *param)
{
	(void)x;
	(void)y;
	(void)param;
	return (0);
}

int		mouse_release(int x, int y, void *param)
{
	(void)x;
	(void)y;
	(void)param;
	return (0);
}
