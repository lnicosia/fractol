/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:29:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/08 18:03:19 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_buddhabrot(t_fract *fract)
{
	fract->nb = 1;
	fract->name = "buddhabrot";
	fract->zoom = 400;
	fract->iter_max = 50;
	fract->max.x = 0.6;
	fract->max.y = 1.2;
	fract->min.x = -2.7;
	fract->min.y = -1.35;
}

static void	*calc_buddhabrot(void *param)
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
				z.y = 2 * z.x * z.y + c.y;
				z.x = xtemp + c.x;
				fract->iter++;
			}
			if (fract->iter == fract->iter_max)
				fract->window.img.str[x + 1920 * y] = 0;
			else
			{
				fract->window.img.str[x + 1920 * y] = 0xFFFFFF
					* (int)(256 * fract->iter / fract->iter_max);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

void		buddhabrot(t_fract *fract)
{
	pthread_t	thread[8];
	t_fract		buddhabrot[8];
	int			i;

	i = 0;
	while (i < 8)
	{
		ft_memcpy(&buddhabrot[i], fract, sizeof(t_fract));
		buddhabrot[i].end = 1080 / 8 * (i + 1);
		buddhabrot[i].start = 1080 / 8 * i;
		pthread_create(&thread[i], NULL, calc_buddhabrot, &buddhabrot[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
}
