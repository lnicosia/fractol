/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:59:27 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 13:44:22 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			init_julia(t_fract *fract)
{
	fract->movement = 0;
	fract->color_base = RED;
	fract->color_mode = FLAT;
	fract->color_inside = WHITE;
	fract->name = "Julia";
	fract->zoom = 300;
	fract->inv_zoom = 1 / fract->zoom;
	fract->iter_max = 64;
	fract->min.y = -1.7;
	fract->min.x = -1.8;
	fract->move.x = 0;
	fract->move.y = 0;
	fract->transfo.x = 0;
	fract->transfo.y = 0;
	fract->incr = 8;
	fract->maj_incr = 40;
	return (0);
}

static void	iterate_z(t_complex z, int x, int y, t_fract *fract)
{
	while (z.r * z.r + z.i * z.i < 4
			&& fract->iter < fract->iter_max)
	{
		z = compute_mandelbrot_sequence(z, new_complex(-0.835
					+ fract->transfo.y, 0.2321 + fract->transfo.x));
		fract->iter++;
	}
	if (fract->iter == fract->iter_max)
		color_inside(x, y, fract);
	else
		color(x, y, fract);
}

static void	*calc_julia(void *param)
{
	int			x;
	int			y;
	t_complex	z;
	t_fract		*fract;

	fract = (t_fract*)param;
	y = fract->start;
	while (y < fract->end)
	{
		x = 0;
		while (x < 1024)
		{
			z.r = x * fract->inv_zoom + fract->min.x
				+ fract->move.x;
			z.i = y * fract->inv_zoom + fract->min.y
				+ fract->move.y;
			fract->iter = 0;
			iterate_z(z, x, y, fract);
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
		julia[i].end = 1024 / 8 * (i + 1);
		julia[i].start = 1024 / 8 * i;
		if (pthread_create(&thread[i], NULL, calc_julia, &julia[i]))
			free_all(fract);
		i++;
	}
	while (i-- > 0)
		if (pthread_join(thread[i], NULL))
			free_all(fract);
	put_fractal_to_window(fract);
}
