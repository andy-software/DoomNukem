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

t_vertex	find_x_from_screen_coords(float xw, t_vertex start, t_vertex end, t_render *r)
{
	t_vertex	res;
	double		a;
	double		b;

	xw -= (WIN_WIDTH / 2);
	if (comp_real(end.x, start.x, 0.001)) //in case of parallel rays //could be more precisely
	{
		// res = (t_vertex){start.x ,(start.x * HFOV * start.y / \
		// 	(start.y * (r->exact_begin - xw) + start.x * HFOV))}; // some old version idr how i calculate this so i will leave it
		res = (t_vertex){start.x, -start.x * HFOV / xw};
	}
	else
	{	
		a = (end.y - start.y) / (end.x - start.x);
		b = start.y - a * start.x;
		res.x = -b * xw / (double)(HFOV + a * xw);
		res.y = a * res.x + b;
	}
	rotate_vertex_xy(&res, r->psin, -r->pcos); //rotate and translate back
	res.x += r->p_x;
	res.y += r->p_y;
	return (res);
}

t_vertex	get_line_param(float x1, float y1, float x2, float y2)
{
	t_vertex	res;

	res.x = (y2 - y1) / (x2 - x1); // k param
	res.y = y2 - res.x * x2; // b param
	return (res);
}