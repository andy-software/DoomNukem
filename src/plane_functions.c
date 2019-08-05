/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:03:49 by apavlov           #+#    #+#             */
/*   Updated: 2019/04/26 16:03:50 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			get_normal_to_plane(t_vector *v, t_plane *p)
{
	v->x = p->a;
	v->y = p->b;
	v->z = p->c;
	return (1);
}

t_plane		rotate_plane_xy(t_plane *plane, float psin, float pcos)
{
	t_vector	nrmplnvect;
	t_plane		res;

	get_normal_to_plane(&nrmplnvect, plane);
	rotate_vector_xy(&nrmplnvect, psin, pcos);
	res.a = nrmplnvect.x;
	res.b = nrmplnvect.y;
	res.c = nrmplnvect.z;
	res.h = plane->h;
	return (res);
}

float		get_z(t_plane plane, float x, float y)
{
	return ((-plane.h - plane.a * x - plane.b * y));
}
