/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:50:42 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/02 15:33:20 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "color_newton.h"
#include <math.h>

int			init_newton(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = FLAT;
	fract->name = "Newton";
	fract->zoom = 400;
	fract->inv_zoom = 1 / fract->zoom;
	fract->iter_max = 40;
	fract->min.x = -1.2;
	fract->min.y = -1.4;
	fract->move.x = 0;
	fract->move.y = 0;
	return (0);
}

int	is_tol(t_complex z, t_complex root, double tolerance)
{
	return (fabs(ft_csub(z, root).r) < tolerance
			&& fabs(ft_csub(z, root).i) < tolerance);
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
		while (x < 1024)
		{
			z.r = x * fract->inv_zoom + fract->min.x + fract->move.x;
			z.i = y * fract->inv_zoom + fract->min.y + fract->move.y;
			fract->iter = 0;
			while (fract->iter < fract->iter_max
				&& !is_tol(z, roots[0], tolerance) && !is_tol(z, roots[1], tolerance) && !is_tol(z, roots[2], tolerance))
			{
				z = ft_csub(z, ft_cmul(new_complex(0.5, 0), ft_cdiv(ft_csub(ft_cpow(z, 3),
									new_complex(1, 0)),
								ft_cmul(new_complex(3, 0), ft_cpow(z, 2)))));
				fract->iter++;
			}
			if (is_tol(z, roots[0], tolerance))
				color_red(x, y, fract);
			else if (is_tol(z, roots[1], tolerance))
				color_green(x, y, fract);
			else if (is_tol(z, roots[2], tolerance))
				color_blue(x, y, fract);
			else
				fract->window.img.str[x + 1024 * y] = 0;
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
	char		*str;

	i = 0;
	while (i < 8)
	{
		ft_memcpy(&newton[i], fract, sizeof(t_fract));
		newton[i].end = 1024 / 8 * (i + 1);
		newton[i].start = 1024 / 8 * i;
		pthread_create(&thread[i], NULL, calc_newton, &newton[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 10, 0xFFFFFF, "Iterations: ");
	str = ft_itoa(fract->iter_max);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 10, 0xFFFFFF, str);
	free(str);
	print_color_data(fract);
}
