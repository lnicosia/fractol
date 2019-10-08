/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:29:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/08 11:53:48 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			init_buddhabrot(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = NASA;
	fract->name = "Buddhabrot";
	fract->zoom = 400;
	fract->inv_zoom = 1 / fract->zoom;
	fract->iter_max = 512;
	fract->min.x = -1.8;
	fract->min.y = -1.28;
	fract->iter_min = 15;
	fract->incr = 8;
	fract->maj_incr = 40;
	if (init_color_arrays(fract))
		return (-1);
	return (0);
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

	fract = (t_fract*)param;
	y = fract->start;
	while (y < fract->end)
	{
		x = 0;
		while (x < 1024)
		{
			c.r = x * fract->inv_zoom + fract->min.x;
			c.i = y * fract->inv_zoom + fract->min.y;
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
			if (fract->iter < fract->iter_max && fract->iter
					> fract->iter_min)
			{
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
					coord.x = (int)((z.r - fract->min.x)
							* fract->zoom);
					coord.y = (int)((z.i - fract->min.y)
							* fract->zoom);
					if (coord.x >= 0 && coord.x < 1024
							&& coord.y >= 0
							&& coord.y < 1024)
					{
						color_buddha_pixel(coord.x,
								coord.y, fract);
						coord.y = (int)((-z.i
						- fract->min.y) * fract->zoom);
						if (coord.y >= 0
							&& coord.y < 1024)
							color_buddha_pixel(
							coord.x, coord.y,
							fract);
					}
				}
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

void		buddhabrot(t_fract *fract)
{
	pthread_t		thread[8];
	t_fract			buddhabrot[8];
	int				i;
	char			*str;

	i = 0;
	reset_img(fract->window.img.str);
	ft_printf("Computing Buddha..\n");
	while (i < 8)
	{
		ft_memcpy(&buddhabrot[i], fract, sizeof(t_fract));
		buddhabrot[i].end = 512 / 8 * (i + 1);
		buddhabrot[i].start = 512 / 8 * i;
		pthread_create(&thread[i], NULL, calc_buddhabrot,
		&buddhabrot[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	if (fract->color_mode != SIN)
		colorize_buddha(fract);
	ft_printf("Done\n\n");
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 10, 0xFFFFFF,
	"Iter max: ");
	str = ft_sitoa(fract->iter_max);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 10, 0xFFFFFF,
	str);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 30, 0xFFFFFF,
	"Iter min: ");
	str = ft_sitoa(fract->iter_min);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 30, 0xFFFFFF,
	str);
	print_color_data(fract);
}
