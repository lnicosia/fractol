/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:46:30 by lnicosia          #+#    #+#             */
/*   Updated: 2018/12/19 11:17:35 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ipart(float x)
{
	return ((int)x);
}

int		round_(float x)
{
	return (ipart(x + 0.5));
}

float	fpart(float x)
{
	return (x - ipart(x));
}

float	rfpart(float x)
{
	return (1.0 - fpart(x));
}
