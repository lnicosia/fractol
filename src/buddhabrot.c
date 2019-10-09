/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:29:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 13:47:04 by lnicosia         ###   ########.fr       */
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
	t_coord2	pos;
	t_complex	z;
	t_complex	c;
	t_fract		*fract;

	fract = (t_fract*)param;
	pos.y = fract->start - 1;
	while (++pos.y < fract->end)
	{
		pos.x = -1;
		while (++pos.x < 1024)
		{
			c.r = pos.x * fract->inv_zoom + fract->min.x;
			c.i = pos.y * fract->inv_zoom + fract->min.y;
			z = new_complex(0, 0);
			fract->iter = -1;
			while (z.r * z.r + z.i * z.i < 4
					&& ++fract->iter < fract->iter_max)
				z = compute_mandelbrot_sequence(z, c);
			if (fract->iter < fract->iter_max
				&& fract->iter > fract->iter_min)
				iterate_valid_point(fract, c);
		}
	}
	return (NULL);
}

void		buddhabrot(t_fract *fract)
{
	pthread_t		thread[8];
	t_fract			buddhabrot[8];
	int				i;

	i = -1;
	reset_img(fract->window.img.str);
	ft_printf("Computing Buddha..\n");
	while (++i < 8)
	{
		ft_memcpy(&buddhabrot[i], fract, sizeof(t_fract));
		buddhabrot[i].end = 512 / 8 * (i + 1);
		buddhabrot[i].start = 512 / 8 * i;
		if (pthread_create(&thread[i], NULL, calc_buddhabrot, &buddhabrot[i]))
			free_all(fract);
	}
	while (i-- > 0)
		if (pthread_join(thread[i], NULL))
			free_all(fract);
	if (fract->color_mode != SIN)
		colorize_buddha(fract);
	put_fractal_to_window(fract);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 30, 0xFFFFFF,
	"Iter min: ");
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 30, 0xFFFFFF,
	ft_sitoa(fract->iter_min));
}
