/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_newton.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:36:57 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/20 16:00:09 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_NEWTON_H
# define COLOR_NEWTON_H
# include "fractol.h"

void	color_red(int x, int y, t_fract *fract);
void	color_green(int x, int y, t_fract *fract);
void	color_blue(int x, int y, t_fract *fract);
void	color_newton(int x, int y, t_fract *fract, t_complex z);

#endif
