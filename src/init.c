/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:13:58 by lnicosia          #+#    #+#             */
/*   Updated: 2019/02/27 16:36:27 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"
#include "hook.h"

void	init_hook(t_env *data, int i)
{
	mlx_hook(data->win_ptr[i], KEYPRESS, KEYPRESSMASK, key_press, data);
	mlx_hook(data->win_ptr[i], KEYRELEASE, KEYRELEASE, key_release, data);
	mlx_hook(data->win_ptr[i], DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_window,
			data);
	mlx_hook(data->win_ptr[i], BUTTONPRESS, BUTTONPRESSMASK, mouse_press, data);
	mlx_hook(data->win_ptr[i], BUTTONRELEASE, BUTTONRELEASEMASK, mouse_release,
			data);
	mlx_hook(data->win_ptr[i], MOTIONNOTIFY, BUTTON1MOTIONMASK, mouse_move, data);
}

int		init_window(t_env *data, int i, char *title)
{
	if (!(data->mlx_ptr[i] = mlx_init()))
		return (0);
	if (!(data->win_ptr[i] = mlx_new_window(data->mlx_ptr[i], data->config.s_width,
					data->config.s_height, title)))
		return (0);
	if (!(data->img_ptr[i] = mlx_new_image(data->mlx_ptr[i], data->config.s_width,
					data->config.s_height)))
		return (0);
	data->img[i].str = (unsigned int*)mlx_get_data_addr(data->img_ptr[i],
			&(data->img[i].bit_per_pixels), &(data->img[i].size_line),
			&(data->img[i].endian));
	init_hook(data, i);
	mlx_loop(data->mlx_ptr[i]);
	return (1);
}

void	init_fract(t_env *data)
{
	data->fractal[0] = &julia;
	data->fractal[1] = &mandelbrot;
}
