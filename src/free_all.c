/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 16:59:19 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/02 17:02:47 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	free_all(t_fract *fract)
{
	int	i;

	i = 0;
	while (i < MAX_FRACT)
	{
		if (fract->fract[i]->state == 1)
		{
			mlx_destroy_image(fract->mlx_ptr, fract->fract[i]->window.img_ptr);
			mlx_destroy_window(fract->mlx_ptr, fract->fract[i]->window.win_ptr);
		}
		i++;
	}
	if (fract->fract[3]->red)
		ft_memdel((void**)&fract->fract[3]->red);
	if (fract->fract[3]->green)
		ft_memdel((void**)&fract->fract[3]->green);
	if (fract->fract[3]->blue)
		ft_memdel((void**)&fract->fract[3]->blue);
	if (fract->fract[6]->red)
		ft_memdel((void**)&fract->fract[6]->red);
	if (fract->fract[6]->green)
		ft_memdel((void**)&fract->fract[6]->green);
	if (fract->fract[6]->blue)
		ft_memdel((void**)&fract->fract[6]->blue);
	exit(0);
}

