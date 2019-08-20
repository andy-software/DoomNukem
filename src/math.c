/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:25:59 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/18 19:44:24 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_vertex	intersect(t_vertex d1, t_vertex d2, t_vertex d3, t_vertex d4)
{
	float	lenght;
	float	n1;
	float	n2;

	n1 = vxs(d1.x, d1.y, d2.x, d2.y);
	n2 = vxs(d3.x, d3.y, d4.x, d4.y);
	lenght = vxs(d1.x - d2.x, d1.y - d2.y, d3.x - d4.x, d3.y - d4.y);
	return ((t_vertex){vxs(n1, d1.x - d2.x, n2, d3.x - d4.x) / lenght,
		vxs(n1, d1.y - d2.y, n2, d3.y - d4.y) / lenght});
}

t_vertex	vec_to_ver(t_vector v)
{
	t_vertex	vert;

	vert.x = v.x;
	vert.y = v.y;
	return (vert);
}

int			project_vector2d(float *ax, float *ay, float bx, float by)
{
	float	k;

	k = dvp(*ax, *ay, bx, by) / dvp(bx, by, bx, by);
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

float		fpercent(float start, float end, float current)
{
	float	placement;
	float	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

float		v2dlenght(float vx, float vy)
{
	return (sqrt(vx * vx + vy * vy));
}

float		line_len(t_vertex start, t_vertex end)
{
	t_vertex	d;

	d.x = end.x - start.x;
	d.y = end.y - start.y;
	return (sqrt(d.x * d.x + d.y * d.y));
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

t_vertex	get_line_param(float x1, float y1, float x2, float y2)
{
	t_vertex	res;

	res.x = (y2 - y1) / (x2 - x1);
	res.y = y2 - res.x * x2;
	return (res);
}

/*
	just cool function that reverse bits in int like this 000011 -> 110000
*/

int			reverse_bits(int b)
{
	return ((b * 0x0202020202ULL & 0x010884422010ULL) % 0x3ff);
}

int			line_point_int(int start, int end, int p)
{
	return (start + (end - start) * p / 100);
}

Uint32		get_color_value_int(Uint32 start, Uint32 end, int perc)
{
	int		r;
	int		g;
	int		b;

	r = line_point_int((start >> 16) & 0xFF, (end >> 16) & 0xFF, perc);
	g = line_point_int((start >> 8) & 0xFF, (end >> 8) & 0xFF, perc);
	b = line_point_int(start & 0xFF, end & 0xFF, perc);
	return ((r << 16) | (g << 8) | b);
}

Uint32		get_color_value(Uint32 start, Uint32 end, float perc)
{
	int		r;
	int		g;
	int		b;

	r = line_point((start >> 16) & 0xFF, (end >> 16) & 0xFF, perc);
	g = line_point((start >> 8) & 0xFF, (end >> 8) & 0xFF, perc);
	b = line_point(start & 0xFF, end & 0xFF, perc);
	return ((r << 16) | (g << 8) | b);
}
