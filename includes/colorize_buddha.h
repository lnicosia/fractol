/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize_buddha.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:46:44 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/07 18:14:51 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORIZE_BUDDHA_H
# define COLORIZE_BUDDHA_H

typedef struct		s_color_data
{
	unsigned int	max;
	unsigned int	max_blue;
	unsigned int	max_green;
	unsigned int	max_red;
	unsigned int	col;
	unsigned int	col_blue;
	unsigned int	col_green;
	unsigned int	col_red;
}					t_color_data;

#endif
