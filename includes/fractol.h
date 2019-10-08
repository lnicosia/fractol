/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:33:04 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/08 15:15:23 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define MAX_FRACT 13
# include <mlx.h>
# include <pthread.h>
# include <time.h>
# include <math.h>
# include "libft.h"
# define BLACK 0
# define WHITE 1
# define RED 2
# define GREEN 3
# define BLUE 4
# define MIXED_1 5
# define MIXED_2 6
# define MIXED_3 7
# define MIXED_4 8
# define MIXED_5 9
# define FLAT 0
# define COS 1
# define SIN 2
# define NASA 3
# define LOG 4
# define INV_LOG 5
# define SIN_PI_3 0.86602540378
# define SQRT_3_2 0.86602540378

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
	int				pow;
	int				end;
	char			*name;
	double			zoom;
	double			a;
	double			inv_zoom;
	void			*mlx_ptr;
	t_window		window;
	size_t			iter;
	size_t			iter_max;
	size_t			iter_min;
	size_t			incr;
	size_t			maj_incr;
	t_fcoord2		min;
	t_coord2		drag;
	t_fcoord2		transfo;
	t_fcoord2		move;
	t_fcoord2		center;
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
void			barnsley(t_fract *fract);
void			tricorn(t_fract *fract);
void			householder(t_fract *fract);
void			householder_fail(t_fract *fract);
void			householder_fail2(t_fract *fract);
int				init_julia(t_fract *fract);
int				init_mandelbrot(t_fract *fract);
int				init_tricorn(t_fract *fract);
int				init_ship(t_fract *fract);
int				init_buddhabrot(t_fract *fract);
int				init_buddha2(t_fract *fract);
int				init_burning_julia(t_fract *fract);
int				init_newton(t_fract *fract);
int				init_barnsley(t_fract *fract);
int				init_koch(t_fract *fract);
int				init_householder(t_fract *fract);
int				init_householder_fail(t_fract *fract);
int				init_householder_fail2(t_fract *fract);
int				init_window(t_fract *fract, t_env *data);
int				init_fract(t_env *data);
int				export_fdf(t_fract fract);
int				is_tol(t_complex z, t_complex root, double tolerance);
void			reset_img(unsigned int *array);
void			color(int x, int y, t_fract *fract);
void			color_inside(int x, int y, t_fract *fract);
void			color_buddha_pixel(int x, int y, t_fract *fract);
void			colorize_buddha(t_fract *fract);
void			swap_color_base(int key, t_fract *fract);
void			swap_color_mode(int key, t_fract *fract);
t_coord2		new_coord2(int x, int y);
t_fcoord2		new_fcoord2(double x, double y);
void			plot_line(t_coord2 c1, t_coord2 c2, t_fract *fract, int color);
void			plot_line_aa(t_coord2 c1, t_coord2 c2, t_fract *fract,
		int color);
void			print_color_data(t_fract *fract);
void			free_all(t_fract *fract);
int				ipart(float x);
int				round_(float x);
float			fpart(float x);
float			rfpart(float x);
void			fill_img(t_coord2 c, t_fract *fract, int color,
		float brightness);
void			put_fractal_to_window(t_fract *fract);
void			iterate_valid_point(t_fract *fract, t_complex c);
int			init_color_arrays(t_fract *fract);
t_complex		compute_mandelbrot_sequence(t_complex z, t_complex c);
void			put_buddha_pixel(t_complex z, t_fract *fract);

#endif
