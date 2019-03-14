/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:33:04 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/14 11:36:09 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define MAX_FRACT 6
# include <mlx.h>
# include <pthread.h>
# include "libft.h"
# define WHITE 0
# define RED 1
# define GREEN 2
# define BLUE 3
# define FLAT 0
# define COS 1
# define SIN 2

typedef struct	s_fcoord2
{
	double	x;
	double	y;
}				t_fcoord2;

typedef struct	s_coord2
{
	int	x;
	int	y;
}				t_coord2;

typedef struct	s_complex
{
	double	r;
	double	i;
}				t_complex;

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
	int				nb;
	int				state;
	struct s_fract	*fract[MAX_FRACT];
	unsigned int	color_base;
	unsigned int	color_mode;
	unsigned int	color_center;
	int				start;
	int				end;
	char			*name;
	double			zoom;
	void			*mlx_ptr;
	t_window		window;
	int				iter;
	int				iter_max;
	t_fcoord2		max;
	t_fcoord2		min;
	t_coord2		drag;
	t_fcoord2		transfo;
	t_fcoord2		move;
	int				movement;
	t_list			*pixels;
	int				maj_buffer;
	void			(*func)(struct s_fract *);
}				t_fract;

typedef struct	s_env
{
	void			*mlx_ptr;
	t_fract			fract[MAX_FRACT];
	void			(*fract_func[MAX_FRACT])(t_fract *);
	void			(*init_fract[MAX_FRACT])(t_fract *);
	int				args[MAX_FRACT];
	int				s_width;
	int				s_height;
}				t_env;

void			julia(t_fract *fract);
void			mandelbrot(t_fract *fract);
void			ship(t_fract *fract);
void			buddhabrot(t_fract *fract);
void			burning_julia(t_fract *fract);
void			newton(t_fract *fract);
void			init_julia(t_fract *fract);
void			init_mandelbrot(t_fract *fract);
void			init_ship(t_fract *fract);
void			init_buddhabrot(t_fract *fract);
void			init_burning_julia(t_fract *fract);
void			init_newton(t_fract *fract);
int				init_window(t_fract *fract, t_env *data);
int				init_fract(t_env *data);
int				export_fdf(t_fract fract);
void			color(int x, int y, t_fract *fract);
void			color_buddha(int x, int y, t_fract *fract);
void			colorize_buddha(t_fract *fract);
void			swap_color_base(int key, t_fract *fract);
void			swap_color_mode(int key, t_fract *fract);
t_complex		ft_cadd(t_complex c1, t_complex c2);
t_complex		ft_csub(t_complex c1, t_complex c2);
t_complex		ft_cmul(t_complex c1, t_complex c2);
t_complex		ft_cdiv(t_complex c1, t_complex c2);
t_complex		ft_cpow(t_complex c1, int pow);
t_complex		new_complex(double r, double i);

#endif
