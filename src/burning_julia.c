/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:31:16 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/12 11:37:04 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void		init_burning_julia(t_fract *fract)
{
	fract->nb = 4;
	fract->movement = 0;
	fract->color_base = RED;
	fract->color_mode = FLAT;
	fract->name = "Burning Julia";
	fract->zoom = 400;
	fract->iter_max = 64;
	fract->max.x = 1.2;
	fract->min.x = -2.25;
	fract->min.y = -1.4;
	fract->max.y = 2.5;
	fract->move.x = 0;
	fract->move.y = 0;
	fract->transfo.x = 0;
	fract->transfo.y = 0;
}

static void	*calc_julia(void *param)
{
	int			x;
	int			y;
	double		xtemp;
	t_fcoord2	z;
	t_fract		*fract;

	fract = (t_fract*)param;
	y = fract->start;
	while (y < fract->end)
	{
		x = 0;
		while (x < 1920)
		{
			z.x = x / fract->zoom + fract->min.x + fract->move.x;
			z.y = y / fract->zoom + fract->min.y + fract->move.y;
			fract->iter = 0;
			while (z.x * z.x + z.y * z.y < 4
					&& fract->iter < fract->iter_max)
			{
				xtemp = z.x * z.x - z.y * z.y;
				z.y = fabs(2 * z.x * z.y + 0.01 + fract->transfo.x);
				z.x = fabs(xtemp + 0.285 + fract->transfo.y);
				fract->iter++;
			}
			if (fract->iter == fract->iter_max)
				fract->window.img.str[x + 1920 * y] = 0;
			else
				color(x, y, fract);
			x++;
		}
		y++;
	}
	return (NULL);
}

void		burning_julia(t_fract *fract)
{
	pthread_t	thread[8];
	t_fract		julia[8];
	int			i;

	i = 0;
	while (i < 8)
	{
		ft_memcpy(&julia[i], fract, sizeof(t_fract));
		julia[i].end = 1080 / 8 * (i + 1);
		julia[i].start = 1080 / 8 * i;
		pthread_create(&thread[i], NULL, calc_julia, &julia[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
}