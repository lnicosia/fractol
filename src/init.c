/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:13:58 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/04 13:47:44 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"
#include "hook.h"
#include <stdio.h>

void	init_hook(t_fract *fract, t_env *data)
{
	mlx_hook(fract->window.win_ptr, KEYPRESS, KEYPRESSMASK, key_press,
			data);
	mlx_hook(fract->window.win_ptr, KEYRELEASE, KEYRELEASE, key_release,
			data);
	mlx_hook(fract->window.win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK,
			close_window,
			data);
	mlx_hook(fract->window.win_ptr, BUTTONPRESS, BUTTONPRESSMASK, mouse_press,
			data);
	mlx_hook(fract->window.win_ptr, BUTTONRELEASE, BUTTONRELEASEMASK,
			mouse_release, data);
	mlx_hook(fract->window.win_ptr, MOTIONNOTIFY, BUTTON1MOTIONMASK,
			mouse_move, data);
}

int		init_window(t_fract *fract, t_env *data, char *title)
{
	if (!(fract->window.win_ptr = mlx_new_window(data->mlx_ptr, data->s_width,
					data->s_height, title)))
		return (0);
	if (!(fract->window.img_ptr = mlx_new_image(data->mlx_ptr, data->s_width,
					data->s_height)))
		return (0);
	fract->window.img.str = (unsigned int*)mlx_get_data_addr(fract->window.
			img_ptr, &(fract->window.img.bit_per_pixels), &(fract->window.
				img.size_line), &(fract->window.img.endian));
	init_hook(fract, data);
	return (1);
}

int		init_fract(t_env *data)
{
	if (!(data->mlx_ptr = mlx_init()))
		return (0);
	data->fract_func[0] = &julia;
	data->fract_func[1] = &mandelbrot;
	data->fract_func[2] = &ship;
	data->fract[0].mlx_ptr = data->mlx_ptr;
	data->fract[1].mlx_ptr = data->mlx_ptr;
	data->fract[2].mlx_ptr = data->mlx_ptr;
	data->titles[0] = "[Julia]";
	data->titles[1] = "[Mandelbrot]";
	data->titles[2] = "[Burning ship]";
	return (1);
}
