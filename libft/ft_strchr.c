/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:49:01 by lnicosia          #+#    #+#             */
/*   Updated: 2018/11/22 14:38:08 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (c == '\0')
	{
		while (s[i])
			i++;
		return ((char*)s + i);
	}
	while (s[i])
	{
		if (c == s[i])
			return ((char*)s + i);
		i++;
	}
	return (0);
}
