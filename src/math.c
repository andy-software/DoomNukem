/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:25:59 by apavlov           #+#    #+#             */
/*   Updated: 2019/03/23 18:26:00 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_vertex	intersect(t_vertex d1, t_vertex d2, t_vertex d3, t_vertex d4) //find the coord dot of intersection of line {d1, d2} and line {d3, d4}
{
	float	lenght;
	float	n1;
	float	n2;

	n1 = vxs(d1.x, d1.y, d2.x, d2.y);
	n2 = vxs(d3.x, d3.y, d3.x, d3.y);
	lenght = vxs(d1.x - d2.x, d1.y - d2.y, d3.x - d4.x, d3.y - d4.y);
	return ((t_vertex){vxs(n1, d1.x - d2.x, n2, d3.x - d4.x) / lenght,
		vxs(n1, d1.y - d2.y, n2, d3.y - d4.y) / lenght});
}

int			project_vector2d(float *ax, float *ay, float bx, float by) //project a onto b
{
	float	k;

	k = dvp(*ax, *ay, bx, by) / dvp(bx, by, bx, by);
	*ax = k * bx;
	*ay = k * by;
	return (1);
}


int		sign(float x)
{
	if (x > 0)
		return (1);
	return (x == 0 ? 0 : -1);
}

int		rotate_vector_xy(t_vector *a, float psin, float pcos)
{
	t_vertex buff;

	buff.x = a->x;
	buff.y = a->y;	

	a->x = buff.x * psin - buff.y * pcos;
	a->y = buff.x * pcos + buff.y * psin;
	a->z = a->z;
	return (0);
}

int		rotate_vertex_xy(t_vertex *a, float psin, float pcos)
{
	t_vertex buff;

	buff.x = a->x;
	buff.y = a->y;	

	a->x = buff.x * psin - buff.y * pcos;
	a->y = buff.x * pcos + buff.y * psin;
	return (0);
}

float	fpercent(float start, float end, float current)
{
	float	placement;
	float	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

float	v2dlenght(float vx, float vy)
{
	return (sqrt(vx * vx + vy * vy));
}
