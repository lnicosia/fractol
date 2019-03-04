/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 12:12:19 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/04 13:39:52 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	quit(t_env *data)
{
	ft_putendl("[ESCAPE]");
	(void)data;
	/*mlx_destroy_image(fract->mlx_ptr, fract->window.img_ptr);
	mlx_destroy_window(fract->mlx_ptr, fract->window.win_ptr);*/
	exit(0);
}

int		close_window(void *param)
{
	t_env	*data;

	data = (t_env*)param;
	ft_putendl("[CLOSE]");
	quit(data);
	return (0);
}
