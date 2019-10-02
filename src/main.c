/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:43:44 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/02 18:00:43 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		usage(void)
{
	ft_printf("usage: ./fractol julia | mandelbrot | ship | buddhabrot");
	ft_printf("| buddha2 | bjulia | newton | barnsley | koch | tricorn\n");
	return (-1);
}

int		parse_arg2(char **av, t_env *data, int i)
{
	if (ft_strequ(av[i], "bjulia"))
	{
		if (!data->args[4])
			data->args[4] = 1;
	}
	else if (ft_strequ(av[i], "newton"))
	{
		if (!data->args[5])
			data->args[5] = 1;
	}
	else if (ft_strequ(av[i], "buddha2"))
	{
		if (!data->args[6])
			data->args[6] = 1;
	}
	else if (ft_strequ(av[i], "barnsley"))
	{
		if (!data->args[7])
			data->args[7] = 1;
	}
	else
		return (0);
	return (1);
}

int		parse_arg(char **av, t_env *data, int i)
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
	else
		return (parse_arg2(av, data, i));
	return (1);
}

int		parse_args(char **av, t_env *data)
{
	int	i;

	i = -1;
	while (++i < MAX_FRACT)
		data->args[i] = 0;
	i = 1;
	while (av[i])
	{
		if (!parse_arg(av, data, i))
		{
			if (ft_strequ(av[i], "koch"))
			{
				if (!data->args[8])
					data->args[8] = 1;
			}
			if (ft_strequ(av[i], "tricorn"))
			{
				if (!data->args[9])
					data->args[9] = 1;
			}
			else
				return (usage());
		}
		i++;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_env	data;
	int		i;

	if (ac < 2)
		return (usage());
	if (init_fract(&data) == 0)
		return (-1);
	if (parse_args(av, &data))
		return (0);
	i = 0;
	while (i < MAX_FRACT)
	{
		if (data.args[i])
		{
			data.init_func[i](&data.fract[i]);
			init_window(&data.fract[i], &data);
			data.fract_func[i](&data.fract[i]);
		}
		else
			data.fract[i].state = 0;
		i++;
	}
	ft_printf("launching..\n");
	mlx_loop(data.mlx_ptr);
	return (0);
}
