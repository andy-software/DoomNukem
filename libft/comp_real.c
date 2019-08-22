/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_real.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:54:29 by apavlov           #+#    #+#             */
/*   Updated: 2019/01/10 14:54:30 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			comp_real(float a, float b, float precision)
{
	if (ft_float_abs(a - b) < precision)
		return (1);
	else
		return (0);
}
