/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:25:59 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/23 18:08:09 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			project_vector2d(float *ax, float *ay, float bx, float by)
{
	float	k;

	k = DVP(*ax, *ay, bx, by) / DVP(bx, by, bx, by);
	*ax = k * bx;
	*ay = k * by;
	return (1);
}

int			sign(float x)
{
	if (comp_real(x, 0.f, 0.000001f))
		return (0);
	return (x > 0 ? 1 : -1);
}

int			rotate_vector_xy(t_vector *a, float psin, float pcos)
{
	t_vertex buff;

	buff.x = a->x;
	buff.y = a->y;
	a->x = buff.x * psin - buff.y * pcos;
	a->y = buff.x * pcos + buff.y * psin;
	a->z = a->z;
	return (0);
}

float		find_angle_2pi(float sin, float cos)
{
	if (sin > 0)
		return (acos(cos));
	else
		return (2 * M_PI - acos(cos));
}

int			rotate_vertex_xy(t_vertex *a, float psin, float pcos)
{
	t_vertex buff;

	buff.x = a->x;
	buff.y = a->y;
	a->x = buff.x * psin - buff.y * pcos;
	a->y = buff.x * pcos + buff.y * psin;
	return (0);
}
