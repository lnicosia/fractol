/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:43:44 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 14:03:22 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		usage(void)
{
	ft_printf("usage: ./fractol julia | mandelbrot | ship | buddhabrot");
	ft_printf("| buddha2 | bjulia | newton | barnsley | koch | tricorn");
	ft_printf("| householder | householder_fail | householder_fail2\n");
	return (-1);
}

int		parse_arg2(char **av, t_env *data, int i)
{
	if (ft_strequ(av[i], "koch"))
		data->args[8] = 1;
	else if (ft_strequ(av[i], "tricorn"))
		data->args[9] = 1;
	else if (ft_strequ(av[i], "householder"))
		data->args[10] = 1;
	else if (ft_strequ(av[i], "householder_fail"))
		data->args[11] = 1;
	else if (ft_strequ(av[i], "householder_fail2"))
		data->args[12] = 1;
	else
		return (-1);
	return (0);
}

int		parse_arg(char **av, t_env *data, int i)
{
	if (ft_strequ(av[i], "julia"))
		data->args[0] = 1;
	else if (ft_strequ(av[i], "mandelbrot"))
		data->args[1] = 1;
	else if (ft_strequ(av[i], "ship"))
		data->args[2] = 1;
	else if (ft_strequ(av[i], "buddhabrot"))
		data->args[3] = 1;
	else if (ft_strequ(av[i], "bjulia"))
		data->args[4] = 1;
	else if (ft_strequ(av[i], "newton"))
		data->args[5] = 1;
	else if (ft_strequ(av[i], "buddha2"))
		data->args[6] = 1;
	else if (ft_strequ(av[i], "barnsley"))
		data->args[7] = 1;
	else
		return (parse_arg2(av, data, i));
	return (0);
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
		if (parse_arg(av, data, i))
			return (usage());
		i++;
	}
	return (0);
}


__attribute__((destructor)) void leaks(void)
{
	ft_printf("Checking leaks after main\n");
	while (1);
}


int		main(int ac, char **av)
{
	t_env	data;
	int		i;

	if (ac < 2)
		return (usage());
	ft_bzero(&data, sizeof(t_env));
	if (init_fract(&data))
		return (-1);
	if (parse_args(av, &data))
		return (0);
	if (!(data.mlx_ptr = mlx_init()))
		return (-1);
	i = -1;
	while (++i < MAX_FRACT)
	{
		if (data.args[i])
		{
			if (data.init_func[i](&data.fract[i]))
				return (-1);
			init_window(&data.fract[i], &data);
			data.fract_func[i](&data.fract[i]);
			data.fract[i].state = 1;
		}
	}
	ft_printf("launching..\n");
	mlx_loop(data.mlx_ptr);
	return (0);
}
