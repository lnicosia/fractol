/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:43:44 by lnicosia          #+#    #+#             */
/*   Updated: 2019/02/26 12:28:44 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"
#include "hook.h"

void	init_hook(t_env *data)
{
	mlx_hook(data->win_ptr, KEYPRESS, KEYPRESSMASK, key_press, data);
	mlx_hook(data->win_ptr, KEYRELEASE, KEYRELEASE, key_release, data);
	mlx_hook(data->win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_window,
			data);
	mlx_hook(data->win_ptr, BUTTONPRESS, BUTTONPRESSMASK, mouse_press, data);
	mlx_hook(data->win_ptr, BUTTONRELEASE, BUTTONRELEASEMASK, mouse_release,
			data);
	mlx_hook(data->win_ptr, MOTIONNOTIFY, BUTTON1MOTIONMASK, mouse_move, data);
}

int		init_window(t_env *data)
{
	if (!(data->mlx_ptr = mlx_init()))
		return (0);
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr, data->config.s_width,
					data->config.s_height, "Fract'ol")))
		return (0);
	if (!(data->img_ptr = mlx_new_image(data->mlx_ptr, data->config.s_width,
					data->config.s_height)))
		return (0);
	data->img.str = (unsigned int*)mlx_get_data_addr(data->img_ptr,
			&(data->img.bit_per_pixels), &(data->img.size_line),
			&(data->img.endian));
	init_hook(data);
	return (1);
}

int		main(int ac, char **av)
{
	t_env	data;

	(void)ac;
	(void)av;
	data.config.s_width = 1920;
	data.config.s_height = 1080;
	if (init_window(&data) == 0)
		return (-1);
	mlx_loop(data.mlx_ptr);
	return (0);
}
