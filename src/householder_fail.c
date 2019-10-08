/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   householder_fail.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:50:42 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/07 17:33:33 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "color_newton.h"

int			init_householder_fail(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = FLAT;
	fract->name = "Householder_fail";
	fract->zoom = 400;
	fract->inv_zoom = 1 / fract->zoom;
	fract->iter_max = 80;
	fract->min.x = -1.2;
	fract->min.y = -1.4;
	fract->move.x = 0;
	fract->move.y = 0;
	fract->incr = 8;
	fract->a = 1;
	fract->maj_incr = 40;
	return (0);
}

static void	*calc_householder_fail(void *param)
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
	roots[1] = new_complex(-0.5, SQRT_3_2);
	roots[2] = new_complex(-0.5, -SQRT_3_2);
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
			while (fract->iter < fract->iter_max
				&& !is_tol(z, roots[0], tolerance)
				&& !is_tol(z, roots[1], tolerance)
				&& !is_tol(z, roots[2], tolerance))
			{
				z = ft_csub(z, ft_cdiv(ft_cadd(ft_rmul(4,
				ft_cpow(z, 6)), ft_radd(-1, ft_rmul(-3,
				ft_cpow(z, 3)))), ft_rmul(9, ft_cpow(z, 5))));
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

void		householder_fail(t_fract *fract)
{
	pthread_t	thread[8];
	t_fract		householder_fail[8];
	int			i;
	char		*str;

	i = 0;
	while (i < 8)
	{
		ft_memcpy(&householder_fail[i], fract, sizeof(t_fract));
		householder_fail[i].end = 1024 / 8 * (i + 1);
		householder_fail[i].start = 1024 / 8 * i;
		pthread_create(&thread[i], NULL, calc_householder_fail,
		&householder_fail[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 10, 0xFFFFFF,
	"Iterations: ");
	str = ft_sitoa(fract->iter_max);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 10, 0xFFFFFF,
	str);
	print_color_data(fract);
}
