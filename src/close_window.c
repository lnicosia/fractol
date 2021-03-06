/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 12:12:19 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 14:01:24 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	check_windows(t_fract *fract)
{
	int	i;

	i = 0;
	while (i < MAX_FRACT)
	{
		if (fract->fract[i]->state == 1)
			return ;
		i++;
	}
	exit(0);
}

void		free_all(t_fract *fract)
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

void		quit(t_fract *fract)
{
	ft_putendl("[ESCAPE]");
	free_all(fract);
	exit(0);
}

int			close_window(void *param)
{
	t_fract	*fract;

	fract = (t_fract*)param;
	ft_putendl("[CLOSE]");
	mlx_destroy_image(fract->mlx_ptr, fract->window.img_ptr);
	mlx_destroy_window(fract->mlx_ptr, fract->window.win_ptr);
	if (fract->red)
		ft_memdel((void**)&fract->red);
	if (fract->green)
		ft_memdel((void**)&fract->green);
	if (fract->blue)
		ft_memdel((void**)&fract->blue);
	if (fract->red)
		ft_memdel((void**)&fract->red);
	if (fract->green)
		ft_memdel((void**)&fract->green);
	if (fract->blue)
		ft_memdel((void**)&fract->blue);
	fract->state = 0;
	check_windows(fract);
	return (0);
}
