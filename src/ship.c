/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:23:51 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/14 11:23:52 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void		init_ship(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = FLAT;
	fract->name = "Burning ship";
	fract->zoom = 12500;
	fract->iter_max = 150;
	fract->max.x = -1.76;
	fract->max.y = 1.075;
	fract->min.x = -1.840;
	fract->min.y = -0.075;
}

static void	*calc_ship(void *param)
{
	int			x;
	int			y;
	double		xtemp;
	t_fcoord2	z;
	t_fcoord2	c;
	t_fract		*fract;

	fract = (t_fract*)param;
	y = fract->start;
	while (y < fract->end)
	{
		x = 0;
		while (x < 1920)
		{
			c.x = x / fract->zoom + fract->min.x + fract->move.x;
			c.y = y / fract->zoom + fract->min.y + fract->move.y;
			z.x = 0;
			z.y = 0;
			fract->iter = 0;
			while (z.x * z.x + z.y * z.y < 4
					&& fract->iter < fract->iter_max)
			{
				xtemp = z.x * z.x - z.y * z.y;
				z.y = fabs(2 * z.x * z.y + c.y);
				z.x = fabs(xtemp + c.x);
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

void		ship(t_fract *fract)
{
	pthread_t	thread[8];
	t_fract		ship[8];
	int			i;

	i = 0;
	while (i < 8)
	{
		ft_memcpy(&ship[i], fract, sizeof(t_fract));
		ship[i].end = 1080 / 8 * (i + 1);
		ship[i].start = 1080 / 8 * i;
		pthread_create(&thread[i], NULL, calc_ship, &ship[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
}
