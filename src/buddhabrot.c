/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:29:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/02 12:17:02 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_array(unsigned int *array)
{
	int	i;

	i = -1;
	while (++i < 1048576)
		array[i] = 0;
}

int			init_buddhabrot(t_fract *fract)
{
	fract->color_base = WHITE;
	fract->color_mode = NASA;
	fract->name = "Buddhabrot";
	fract->zoom = 400;
	//fract->iter_max = 10000;
	fract->iter_max = 512;
	fract->min.x = -1.8;
	fract->min.y = -1.28;
	fract->iter_min = 15;
	fract->red = NULL;
	fract->green = NULL;
	fract->blue = NULL;
	if (fract->color_mode == NASA)
	{
		if (!(fract->red = (unsigned int*)malloc(sizeof(unsigned int) * 1048576)))
			return (ft_perror("Could not malloc red array"));
		init_array(fract->red);
		if (!(fract->blue = (unsigned int*)malloc(sizeof(unsigned int) * 1048576)))
		{
			free(fract->red);
			return (ft_perror("Could not malloc blue array"));
		}
		init_array(fract->blue);
		if (!(fract->green = (unsigned int*)malloc(sizeof(unsigned int) * 1048576)))
		{
			free(fract->red);
			free(fract->blue);
			return (ft_perror("Could not malloc green array"));
		}
		init_array(fract->green);
	}
	return (0);
}

static void	*calc_buddhabrot(void *param)
{
	int			x;
	int			y;
	double		xtemp;
	t_complex	z;
	t_complex	c;
	t_fract		*fract;
	t_coord2	coord;

	fract = (t_fract*)param;
	y = fract->start;
	//ft_printf("de %d a %d\n", y, fract->end);
	while (y < fract->end)
	{
		x = 0;
		while (x < 1024)
		{
			c.r = x / fract->zoom + fract->min.x;
			c.i = y / fract->zoom + fract->min.y;
			z.r = 0;
			z.i = 0;
			fract->iter = 0;
			while (z.r * z.r + z.i * z.i < 4
					&& fract->iter < fract->iter_max)
			{
				xtemp = z.r * z.r - z.i * z.i;
				z.i = 2 * z.r * z.i + c.i;
				z.r = xtemp + c.r;
				fract->iter++;
			}
			if (fract->iter < fract->iter_max && fract->iter > fract->iter_min)
			{
				z.r = 0;
				z.i = 0;
				fract->iter = 0;
				while (z.r * z.r + z.i * z.i < 4
						&& fract->iter < fract->iter_max)
				{
					xtemp = z.r * z.r - z.i * z.i;
					z.i = 2 * z.r * z.i + c.i;
					z.r = xtemp + c.r;
					fract->iter++;
					coord.x = (int)((z.r - fract->min.x) * fract->zoom)
						;//+ fract->move.x * 20;
					coord.y = (int)((z.i - fract->min.y) * fract->zoom)
						;//+ fract->move.y * 20;
					if (coord.x >= 0 && coord.x < 1024
							&& coord.y >= 0 && coord.y < 1024)
					{
						color_buddha(coord.x, coord.y, fract);
						//coord.y = coord.y + 2 * (512 - coord.y) - 1;
						coord.y = (int)((-z.i - fract->min.y) * fract->zoom)
							;//+ fract->move.y * 20;
						if (coord.y >= 0 && coord.y < 1024)
							color_buddha(coord.x, coord.y, fract);
					}
				}
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

void		buddhabrot(t_fract *fract)
{
	pthread_t		thread[8];
	t_fract			buddhabrot[8];
	int				i;
	char			*str;

	i = 0;
	reset_img(fract);
	ft_printf("Computing Buddha..\n");
	while (i < 8)
	{
		ft_memcpy(&buddhabrot[i], fract, sizeof(t_fract));
		buddhabrot[i].end = 512 / 8 * (i + 1);
		buddhabrot[i].start = 512 / 8 * i;
		pthread_create(&thread[i], NULL, calc_buddhabrot, &buddhabrot[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thread[i], NULL);
	if (fract->color_mode != SIN)
		colorize_buddha(fract);
	ft_printf("Done\n\n");
	//exit(0);
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 10, 0xFFFFFF, "Iter max: ");
	str = ft_itoa(fract->iter_max);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 10, 0xFFFFFF, str);
	free(str);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 30, 0xFFFFFF, "Iter min: ");
	str = ft_itoa(fract->iter_min);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 30, 0xFFFFFF, str);
	free(str);
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 50, 0xFFFFFF,
			"Color mode: ");
	if (fract->color_mode == NASA)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 50, 0xFFFFFF,
				"NASA");
	else if (fract->color_mode == SIN)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 50, 0xFFFFFF,
				"SIN");
	else if (fract->color_mode == FLAT)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 50, 0xFFFFFF,
				"FLAT");
	else if (fract->color_mode == COS)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 125, 50, 0xFFFFFF,
				"COS");
}
