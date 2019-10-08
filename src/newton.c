/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:50:42 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/08 16:00:27 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "color_newton.h"

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
	fract->incr = 8;
	fract->a = 1;
	fract->maj_incr = 40;
	return (0);
}

void		iterate_z(t_complex z, t_complex roots[3], t_coord2 pos,
t_fract *fract)
{
	while (fract->iter < fract->iter_max
			&& !is_tol(z, roots[0], 0.001)
			&& !is_tol(z, roots[1], 0.001)
			&& !is_tol(z, roots[2], 0.001))
	{
		z = ft_csub(z, ft_rmul(fract->a,
					ft_cdiv(ft_rsub(1, ft_cpow(z, 3)),
						ft_rmul(3, ft_cpow(z, 2)))));
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

static void	*calc_newton(void *param)
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

void		newton(t_fract *fract)
{
	pthread_t	thread[8];
	t_fract		newton[8];
	int			i;

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
	put_fractal_to_window(fract);
}
