/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:32:18 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/10 11:32:21 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_dprintf(int fd, const char *restrict format, ...)
{
	t_data	data;

	if (!format)
		return (-1);
	init_data(&data, fd);
	va_start(data.ap, format);
	parse_format(format, &data);
	write(fd, data.buffer, data.i);
	va_end(data.ap);
	return (data.ret);
}
