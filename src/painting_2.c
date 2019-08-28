/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 18:58:25 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/23 18:58:26 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	first_part(t_sprite_render *sr, t_doom *d)
{
	sr->surr = d->texture.sprt[sr->paint[sr->i].num_sheet].\
		sprites[sr->paint[sr->i].text_no];
	sr->t1.x = sr->paint[sr->i].v1.x - d->player.coord.x;
	sr->t1.y = sr->paint[sr->i].v1.y - d->player.coord.y;
	sr->t2.x = sr->paint[sr->i].v2.x - d->player.coord.x;
	sr->t2.y = sr->paint[sr->i].v2.y - d->player.coord.y;
	sr->z1 = sr->paint[sr->i].v1.z - d->player.coord.z;
	sr->z2 = sr->paint[sr->i].v2.z - d->player.coord.z;
	rotate_vector_xy(&sr->t1, d->player.anglesin, d->player.anglecos);
	rotate_vector_xy(&sr->t2, d->player.anglesin, d->player.anglecos);
	sr->v1 = sr->t1;
	sr->v2 = sr->t2;
	sr->t1_1_line = sr->t1.y < sr->t1.x * 1.455;
	sr->t1_2_line = sr->t1.y < -sr->t1.x * 1.455;
	sr->t2_1_line = sr->t2.y < sr->t2.x * 1.455;
	sr->t2_2_line = sr->t2.y < -sr->t2.x * 1.455;
}

static void	skiping_lines(t_sprite_render *sr)
{
	if (sr->t1_1_line || sr->t1_2_line || sr->t2_1_line || sr->t2_2_line)
	{
		sr->i1 = intersect((t_vertex){sr->t1.x, sr->t1.y}, \
	(t_vertex){sr->t2.x, sr->t2.y}, (t_vertex){0, 0}, (t_vertex){1, 1.455});
		sr->i2 = intersect((t_vertex){sr->t1.x, sr->t1.y}, \
	(t_vertex){sr->t2.x, sr->t2.y}, (t_vertex){0, 0}, (t_vertex){-1, 1.455});
		if (sr->t1_1_line && sr->i1.y >= 0)
			sr->t1 = (t_vector){sr->i1.x, sr->i1.y, sr->t1.z};
		if (sr->t1_2_line && sr->i2.y >= 0)
			sr->t1 = (t_vector){sr->i2.x, sr->i2.y, sr->t1.z};
		if (sr->t2_1_line && sr->i1.y >= 0)
			sr->t2 = (t_vector){sr->i1.x, sr->i1.y, sr->t2.z};
		if (sr->t2_2_line && sr->i2.y >= 0)
			sr->t2 = (t_vector){sr->i2.x, sr->i2.y, sr->t2.z};
	}
	sr->xscale1 = HFOV / sr->t1.y;
	sr->xscale2 = HFOV / sr->t2.y;
	sr->zscale1 = VFOV / sr->t1.y;
	sr->zscale2 = VFOV / sr->t2.y;
	sr->x1 = WIN_WIDTH / 2 - (sr->t1.x * sr->xscale1);
	sr->x2 = WIN_WIDTH / 2 - (sr->t2.x * sr->xscale2);
	sr->tmp = sr->begin;
}

void		render_painting(t_doom *d)
{
	t_sprite_render sr;

	sr = d->sr;
	sr.paint = d->map.paint;
	sr.c_paint = d->map.num_paint;
	sr.i = -1;
	while (++sr.i < sr.c_paint)
	{
		first_part(&sr, d);
		if ((sr.t1_1_line && sr.t2_1_line) || (sr.t1_2_line && sr.t2_2_line))
			continue ;
		skiping_lines(&sr);
		painting_render_cycle(&sr, d);
	}
}
