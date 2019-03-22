/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:13:58 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/22 18:48:40 by lnicosia         ###   ########.fr       */
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
	if (ft_strequ(fract->name, "Buddhabrot")
			|| ft_strequ(fract->name, "Random buddhabrot"))
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

void	init_fract1(t_env *data)
{
	data->fract_func[0] = &julia;
	data->fract_func[1] = &mandelbrot;
	data->fract_func[2] = &ship;
	data->fract_func[3] = &buddhabrot;
	data->fract_func[4] = &burning_julia;
	data->fract_func[5] = &newton;
	data->fract_func[6] = &buddha2;
	data->fract_func[7] = &barnsley;
	data->fract_func[8] = &koch;
}

void	init_fract2(t_env *data)
{
	data->init_fract[0] = &init_julia;
	data->init_fract[1] = &init_mandelbrot;
	data->init_fract[2] = &init_ship;
	data->init_fract[3] = &init_buddhabrot;
	data->init_fract[4] = &init_burning_julia;
	data->init_fract[5] = &init_newton;
	data->init_fract[6] = &init_buddha2;
	data->init_fract[7] = &init_barnsley;
	data->init_fract[8] = &init_koch;
}

int		init_fract(t_env *data)
{
	int	i;
	int	j;

	i = 0;
	if (!(data->mlx_ptr = mlx_init()))
		return (0);
	init_fract1(data);
	init_fract2(data);
	while (i < MAX_FRACT)
	{
		j = 0;
		while (j < MAX_FRACT)
		{
			data->fract[i].fract[j] = &data->fract[j];
			j++;
		}
		data->fract[i].nb = i;
		data->fract[i].state = 1;
		data->fract[i].maj_buffer = 0;
		data->fract[i].func = data->fract_func[i];
		data->fract[i].mlx_ptr = data->mlx_ptr;
		i++;
	}
	return (1);
}
