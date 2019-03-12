/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:43:44 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/12 11:25:05 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		usage(void)
{
	ft_printf("usage: ./fractol julia | mandelbrot | ship | buddhabrot");
	ft_printf("| bjulia\n");
	exit(0);
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
		else if (ft_strequ(av[i], "buddhabrot"))
		{
			if (!data->args[3])
				data->args[3] = 1;
		}
		else if (ft_strequ(av[i], "bjulia"))
		{
			if (!data->args[4])
				data->args[4] = 1;
		}
		else
			usage();
		i++;
	}
}

int		main(int ac, char **av)
{
	t_env	data;
	int		i;

	if (ac < 2)
		usage();
	else
	{
		if (init_fract(&data) == 0)
			return (-1);
		parse_args(av, &data);
		i = 0;
		while (i < MAX_FRACT)
		{
			if (data.args[i])
			{
				data.init_fract[i](&data.fract[i]);
				init_window(&data.fract[i], &data);
				data.fract_func[i](&data.fract[i]);
			}
			i++;
		}
	}
	ft_printf("launching..\n");
	mlx_loop(data.mlx_ptr);
	return (0);
}
