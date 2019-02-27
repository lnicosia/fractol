/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:33:04 by lnicosia          #+#    #+#             */
/*   Updated: 2019/02/26 12:28:17 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define MAX_FRACT 2
# include <mlx.h>
# include "libft.h"

typedef struct	s_img
{
	int				bit_per_pixels;
	int				size_line;
	int				endian;
	unsigned int	*str;
}				t_img;

typedef struct	s_config
{
	unsigned int	s_width;
	unsigned int	s_height;
}				t_config;

typedef struct	s_fract
{
	int		iter;
	int		iter_max;
}				t_fract;

typedef struct	s_env
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_img		img;
	t_config	config;
	char		*title;
	void		(*fractal[MAX_FRACT])(struct s_env *);
	int			args[MAX_FRACT];
}				t_env;

void	julia(t_env *data);
void	mandelbrot(t_env *data);
int		init_window(t_env *data, int i, char *title);
void	init_hook(t_env *data, int i);
void	init_fract(t_env *data);

#endif
