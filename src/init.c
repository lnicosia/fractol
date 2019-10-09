/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:13:58 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 14:03:10 by lnicosia         ###   ########.fr       */
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
	fract->mlx_ptr = data->mlx_ptr;
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
		if (!(fract->window.win_ptr = mlx_new_window(data->mlx_ptr, 1024,
						1024, fract->name)))
			return (0);
		if (!(fract->window.img_ptr = mlx_new_image(data->mlx_ptr, 1024,
						1024)))
			return (0);
	}
	fract->window.img.str = (unsigned int*)mlx_get_data_addr(fract->window.
			img_ptr, &(fract->window.img.bit_per_pixels), &(fract->window.
				img.size_line), &(fract->window.img.endian));
	init_hook(fract);
	return (1);
}

void	init_functions(t_env *data)
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
	data->fract_func[9] = &tricorn;
	data->fract_func[10] = &householder;
	data->fract_func[11] = &householder_fail;
	data->fract_func[12] = &householder_fail2;
}

void	init_init_functions(t_env *data)
{
	data->init_func[0] = &init_julia;
	data->init_func[1] = &init_mandelbrot;
	data->init_func[2] = &init_ship;
	data->init_func[3] = &init_buddhabrot;
	data->init_func[4] = &init_burning_julia;
	data->init_func[5] = &init_newton;
	data->init_func[6] = &init_buddha2;
	data->init_func[7] = &init_barnsley;
	data->init_func[8] = &init_koch;
	data->init_func[9] = &init_tricorn;
	data->init_func[10] = &init_householder;
	data->init_func[11] = &init_householder_fail;
	data->init_func[12] = &init_householder_fail2;
}

int		init_fract(t_env *data)
{
	int	i;
	int	j;

	i = 0;
	init_functions(data);
	init_init_functions(data);
	while (i < MAX_FRACT)
	{
		j = 0;
		while (j < MAX_FRACT)
		{
			data->fract[i].fract[j] = &data->fract[j];
			j++;
		}
		data->fract[i].nb = i;
		data->fract[i].state = 0;
		data->fract[i].maj_buffer = 0;
		data->fract[i].func = data->fract_func[i];
		data->fract[i].init_func = data->init_func[i];
		i++;
	}
	return (0);
}
