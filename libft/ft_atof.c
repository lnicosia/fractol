/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:44:04 by sipatry           #+#    #+#             */
/*   Updated: 2019/10/09 11:55:19 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	part2(const char *str)
{
	int		count;
	double	res2;

	count = 0;
	res2 = ft_abs(ft_atoi(str));
	while (*str >= '0' && *str <= '9')
	{
		str++;
		count++;
	}
	while (count > 0)
	{
		res2 /= 10;
		count--;
	}
	return (res2);
}

double			ft_atof(const char *str)
{
	double	res;
	double	res1;
	int		count;
	int		neg;

	neg = 1;
	if (*str == '-')
	{
		neg = -1;
		str++;
	}
	count = 0;
	res1 = ft_abs(ft_atoi(str));
	while (*str >= '0' && *str <= '9')
	{
		str++;
		count++;
	}
	if (!*str || *str != '.')
		return (neg * res1);
	str++;
	res = res1 + part2(str);
	return (neg * res);
}
