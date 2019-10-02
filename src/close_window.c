/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 12:12:19 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/02 12:00:37 by lnicosia         ###   ########.fr       */
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

static void	close_all_windows(t_fract *fract)
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
		free(fract->fract[3]->red);
	if (fract->fract[3]->green)
		free(fract->fract[3]->green);
	if (fract->fract[3]->blue)
		free(fract->fract[3]->blue);
	if (fract->fract[6]->red)
		free(fract->fract[6]->red);
	if (fract->fract[6]->green)
		free(fract->fract[6]->green);
	if (fract->fract[6]->blue)
		free(fract->fract[6]->blue);
	exit(0);
}

void		quit(t_fract *fract)
{
	ft_putendl("[ESCAPE]");
	close_all_windows(fract);
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
		free(fract->red);
	if (fract->green)
		free(fract->green);
	if (fract->blue)
		free(fract->blue);
	fract->state = 0;
	check_windows(fract);
	return (0);
}
