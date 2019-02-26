/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:52:33 by lnicosia          #+#    #+#             */
/*   Updated: 2019/02/26 12:32:14 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"
#include "hook.h"

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
	(void)x;
	(void)y;
	(void)param;
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
