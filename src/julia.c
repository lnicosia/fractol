/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:59:27 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/20 14:39:57 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_julia(t_fract *fract)
{
	fract->movement = 0;
	fract->color_base = RED;
	fract->color_mode = FLAT;
	fract->color_inside = WHITE;
	fract->name = "Julia";
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
				z.y = 2 * z.x * z.y + 0.2321 + fract->transfo.x;
				z.x = xtemp + -0.835 + fract->transfo.y;
				fract->iter++;
			}
			if (fract->iter == fract->iter_max)
				color_inside(x, y, fract);
			else
				color(x, y, fract);
			x++;
		}
		y++;
	}
	return (NULL);
}

void		julia(t_fract *fract)
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
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 10, 0xFFFFFF, "Iterations: ");
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 10, 0xFFFFFF, ft_itoa(fract->iter_max));
}
