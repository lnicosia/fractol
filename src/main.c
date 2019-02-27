/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:43:44 by lnicosia          #+#    #+#             */
/*   Updated: 2019/02/27 17:07:29 by lnicosia         ###   ########.fr       */
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
		if (ft_strequ(av[1], "julia"))
		{
			if (!data->args[0])
				data->args[0] = 1;
		}
		else if (ft_strequ(av[1], "mandelbrot"))
		{
			if (!data->args[1])
				data->args[1] = 1;
		}
		i++;
	}
}

void	launch_fract(t_env *data)
{
	int	i;

	i = 0;
	while (i < MAX_FRACT)
	{
		if (data->args[i])
		{
			printf("Launching %d\n", i);
			data->fractal[i](data);
		}
		i++;
	}
}

int		main(int ac, char **av)
{
	t_env	data[MAX_FRACT];

	if (ac < 2)
		return (usage());
	else
	{
		init_fract(&data);
		data.config.s_width = 1920;
		data.config.s_height = 1080;
		parse_args(av, &data);
	}
	launch_fract(&data);
	return (0);
}
