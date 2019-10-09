/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:29:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 13:47:10 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			init_buddha2(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = NASA;
	fract->name = "Random buddhabrot";
	fract->zoom = 400;
	fract->inv_zoom = 1 / fract->zoom;
	fract->iter_max = 512;
	fract->min.x = -1.8;
	fract->min.y = -1.28;
	fract->iter_min = 15;
	fract->incr = 8;
	fract->pow = 2;
	fract->maj_incr = 40;
	if (init_color_arrays(fract))
		return (1);
	return (0);
}

static void	*calc_buddha2(void *param)
{
	int			x;
	t_complex	z;
	t_complex	c;
	t_fract		*fract;

	fract = (t_fract*)param;
	srand(time(NULL));
	x = -1;
	while (++x < 1000000)
	{
		c = new_complex((rand() / (double)RAND_MAX) * -fract->min.x * 2
			+ fract->min.x, (rand() / (double)RAND_MAX)
			* -fract->min.y * 2 + fract->min.y);
		z = new_complex(0, 0);
		fract->iter = -1;
		while (z.r * z.r + z.i * z.i < 4
				&& ++fract->iter < fract->iter_max)
			z = compute_mandelbrot_sequence(z, c);
		if (fract->iter < fract->iter_max
				&& fract->iter > fract->iter_min)
			iterate_valid_point(fract, c);
	}
	return (NULL);
}

void		buddha2(t_fract *fract)
{
	pthread_t		thread[8];
	t_fract			buddha2[8];
	int				i;

	i = -1;
	ft_printf("Computing Buddha..\n");
	reset_img(fract->window.img.str);
	while (++i < 8)
	{
		ft_memcpy(&buddha2[i], fract, sizeof(t_fract));
		if (pthread_create(&thread[i], NULL, calc_buddha2, &buddha2[i]))
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
