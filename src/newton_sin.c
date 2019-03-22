/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:50:42 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/22 14:43:50 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "color_newton.h"
#include <math.h>

void		init_newton_sin(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = FLAT;
	fract->name = "Newton";
	fract->zoom = 200;
	fract->iter_max = 16;
	fract->min.x = -2.0;
	fract->min.y = -2.0;
	fract->move.x = 0;
	fract->move.y = 0;
}

int	is_sin_tol(t_complex z, t_complex root, double tolerance)
{
	return (fabs(ft_csub(z, root).r) < tolerance && fabs(ft_csub(z, root).i) < tolerance);
	/*(void)tolerance;
	return (z.r % root.r == 0);*/
}

static void	*calc_newton_sin(void *param)
{
	int			x;
	int			y;
	t_complex	z;
	t_fract		*fract;
	t_complex	roots[3];
	double		tolerance;

	fract = (t_fract*)param;
	tolerance = 0.001;
	roots[0] = new_complex(2 * M_PI, 0);
	roots[1] = new_complex(2 * M_PI, 0);
	roots[2] = new_complex(M_PI + 2 * M_PI, 0);
	y = fract->start;
	while (y < fract->end)
	{
		x = 0;
		while (x < 1920)
		{
			z.r = x / fract->zoom + fract->min.x + fract->move.x;
			z.i = y / fract->zoom + fract->min.y + fract->move.y;
			fract->iter = 0;
			while (fract->iter < fract->iter_max)
				//&& !is_tol(z, roots[0], tolerance) && !is_tol(z, roots[1], tolerance) && !is_tol(z, roots[2], tolerance))
			{
				z = ft_csub(z, ft_cmul(new_complex(1, 0), ft_cdiv(ft_csin(z), ft_ccos(z))));
				fract->iter++;
			}
			//ft_printf("%f + %fi\n", z.r, z.i);
			color_newton(x, y, fract, z);
			/*if (is_sin_tol(z, roots[0], tolerance))
				color_red(x, y, fract);
			else if (is_sin_tol(z, roots[1], tolerance))
				color_green(x, y, fract);
			else if (is_sin_tol(z, roots[2], tolerance))
				color_blue(x, y, fract);
			else
				fract->window.img.str[x + 1920 * y] = 0;*/
			x++;
		}
		y++;
	}
	return (NULL);
}

void		newton_sin(t_fract *fract)
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
		pthread_create(&thread[i], NULL, calc_newton_sin, &newton[i]);
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