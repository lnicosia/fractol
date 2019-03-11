/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:13:58 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/11 12:20:22 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"
#include "hook.h"

void	init_hook(t_fract *fract)
{
	mlx_hook(fract->window.win_ptr, KEYPRESS, KEYPRESSMASK, key_press,
			fract);
	mlx_hook(fract->window.win_ptr, KEYRELEASE, KEYRELEASE, key_release,
			fract);
	mlx_hook(fract->window.win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK,
			close_window,
			fract);
	mlx_hook(fract->window.win_ptr, BUTTONPRESS, BUTTONPRESSMASK, mouse_press,
			fract);
	mlx_hook(fract->window.win_ptr, BUTTONRELEASE, BUTTONRELEASEMASK,
			mouse_release, fract);
	mlx_hook(fract->window.win_ptr, MOTIONNOTIFY, BUTTON1MOTIONMASK,
			mouse_move, fract);
}

int		init_window(t_fract *fract, t_env *data)
{
	if (ft_strequ(fract->name, "Buddhabrot"))
	{
		if (!(fract->window.win_ptr = mlx_new_window(data->mlx_ptr, 1024,
						1024, fract->name)))
			return (0);
		if (!(fract->window.img_ptr = mlx_new_image(data->mlx_ptr, 1024,
						1024)))
			return (0);
	}
	else
	{
		if (!(fract->window.win_ptr = mlx_new_window(data->mlx_ptr, 1920,
						1080, fract->name)))
			return (0);
		if (!(fract->window.img_ptr = mlx_new_image(data->mlx_ptr, 1920,
						1080)))
			return (0);
	}
	fract->window.img.str = (unsigned int*)mlx_get_data_addr(fract->window.
			img_ptr, &(fract->window.img.bit_per_pixels), &(fract->window.
				img.size_line), &(fract->window.img.endian));
	init_hook(fract);
	return (1);
}

int		init_fract(t_env *data)
{
	if (!(data->mlx_ptr = mlx_init()))
		return (0);
	data->fract_func[0] = &julia;
	data->fract_func[1] = &mandelbrot;
	data->fract_func[2] = &ship;
	data->fract_func[3] = &buddhabrot;
	data->fract[0].func = &julia;
	data->fract[1].func = &mandelbrot;
	data->fract[2].func = &ship;
	data->fract[3].func = &buddhabrot;
	data->init_fract[0] = &init_julia;
	data->init_fract[1] = &init_mandelbrot;
	data->init_fract[2] = &init_ship;
	data->init_fract[3] = &init_buddhabrot;
	data->fract[0].mlx_ptr = data->mlx_ptr;
	data->fract[1].mlx_ptr = data->mlx_ptr;
	data->fract[2].mlx_ptr = data->mlx_ptr;
	data->fract[3].mlx_ptr = data->mlx_ptr;
	return (1);
}
