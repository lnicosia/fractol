/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:50:42 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/14 10:19:34 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void		init_newton(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = FLAT;
	fract->name = "Newton";
	fract->zoom = 400;
	fract->iter_max = 30;
	fract->max.x = 0.6;
	fract->max.y = 1.2;
	fract->min.x = -2.4;
	fract->min.y = -1.4;
	fract->move.x = 0;
	fract->move.y = 0;
}

static int	is_tol(t_complex z, t_complex root, double tolerance)
{
	return (fabs(ft_csub(z, root).r) < tolerance && fabs(ft_csub(z, root).i) < tolerance);
}

static void	*calc_newton(void *param)
{
	int			x;
	int			y;
	t_complex	z;
	t_fract		*fract;
	t_complex	roots[3];
	double		tolerance;

	fract = (t_fract*)param;
	tolerance = 0.001;
	roots[0] = new_complex(1, 0);
	roots[1] = new_complex(-0.5, sqrt(3) / 2);
	roots[2] = new_complex(-0.5, -sqrt(3) / 2);
	y = fract->start;
	while (y < fract->end)
	{
		x = 0;
		while (x < 1920)
		{
			z.r = x / fract->zoom + fract->min.x + fract->move.x;
			z.i = y / fract->zoom + fract->min.y + fract->move.y;
			fract->iter = 0;
			while (fract->iter < fract->iter_max && !is_tol(z, roots[0], tolerance) && !is_tol(z, roots[1], tolerance) && !is_tol(z, roots[2], tolerance))
			{
				z = ft_cdiv(ft_cadd(ft_cmul(new_complex(2, 0),
					ft_cpow(z, 3)), new_complex(1, 0)),
						ft_cmul(new_complex(3, 0), ft_cpow(z, 2)));
				fract->iter++;
			}
			//ft_printf("%f + %fi\n", z.r, z.i);
			if (is_tol(z, roots[0], tolerance))
				fract->window.img.str[x + 1920 * y] = 0xFF0000 *
					(255 * fract->iter / fract->iter_max);
			else if (is_tol(z, roots[1], tolerance))
				fract->window.img.str[x + 1920 * y] = 0x00FF00 *
					(255 * fract->iter / fract->iter_max);
			else if (is_tol(z, roots[2], tolerance))
				fract->window.img.str[x + 1920 * y] = 0x0000FF *
					(255 * fract->iter / fract->iter_max);
			else
				fract->window.img.str[x + 1920 * y] = 0;
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
