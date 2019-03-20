/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 12:23:40 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/20 14:41:36 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <fcntl.h>
#include <stdio.h>

static int	write_fdf(t_fract fract, int fd)
{
	int	x;
	int	y;

	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			if (x != 0)
				ft_dprintf(fd, " ");
			ft_dprintf(fd, "%d,0x%X",
					(fract.window.img.str[x + y * 1920] * 1000 / 0xFFFFFF),
					fract.window.img.str[x + y * 1920]);
			x += 3;
		}
		ft_dprintf(fd, "\n");
		y += 3;
	}
	return (0);
}

static int	write_buddha_fdf(t_fract fract, int fd)
{
	int	x;
	int	y;

	y = 0;
	while (y < 1024)
	{
		x = 0;
		while (x < 1024)
		{
			if (x != 0)
				ft_dprintf(fd, " ");
			ft_dprintf(fd, "%d,0x%X",
					(fract.window.img.str[x + y * 1024] * 1000 / 0xFFFFFF),
					fract.window.img.str[x + y * 1024]);
			x += 2;
		}
		ft_dprintf(fd, "\n");
		y += 2;
	}
	return (0);
}

int			export_fdf(t_fract fract)
{
	int		fd;
	char	*file;

	ft_printf("exporting..\n");
	file = ft_strjoin(fract.name, ".fdf");
	if ((fd = open(file, O_CREAT, 00755)) < 0)
	{
		ft_printf("Open error\n");
		return (-1);
	}
	if ((fd = open(file, O_WRONLY)) < 0)
	{
		ft_printf("Open error\n");
		return (-1);
	}
	if (fract.nb == 3 || fract.nb == 6)
		write_buddha_fdf(fract, fd);
	else
		write_fdf(fract, fd);
	if (close(fd) == -1)
		return (-1);
	ft_printf("%s created successfully!\n", file);
	ft_strdel(&file);
	return (0);
}
