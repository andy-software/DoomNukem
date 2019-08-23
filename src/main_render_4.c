/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_render_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 20:07:35 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/23 20:07:36 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	render_sector_first_part(t_render *r, t_doom *d, int i)
{
	r->line = r->sect->lines[i];
	r->t1.x = r->sect->vert[i].x - r->p_x;
	r->t1.y = r->sect->vert[i].y - r->p_y;
	r->t2.x = r->sect->vert[i + 1].x - r->p_x;
	r->t2.y = r->sect->vert[i + 1].y - r->p_y;
	rotate_vertex_xy(&r->t1, r->psin, r->pcos);
	rotate_vertex_xy(&r->t2, r->psin, r->pcos);
	r->v1.x = r->t1.x;
	r->v1.y = r->t1.y;
	r->v2.x = r->t2.x;
	r->v2.y = r->t2.y;
	r->t1_1_line = r->t1.y < r->t1.x * 1.455;
	r->t1_2_line = r->t1.y < -r->t1.x * 1.455;
	r->t2_1_line = r->t2.y < r->t2.x * 1.455;
	r->t2_2_line = r->t2.y < -r->t2.x * 1.455;
}

int		render_sector_cliping_lines(t_render *r)
{
	if (r->t1.y < 0 && r->t2.y < 0)
		return (1);
	if ((r->t1_1_line && r->t2_1_line) || (r->t1_2_line && r->t2_2_line))
		return (1);
	if (r->t1_1_line || r->t1_2_line || r->t2_1_line || r->t2_2_line)
	{
		r->i1 = intersect(r->t1, r->t2, (t_vertex){0, 0}, \
												(t_vertex){1, 1.455});
		r->i2 = intersect(r->t1, r->t2, (t_vertex){0, 0}, \
												(t_vertex){-1, 1.455});
		if (r->t1_1_line && r->i1.y >= 0)
			r->t1 = r->i1;
		if (r->t1_2_line && r->i2.y >= 0)
			r->t1 = r->i2;
		if (r->t2_1_line && r->i1.y >= 0)
			r->t2 = r->i1;
		if (r->t2_2_line && r->i2.y >= 0)
			r->t2 = r->i2;
	}
	r->xscale1 = HFOV / r->t1.y;
	r->xscale2 = HFOV / r->t2.y;
	r->zscale1 = VFOV / r->t1.y;
	r->zscale2 = VFOV / r->t2.y;
	return (0);
}
