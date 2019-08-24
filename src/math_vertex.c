/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vertex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:55:16 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/23 17:57:19 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_vertex	intersect(t_vertex d1, t_vertex d2, t_vertex d3, t_vertex d4)
{
	float	lenght;
	float	n1;
	float	n2;

	n1 = VXS(d1.x, d1.y, d2.x, d2.y);
	n2 = VXS(d3.x, d3.y, d4.x, d4.y);
	lenght = VXS(d1.x - d2.x, d1.y - d2.y, d3.x - d4.x, d3.y - d4.y);
	return ((t_vertex){VXS(n1, d1.x - d2.x, n2, d3.x - d4.x) / lenght,
		VXS(n1, d1.y - d2.y, n2, d3.y - d4.y) / lenght});
}

t_vertex	vec_to_ver(t_vector v)
{
	t_vertex	vert;

	vert.x = v.x;
	vert.y = v.y;
	return (vert);
}

t_vertex	get_line_param(float x1, float y1, float x2, float y2)
{
	t_vertex	res;

	res.x = (y2 - y1) / (x2 - x1);
	res.y = y2 - res.x * x2;
	return (res);
}

t_vertex	find_x_from_screen_coords(float xw, t_vertex start, \
	t_vertex end, t_render *r)
{
	t_vertex	res;
	double		a;
	double		b;

	xw -= (WIN_WIDTH / 2);
	if (comp_real(end.x, start.x, 0.001))
		res = (t_vertex){start.x, -start.x * HFOV / xw};
	else
	{
		a = (end.y - start.y) / (end.x - start.x);
		b = start.y - a * start.x;
		res.x = -b * xw / (double)(HFOV + a * xw);
		res.y = a * res.x + b;
	}
	rotate_vertex_xy(&res, r->psin, -r->pcos);
	res.x += r->p_x;
	res.y += r->p_y;
	return (res);
}
