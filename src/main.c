/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:43:44 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/05 14:18:21 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int		usage(void)
{
	printf("usage: ./fractol julia | mandelbrot | ship\n");
	return (-1);
}

void	parse_args(char **av, t_env *data)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_strequ(av[i], "julia"))
		{
			if (!data->args[0])
				data->args[0] = 1;
		}
		else if (ft_strequ(av[i], "mandelbrot"))
		{
			if (!data->args[1])
				data->args[1] = 1;
		}
		else if (ft_strequ(av[i], "ship"))
		{
			if (!data->args[2])
				data->args[2] = 1;
		}
		else
		{
			usage();
			exit(0);
		}
		i++;
	}
}

int		main(int ac, char **av)
{
	t_env	data;
	int		i;

	if (ac < 2)
		return (usage());
	else
	{
		if (init_fract(&data) == 0)
			return (-1);
		data.s_width = 1920;
		data.s_height = 1080;
		data.move.x = 0.0;
		data.move.y = 0.0;
		data.transfo.x = 0.0;
		data.transfo.y = 0.0;
		data.drag.x = 0;
		data.drag.y = 0;
		data.zoom.x = 1.0;
		data.zoom.y = 1.0;
		data.movement = 0;
		data.center.x = data.s_width / 2;
		data.center.y = data.s_height / 2;
		parse_args(av, &data);
		i = 0;
		while (i < MAX_FRACT)
		{
			if (data.args[i])
			{
				init_window(&data.fract[i], &data, data.titles[i]);
				data.fract_func[i](&data);
			}
			i++;
		}
	}
	printf("launching..\n");
	mlx_loop(data.mlx_ptr);
	return (0);
}
