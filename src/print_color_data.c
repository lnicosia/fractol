/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_color_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 12:28:56 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/02 16:27:33 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_inside_color(t_fract *fract)
{
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 250, 50, 0xFFFFFF,
			"| Inside mode: ");
	if (fract->color_inside_mode == NASA)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 405, 50, 0xFFFFFF,
				"nasa");
	else if (fract->color_inside_mode == SIN)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 405, 50, 0xFFFFFF,
				"sin");
	else if (fract->color_inside_mode == FLAT)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 405, 50, 0xFFFFFF,
				"flat");
	else if (fract->color_inside_mode == COS)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 405, 50, 0xFFFFFF,
				"cos");
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 250, 70, 0xFFFFFF,
			"| Inside color: ");
	if (fract->color_inside == WHITE)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 405, 70, 0xFFFFFF,
				"white");
	else if (fract->color_inside == BLACK)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 405, 70, 0xFFFFFF,
				"black");
	else if (fract->color_inside == RED)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 405, 70, 0xFFFFFF,
				"red");
	else if (fract->color_inside == BLUE)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 405, 70, 0xFFFFFF,
				"blue");
	else if (fract->color_inside == GREEN)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 405, 70, 0xFFFFFF,
				"green");
	else if (fract->color_inside == MIXED_1)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 405, 70, 0xFFFFFF,
				"mixed 1");
	else if (fract->color_inside == MIXED_2)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 405, 70, 0xFFFFFF,
				"mixed 2");
	else if (fract->color_inside == MIXED_3)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 405, 70, 0xFFFFFF,
				"mixed 3");
}

void	print_color_data(t_fract *fract)
{
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 50, 0xFFFFFF,
			"Outside mode: ");
	if (fract->color_mode == NASA)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 155, 50, 0xFFFFFF,
				"nasa");
	else if (fract->color_mode == SIN)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 155, 50, 0xFFFFFF,
				"sin");
	else if (fract->color_mode == FLAT)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 155, 50, 0xFFFFFF,
				"flat");
	else if (fract->color_mode == COS)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 155, 50, 0xFFFFFF,
				"cos");
	mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 10, 70, 0xFFFFFF,
			"Outside color: ");
	if (fract->color_base == WHITE)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 155, 70, 0xFFFFFF,
				"white");
	else if (fract->color_base == BLACK)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 155, 70, 0xFFFFFF,
				"black");
	else if (fract->color_base == RED)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 155, 70, 0xFFFFFF,
				"red");
	else if (fract->color_base == BLUE)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 155, 70, 0xFFFFFF,
				"blue");
	else if (fract->color_base == GREEN)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 155, 70, 0xFFFFFF,
				"green");
	else if (fract->color_base == MIXED_1)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 155, 70, 0xFFFFFF,
				"mixed 1");
	else if (fract->color_base == MIXED_2)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 155, 70, 0xFFFFFF,
				"mixed 2");
	else if (fract->color_base == MIXED_3)
		mlx_string_put(fract->mlx_ptr, fract->window.win_ptr, 155, 70, 0xFFFFFF,
				"mixed 3");
	print_inside_color(fract);
}
