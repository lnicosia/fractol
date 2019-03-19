/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:05:34 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/19 15:08:54 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "math.h"

t_complex	ft_cadd(t_complex c1, t_complex c2)
{
	t_complex	res;

	res.r = c1.r + c2.r;
	res.i = c1.i + c2.i;
	return (res);
}

t_complex	ft_csub(t_complex c1, t_complex c2)
{
	t_complex	res;

	res.r = c1.r - c2.r;
	res.i = c1.i - c2.i;
	return (res);
}

t_complex	ft_cmul(t_complex c1, t_complex c2)
{
	t_complex	res;

	res.r = c1.r * c2.r - c1.i * c2.i;
	res.i = c1.r * c2.i + c1.i * c2.r;
	return (res);
}

t_complex	ft_cdiv(t_complex c1, t_complex c2)
{
	t_complex	res;

	res.r = (c1.r * c2.r + c1.i * c2.i) / (c2.r * c2.r + c2.i * c2.i);
	res.i = (c1.i * c2.r - c1.r * c2.i) / (c2.r * c2.r + c2.i * c2.i);
	return (res);
}

t_complex	ft_cpow(t_complex c1, int pow)
{
	t_complex	res;

	res = c1;
	while (pow > 1)
	{
		res = ft_cmul(res, c1);
		pow--;
	}
	return (res);
}

t_complex	new_complex(double r, double i)
{
	t_complex	res;

	res.r = r;
	res.i = i;
	return (res);
}

t_complex	ft_csin(t_complex c)
{
	t_complex	res;

	res.r = sin(c.r) * cosh(c.i);
	res.i = sinh(c.i) * cos(c.r);
	return (res);
}

t_complex	ft_ccos(t_complex c)
{
	t_complex	res;

	res.r = cos(c.r) * cosh(c.i);
	res.i = -sinh(c.r) * sinh(c.r);
	return (res);
}
