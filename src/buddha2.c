/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:29:09 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/15 18:22:23 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_buddha2(t_fract *fract)
{
	fract->color_base = RED;
	fract->color_mode = COS;
	fract->name = "Random buddhabrot";
	fract->zoom = 400;
	fract->iter_max = 1000;
	fract->max.x = 0.6;
	fract->max.y = 1;
	fract->min.x = -1.8;
	fract->min.y = -1.35;
}

static void	*calc_buddha2(void *param)
{
	int			x;
	int			freer;
	double		xtemp;
	t_complex	z;
	t_complex	c;
	t_fract		*fract;
	t_coord2	coord;
	t_coord2	*tmp_c;
	t_list		*pixels;
	t_list		*tmp;
	t_list		*tmp2;

	fract = (t_fract*)param;
	x = 0;
	pixels = NULL;
	tmp = NULL;
	tmp2 = NULL;
	tmp_c = NULL;
	while (x < 1048576)
	{
		c.r = (rand() / (double)RAND_MAX) * (fract->max.x - fract->min.x) + fract->min.x;
		c.i = (rand() / (double)RAND_MAX) * (fract->max.x - fract->min.x) + fract->max.x;
		//ft_printf("c = %f + %fi\n", c.r, c.i);
		z.r = 0;
		z.i = 0;
		fract->iter = 0;
		freer = 0;
		while (z.r * z.r + z.i * z.i < 4
				&& fract->iter < fract->iter_max)
		{
			xtemp = z.r * z.r - z.i * z.i;
			z.i = 2 * z.r * z.i + c.i;
			z.r = xtemp + c.r;
			fract->iter++;
			/*coord.x = (int)((z.r - fract->min.x) * fract->zoom);
			coord.y = (int)((z.i - fract->min.y) * fract->zoom);
			if (coord.x >= 0 && coord.x < 1024
					&& coord.y >= 0 && coord.y < 1024)
			{
				if (!(tmp = ft_lstnew(&coord, sizeof(t_coord2*))))
				{
					ft_printf("malloc failed\n");
					if (pixels)
						free(pixels);
					if (tmp)
						free(tmp);
					if (tmp2)
						free(tmp2);
					exit(0);
				}
				ft_lstadd(&pixels, tmp);
				coord.y = coord.y + 2 * (512 - coord.y);
				//ft_printf("pixel2 = [%d][%d]\n", coord.x, coord.y);
				if (!(tmp2 = ft_lstnew(&coord, sizeof(t_coord2*))))
				{
					ft_printf("malloc failed\n");
					if (pixels)
						free(pixels);
					if (tmp)
						free(tmp);
					if (tmp2)
						free(tmp2);
					exit(0);
				}
				ft_lstadd(&pixels, tmp2);
				freer = 1;
			}*/
		}
		/*if (fract->iter < fract->iter_max && fract->iter > 10)
		{
			tmp = pixels;
			while (tmp)
			{
				tmp_c = (t_coord2*)tmp->content;
				fract->window.img.str[tmp_c->y + tmp_c->x * 1024] += 0xFFFFFF;
				//fract->window.img.str[tmp_c->y + tmp_c->x * 1024]++;
				//color_buddha(tmp_c->x, tmp_c->y, fract);
				tmp = tmp->next;
			}
		}*/
		if (fract->iter < fract->iter_max && fract->iter > 10)
		{
			fract->iter = 0;
			z.r = 0;
			z.i = 0;
			while (z.r * z.r + z.i * z.i < 4
					&& fract->iter < fract->iter_max)
			{
				xtemp = z.r * z.r - z.i * z.i;
				z.i = 2 * z.r * z.i + c.i;
				z.r = xtemp + c.r;
				fract->iter++;
				coord.x = (int)((z.r - fract->min.x) * fract->zoom);
				coord.y = (int)((z.i - fract->min.y) * fract->zoom);
				if (coord.x >= 0 && coord.x < 1024
						&& coord.y >= 0 && coord.y < 1024)
				{
					//color_buddha(coord.x, coord.y, fract);
					fract->window.img.str[coord.y + coord.x * 1024] += 7500;
					coord.y = coord.y + 2 * (512 - coord.y);
					//color_buddha(coord.x, coord.y, fract);
					fract->window.img.str[coord.y + coord.x * 1024] += 7500;
				}
			}
		}
		while (pixels && freer)
		{
			tmp = pixels;
			pixels = pixels->next;
			free(tmp->content);
			free(tmp);
			tmp = NULL;
		}
		x++;
	}
	return (NULL);
}

static void	reset_img(t_fract *fract)
{
	int	x;
	int	y;

	y = 0;
	while (y < 1024)
	{
		x = 0;
		while (x < 1024)
		{
			fract->window.img.str[x + y * 1024] = 0;
			x++;
		}
		y++;
	}
}

void		buddha2(t_fract *fract)
{
	/*pthread_t		thread[8];
	  t_fract			buddhabrot[8];
	  int				i;

	  i = 0;
	  reset_img(fract);
	  ft_printf("Computing Buddha..\n");
	  while (i < 8)
	  {
	  ft_memcpy(&buddhabrot[i], fract, sizeof(t_fract));
	  buddhabrot[i].end = 1024 / 8 * (i + 1);
	  buddhabrot[i].start = 1024 / 8 * i;
	  pthread_create(&thread[i], NULL, calc_buddhabrot, &buddhabrot[i]);
	  i++;
	  }
	  while (i-- > 0)
	  pthread_join(thread[i], NULL);
	  ft_printf("Done\n\n");
	  if (fract->color_mode == SIN)
	  colorize_buddha(fract);
	  mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	  mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
	  fract->window.img_ptr, 0, 0);*/
	ft_printf("Computing random buddhabrot..\n");
	reset_img(fract);
	calc_buddha2(fract);
	//colorize_buddha(fract);
	ft_printf("Done\n\n");
	//exit(0);
	mlx_clear_window(fract->mlx_ptr, fract->window.win_ptr);
	mlx_put_image_to_window(fract->mlx_ptr, fract->window.win_ptr,
			fract->window.img_ptr, 0, 0);
}
