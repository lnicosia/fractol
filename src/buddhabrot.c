/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:29:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/15 18:54:17 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_buddhabrot(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = COS;
	fract->name = "Buddhabrot";
	fract->zoom = 400;
	fract->iter_max = 512;
	fract->max.x = 0.6;
	fract->max.y = 1.2;
	fract->min.x = -1.8;
	fract->min.y = -1.35;
}

static void	*calc_buddhabrot(void *param)
{
	int			x;
	int			y;
	double		xtemp;
	t_complex	z;
	t_complex	c;
	t_fract		*fract;
	t_coord2	coord;
	int			i;

	fract = (t_fract*)param;
	y = fract->start;
	i = 0;
	while (y < fract->end)
	{
		x = 0;
		while (x < 1024)
		{
			c.r = x / fract->zoom + fract->min.x + fract->move.x;
			c.i = y / fract->zoom + fract->min.y + fract->move.y;
			z.r = 0;
			z.i = 0;
			fract->iter = 0;
			while (z.r * z.r + z.i * z.i < 4
					&& fract->iter < fract->iter_max)
			{
				xtemp = z.r * z.r - z.i * z.i;
				z.i = 2 * z.r * z.i + c.i;
				z.r = xtemp + c.r;
				fract->iter++;
			}
			if (fract->iter < fract->iter_max && fract->iter > 15)
			{
				i = 0;
				z.r = 0;
				z.i = 0;
				while (z.r * z.r + z.i * z.i < 4
						&& i < fract->iter_max)
				{
					xtemp = z.r * z.r - z.i * z.i;
					z.i = 2 * z.r * z.i + c.i;
					z.r = xtemp + c.r;
					fract->iter++;
					coord.x = (int)((z.r - fract->min.x) * fract->zoom);
					coord.y = (int)((z.i - fract->min.y) * fract->zoom);
					if (coord.x >= 0 && coord.x < 1024
						&& coord.y >= 0 && coord.y < 1024)
						//color_buddha(coord.x, coord.y, fract);
						fract->window.img.str[coord.y + coord.x * 1024]++;
				}
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

static void	reset_img(t_fract *fract)
{
	int	x;
	int	y;

	y = 0;
	while (y < 1024)
	{
		x = 0;
		while (x < 1024)
		{
			fract->window.img.str[x + y * 1024] = 0;
			x++;
		}
		y++;
	}
}

void		buddhabrot(t_fract *fract)
{
	pthread_t		thread[8];
	t_fract			buddhabrot[8];
	int				i;

	i = 0;
	reset_img(fract);
	ft_printf("Computing Buddha..\n");
	while (i < 8)
	{
		ft_memcpy(&buddhabrot[i], fract, sizeof(t_fract));
		buddhabrot[i].end = 1024 / 8 * (i + 1);
		buddhabrot[i].start = 1024 / 8 * i;
		pthread_create(&thread[i], NULL, calc_buddhabrot, &buddhabrot[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	//if (fract->color_mode == SIN)
		colorize_buddha(fract);
	ft_printf("Done\n\n");
	//exit(0);
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
}
