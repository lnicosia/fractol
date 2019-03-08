/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 12:12:19 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/08 11:58:24 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	quit(t_fract *fract)
{
	ft_putendl("[ESCAPE]");
	(void)fract;
	exit(0);
}

int		close_window(void *param)
{
	t_fract	*fract;

	fract = (t_fract*)param;
	ft_putendl("[CLOSE]");
	quit(fract);
	return (0);
}
