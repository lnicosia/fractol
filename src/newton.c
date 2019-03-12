/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:50:42 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/12 14:01:01 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_newton(t_fract *fract)
{
	fract->nb = 5;
	fract->color_base = WHITE;
	fract->color_mode = FLAT;
	fract->name = "Newton";
	fract->zoom = 400;
	fract->iter_max = 64;
	fract->max.x = 0.6;
	fract->max.y = 1.2;
	fract->min.x = -2.0;
	fract->min.y = -2.0;
	fract->move.x = 0;
	fract->move.y = 0;
}

static void	*calc_newton(void *param)
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
				z.y = 2 * z.x * z.y;
				z.x = xtemp;
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

void		newton(t_fract *fract)
{
	pthread_t	thread[8];
	t_fract		newton[8];
	int			i;

	i = 0;
	while (i < 8)
	{
		ft_memcpy(&newton[i], fract, sizeof(t_fract));
		newton[i].end = 1080 / 8 * (i + 1);
		newton[i].start = 1080 / 8 * i;
		pthread_create(&thread[i], NULL, calc_newton, &newton[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
}
