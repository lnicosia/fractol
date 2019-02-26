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

typedef struct	s_env
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_img		img;
	t_config	config;

}				t_env;

#endif
