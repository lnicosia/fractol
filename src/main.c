/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:43:44 by lnicosia          #+#    #+#             */
/*   Updated: 2019/02/26 14:16:48 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"
#include "hook.h"
#include <stdio.h>

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

int		init_data(t_env *data, int i, const char *title)
{
	if (!(data->mlx_ptr = mlx_init()))
		return (0);
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr, data->config.s_width,
					data->config.s_height, title)))
		return (0);
	if (!(data->img_ptr = mlx_new_image(data->mlx_ptr, data->config.s_width,
					data->config.s_height)))
		return (0);
	data->img.str = (unsigned int*)mlx_get_data_addr(data->img_ptr,
			&(data->img.bit_per_pixels), &(data->img.size_line),
			&(data->img.endian));
	init_hook(data);
	mlx_loop(data.mlx_ptr);
	return (1);
}

int		usage(void)
{
	printf("usage: ./fractol julia | mandelbrot | ship\n");
	return (-1);
}

int		parse_args(char **av, t_env *data)
{
	int	i;
	int	args[MAX_FRACT];

	i = 1;
	while (av[i])
	{
		if (ft_strequ(av[1], "julia"))
		{
			if (args[0])
			{
				if (init_data(data, 0, "[Julia]") == 0)
					return (0);
				args[0] = 1;
			}
		}
		else if (ft_strequ(av[1], "mandelbrot"))
		{
			if (args[1])
			{
				if (init_data(data, 0, "[Mandelbrot]") == 0)
					return (0);
				args[1] = 1;
			}
		}
		i++;
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_env	data[MAX_FRACT];

	if (ac < 2)
		return (usage());
	else
	{
		data.config.s_width = 1920;
		data.config.s_height = 1080;
		if (parse_args(av, &data) == 0)
			return (-1);
	}
	return (0);
}
