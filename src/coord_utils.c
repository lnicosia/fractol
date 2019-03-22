/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 11:40:10 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/22 11:41:04 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_coord2	new_coord2(int x, int y)
{
	t_coord2	c;

	c.x = x;
	c.y = y;
	return (c);
}

t_fcoord2	new_fcoord2(double x, double y)
{
	t_fcoord2	c;

	c.x = x;
	c.y = y;
	return (c);
}
