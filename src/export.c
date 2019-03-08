/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 12:23:40 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/08 12:44:45 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <fcntl.h>

int		export_fdf(t_fract fract)
{
	int		fd;
	char	*file;

	ft_printf("exporting..\n");
	file = ft_strjoin(fract.name, ".fdf");
	if ((fd = open(file, O_CREAT)) < 0)
	{
		ft_printf("Open error\n");
		return (-1);
	}
	ft_dprintf(fd, "test\n");
	if (close(fd) == -1)
		return (-1);
	ft_printf("%s created successfully!\n", file);
	ft_strdel(&file);
	return (0);
}
