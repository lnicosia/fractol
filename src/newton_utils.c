/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:50:45 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/08 15:54:22 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		is_tol(t_complex z, t_complex root, double tolerance)
{
	return (fabs(ft_csub(z, root).r) < tolerance
			&& fabs(ft_csub(z, root).i) < tolerance);
}
