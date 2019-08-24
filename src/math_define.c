/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_define.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 18:04:08 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/24 17:39:05 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			ctl(t_vertex v1, t_vertex v2, t_vertex v3, t_vertex v4)
{
	return (intersectbox(v1, v2, v3, v4) && pointside(v2, v3, v4) < 0);
}

float		pointside(t_vertex vp, t_vertex v1, t_vertex v2)
{
	return (VXS(v2.x - v1.x, v2.y - v1.y, \
							vp.x - v1.x, vp.y - v1.y));
}

int			intersectbox(t_vertex v1, t_vertex v2, t_vertex v3, t_vertex v4)
{
	return (overlap(v1.x, v2.x, v3.x, v4.x) && \
							overlap(v1.y, v2.y, v3.y, v4.y));
}

int			overlap(float a0, float a1, float b0, float b1)
{
	return (MIN(a0, a1) <= MAX(b0, b1) && MIN(b0, b1) <= MAX(a0, a1));
}
