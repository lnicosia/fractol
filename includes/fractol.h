/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:33:04 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/04 12:08:14 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define MAX_FRACT 3
# include <mlx.h>
# include "libft.h"

typedef struct	s_fcoord2
{
	double	x;
	double	y;
}				t_fcoord2;

typedef struct	s_img
{
	int				bit_per_pixels;
	int				size_line;
	int				endian;
	unsigned int	*str;
}				t_img;

typedef struct	s_window
{
	void		*win_ptr;
	void		*img_ptr;
	t_img		img;
	char		*title;
}				t_window;

typedef struct	s_fract
{
	void		*mlx_ptr;
	t_window	window;
	int			iter;
	int			iter_max;
}				t_fract;

typedef struct	s_env
{
	void			*mlx_ptr;
	t_fract			fract[MAX_FRACT];
	void			(*fract_func[MAX_FRACT])(struct s_env *);
	int				args[MAX_FRACT];
	int				s_width;
	int				s_height;
	t_fcoord2		move;
}				t_env;

void			julia(t_env *data);
void			mandelbrot(t_env *data);
void			ship(t_env *data);
int				init_window(t_fract *fract, t_env *data, char *title);
void			init_hook(t_fract *fract);
int				init_fract(t_env *data);

#endif
