/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:32:35 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/10 11:32:37 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_delindex(void *ptr, size_t old_size, size_t type, size_t index)
{
	void		*res;
	size_t		i;
	size_t		j;
	size_t		new_size;

	i = 0;
	j = 0;
	new_size = old_size - type;
	if (!ptr || !old_size || !type || old_size <= type
			|| !(res = malloc(new_size)))
		return (NULL);
	ft_bzero(res, new_size);
	while (i < new_size)
	{
		if (j == index)
			j += type;
		else
		{
			((char*)res)[i] = ((char*)ptr)[j];
			i++;
			j++;
		}
	}
	ft_memdel(&ptr);
	return (res);
}
