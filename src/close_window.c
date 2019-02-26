/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 12:12:19 by lnicosia          #+#    #+#             */
/*   Updated: 2019/02/26 12:32:37 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	quit(t_env *data)
{
	ft_putendl("[ESCAPE]");
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}

int		close_window(void *param)
{
	t_env *data;

	data = (t_env*)param;
	ft_putendl("[CLOSE]");
	quit(data);
	return (0);
}
