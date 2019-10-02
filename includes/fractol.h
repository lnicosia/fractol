/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:33:04 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/02 17:03:05 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define MAX_FRACT 9
# include <mlx.h>
# include <pthread.h>
# include <time.h>
# include "libft.h"
# define BLACK 0
# define WHITE 1
# define RED 2
# define GREEN 3
# define BLUE 4
# define MIXED_1 5
# define MIXED_2 6
# define MIXED_3 7
# define FLAT 0
# define COS 1
# define SIN 2
# define NASA 3

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
	unsigned int	color_inside;
	unsigned int	color_inside_mode;
	unsigned int	color_center;
	unsigned int	*red;
	unsigned int	*green;
	unsigned int	*blue;
	int				start;
	int				end;
	char			*name;
	double			zoom;
	double			inv_zoom;
	void			*mlx_ptr;
	t_window		window;
	int				iter;
	int				iter_max;
	int				iter_min;
	t_fcoord2		min;
	t_coord2		drag;
	t_fcoord2		transfo;
	t_fcoord2		move;
	int				movement;
	t_list			*pixels;
	int				maj_buffer;
	int				ctrl_buffer;
	void			(*func)(struct s_fract *);
	int				(*init_func)(struct s_fract *);
}				t_fract;

typedef struct	s_env
{
	void			*mlx_ptr;
	t_fract			fract[MAX_FRACT];
	void			(*fract_func[MAX_FRACT])(t_fract *);
	int				(*init_func[MAX_FRACT])(t_fract *);
	int				args[MAX_FRACT];
	int				s_width;
	int				s_height;
}				t_env;

void			julia(t_fract *fract);
void			mandelbrot(t_fract *fract);
void			ship(t_fract *fract);
void			buddhabrot(t_fract *fract);
void			buddha2(t_fract *fract);
void			burning_julia(t_fract *fract);
void			newton(t_fract *fract);
void			koch(t_fract *fract);
void			newton_sin(t_fract *fract);
void			barnsley(t_fract *fract);
int				init_julia(t_fract *fract);
int				init_mandelbrot(t_fract *fract);
int				init_ship(t_fract *fract);
int				init_buddhabrot(t_fract *fract);
int				init_buddha2(t_fract *fract);
int				init_burning_julia(t_fract *fract);
int				init_newton(t_fract *fract);
int				init_newton_sin(t_fract *fract);
int				init_barnsley(t_fract *fract);
int				init_koch(t_fract *fract);
int				init_window(t_fract *fract, t_env *data);
int				init_fract(t_env *data);
int				export_fdf(t_fract fract);
void			reset_img(t_fract *fract);
void			color(int x, int y, t_fract *fract);
void			color_inside(int x, int y, t_fract *fract);
void			color_buddha(int x, int y, t_fract *fract);
void			colorize_buddha(t_fract *fract);
void			swap_color_base(int key, t_fract *fract);
void			swap_color_mode(int key, t_fract *fract);
t_complex		ft_cadd(t_complex c1, t_complex c2);
t_complex		ft_csub(t_complex c1, t_complex c2);
t_complex		ft_cmul(t_complex c1, t_complex c2);
t_complex		ft_cdiv(t_complex c1, t_complex c2);
t_complex		ft_cpow(t_complex c1, int pow);
t_complex		ft_csin(t_complex c);
t_complex		ft_ccos(t_complex c);
t_complex		new_complex(double r, double i);
t_coord2		new_coord2(int x, int y);
t_fcoord2		new_fcoord2(double x, double y);
void			plot_line(t_coord2 c1, t_coord2 c2, t_fract *fract, int color);
void			print_color_data(t_fract *fract);
void			free_all(t_fract *fract);

#endif
