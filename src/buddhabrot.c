/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:29:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/11 12:28:12 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_buddhabrot(t_fract *fract)
{
	fract->nb = 3;
	fract->name = "Buddhabrot";
	fract->zoom = 400;
	fract->iter_max = 128;
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
	t_fcoord2	z;
	t_fcoord2	c;
	t_fract		*fract;
	t_coord2	coord;
	t_coord2	*tmp_c;
	t_list		*pixels;
	t_list		*tmp;

	fract = (t_fract*)param;
	y = fract->start;
	while (y < fract->end)
	{
		x = 0;
		while (x < 1024)
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
				coord.x = (int)((z.x - fract->min.x) * fract->zoom);
				coord.y = (int)((z.y - fract->min.y) * fract->zoom);
				if (coord.x >= 0 && coord.x < 1024
					&& coord.y >= 0 && coord.y < 1024)
					ft_lstadd(&pixels, ft_lstnew(&coord, sizeof(t_coord2*)));
			}
			if (fract->iter < fract->iter_max && fract->iter > 15)
			{
				tmp = pixels;
				while (tmp)
				{
					tmp_c = (t_coord2*)tmp->content;
					fract->window.img.str[tmp_c->y + tmp_c->x * 1024] += 4500;
					tmp = tmp->next;
				}
			}
			while (pixels)
			{
				tmp = pixels;
				pixels = pixels->next;
				free(tmp->content);
				free(tmp);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

void		rotate_buddha(t_fract *fract)
{
	(void)fract;
}

void		buddhabrot(t_fract *fract)
{
	pthread_t		thread[8];
	t_fract			buddhabrot[8];
	int				i;

	i = 0;
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
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
}
