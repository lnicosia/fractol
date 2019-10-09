/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:42:10 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/09 11:47:35 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_keycode.h"

int		mouse_move(int x, int y, void *param)
{
	t_fract	*fract;
	int		i;

	fract = (t_fract*)param;
	i = 0;
	if (fract->movement && fract->nb != 3)
	{
		fract->transfo.x = x / 1024.0;
		fract->transfo.y = y / 1024.0;
		fract->func(fract);
	}
	return (0);
}

void	mouse_press2(int button, int x, int y, t_fract *fract)
{
	if (button == SCROLLDOWN_KEY && (fract->iter_max > 4
				|| fract->nb == 8))
	{
		if ((fract->zoom > 3 && fract->iter_max > 4)
				|| fract->nb == 8)
		{
			fract->min.x = (x / fract->zoom + fract->min.x)
				- (x / (fract->zoom / 1.5));
			fract->min.y = (y / fract->zoom + fract->min.y)
				- (y / (fract->zoom / 1.5));
			fract->center.x = x + (fract->center.x - x) / 1.5;
			fract->center.y = y + (fract->center.y - y) / 1.5;
			fract->zoom /= 1.5;
			if (fract->nb == 7)
				fract->incr /= 1.5;
			fract->inv_zoom = 1 / fract->zoom;
			fract->func(fract);
		}
	}
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_fract	*fract;
	int		i;

	i = 0;
	fract = (t_fract*)param;
	if (button == SCROLLUP_KEY)
	{
		fract->min.x = (x / fract->zoom + fract->min.x)
			- (x / (fract->zoom * 1.5));
		fract->min.y = (y / fract->zoom + fract->min.y)
			- (y / (fract->zoom * 1.5));
		fract->center.x = x + (fract->center.x - x) * 1.5;
		fract->center.y = y + (fract->center.y - y) * 1.5;
		fract->zoom *= 1.5;
		if (fract->nb == 7)
			fract->incr *= 1.5;
		fract->inv_zoom = 1 / fract->zoom;
		fract->func(fract);
	}
	else
		mouse_press2(button, x, y, fract);
	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_fract	*fract;

	(void)x;
	(void)y;
	fract = (t_fract*)param;
	if (button == BUT1_KEY)
		fract->movement = fract->movement ? 0 : 1;
	return (0);
}
