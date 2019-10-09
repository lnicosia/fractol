/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   householder_fail2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:50:42 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 10:12:02 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "color_newton.h"

int			init_householder_fail2(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = FLAT;
	fract->name = "householder_fail2";
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

static void	iterate_z(t_complex z, t_complex roots[3], t_coord2 pos,
		t_fract *fract)
{
	while (fract->iter < fract->iter_max
			&& !is_tol(z, roots[0], 0.001)
			&& !is_tol(z, roots[1], 0.001)
			&& !is_tol(z, roots[2], 0.001))
	{
		z = ft_csub(z, ft_cdiv(ft_cadd(ft_rmul(4,
							ft_cpow(z, 6)), ft_radd(-1, ft_rmul(-3,
								ft_cpow(z, 6)))), ft_rmul(9, ft_cpow(z, 5))));
		fract->iter++;
	}
	if (is_tol(z, roots[0], 0.001))
		color_red(pos.x, pos.y, fract);
	else if (is_tol(z, roots[1], 0.001))
		color_green(pos.x, pos.y, fract);
	else if (is_tol(z, roots[2], 0.001))
		color_blue(pos.x, pos.y, fract);
	else
		fract->window.img.str[pos.x + 1024 * pos.y] = 0;
}

static void	*calc_householder_fail2(void *param)
{
	t_coord2	pos;
	t_complex	z;
	t_fract		*fract;
	t_complex	roots[3];

	fract = (t_fract*)param;
	roots[0] = new_complex(1, 0);
	roots[1] = new_complex(-0.5, SQRT_3_2);
	roots[2] = new_complex(-0.5, -SQRT_3_2);
	pos.y = fract->start - 1;
	while (++pos.y < fract->end)
	{
		pos.x = -1;
		while (++pos.x < 1024)
		{
			z.r = pos.x * fract->inv_zoom + fract->min.x
				+ fract->move.x;
			z.i = pos.y * fract->inv_zoom + fract->min.y
				+ fract->move.y;
			fract->iter = 0;
			iterate_z(z, roots, pos, fract);
		}
	}
	return (NULL);
}

void		householder_fail2(t_fract *fract)
{
	pthread_t	thread[8];
	t_fract		householder_fail2[8];
	int			i;

	i = 0;
	while (i < 8)
	{
		ft_memcpy(&householder_fail2[i], fract, sizeof(t_fract));
		householder_fail2[i].end = 1024 / 8 * (i + 1);
		householder_fail2[i].start = 1024 / 8 * i;
		pthread_create(&thread[i], NULL, calc_householder_fail2,
				&householder_fail2[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	put_fractal_to_window(fract);
}
