/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 16:25:50 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/09 14:08:41 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	first_part(t_sprite_render *sr, t_doom *d)
{
	sr->surr = d->texture.sprt[sr->paint[sr->i].num_sheet].sprites[sr->paint[sr->i].text_no];
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

static void	cycling(t_sprite_render *sr, t_doom *d)
{
	sr->x_text = (sr->surr->w * sr->percent) / \
		((1 - sr->percent) * sr->doomy + sr->percent);
	sr->clmp_bot = line_point(sr->tmp->zbot1, \
		sr->tmp->zbot2, sr->percent_of_wall);
	sr->clmp_top = line_point(sr->tmp->ztop1, \
		sr->tmp->ztop2, sr->percent_of_wall);
	sr->clmp_top = max(sr->clmp_top, 0);
	sr->clmp_bot = min(sr->clmp_bot, WIN_HEIGHT - 1);
	draw_line_of_sprite(sr, sr->surr, &d->render);
	sr->y += sr->d_y;
	sr->za += sr->d_za;
	sr->zb += sr->d_zb;
	sr->percent += sr->d_percent;
	sr->percent_of_wall += sr->d_percent_of_wall;
}

static void	pre_cycle_cal(t_sprite_render *sr, t_doom *d)
{
	sr->curr_sect = d->map.sectors + sr->paint[sr->i].sector_no;
	sr->xscale1_p = HFOV / sr->v1.y;
	sr->xscale2_p = HFOV / sr->v2.y;
	sr->x1_p = WIN_WIDTH / 2 - (sr->v1.x * sr->xscale1_p);
	sr->x2_p = WIN_WIDTH / 2 - (sr->v2.x * sr->xscale2_p);
	sr->begin_x = max(sr->x1, sr->tmp->sx1);
	sr->end_x = min(sr->x2, sr->tmp->sx2);
	sr->win_x = sr->begin_x - 1;
	sr->z1a = WIN_HEIGHT / 2 - ((sr->z1 + sr->t1.y * d->player.angle_z) * sr->zscale1);
	sr->z1b = WIN_HEIGHT / 2 - ((sr->z2 + sr->t1.y * d->player.angle_z) * sr->zscale1);
	sr->z2a = WIN_HEIGHT / 2 - ((sr->z1 + sr->t2.y * d->player.angle_z) * sr->zscale2);
	sr->z2b = WIN_HEIGHT / 2 - ((sr->z2 + sr->t2.y * d->player.angle_z) * sr->zscale2);
	sr->d_percent = 1.0 / (sr->x2_p - sr->x1_p);
	sr->percent = (sr->begin_x - sr->x1_p) * sr->d_percent;
	sr->d_za = (sr->z2a - sr->z1a) / (sr->x2 - sr->x1);
	sr->d_zb = (sr->z2b - sr->z1b) / (sr->x2 - sr->x1);
	sr->za = (sr->begin_x - sr->x1) * sr->d_za + sr->z1a;
	sr->zb = (sr->begin_x - sr->x1) * sr->d_zb + sr->z1b;
	sr->percent_of_wall = fpercent(sr->tmp->sx1, sr->tmp->sx2, sr->begin_x);
	sr->d_percent_of_wall = 1.0 / ((float)sr->tmp->sx2 - sr->tmp->sx1);
	sr->d_y = (sr->t2.y - sr->t1.y) / (sr->x2 - sr->x1);
	sr->y = (sr->begin_x - sr->x1) * sr->d_y + sr->t1.y;
	sr->doomy = sr->v2.y / sr->v1.y;
}
void		paint_vert_cal(t_vector *t1, t_vector *t2, t_painting *pnt, t_player p)
{
	t1->x = pnt->v1.x - p.coord.x;
	t1->y = pnt->v1.y - p.coord.y;
	t2->x = pnt->v2.x - p.coord.x;
	t2->y = pnt->v2.y - p.coord.y;
	t1->z = pnt->v1.z - p.coord.z;
	t2->z = pnt->v2.z - p.coord.z;
	rotate_vector_xy(t1, p.anglesin, p.anglecos);
	rotate_vector_xy(t2, p.anglesin, p.anglecos);
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
		while (sr.tmp != d->render.tail)
		{
			if ((int)sr.tmp->num == sr.paint[sr.i].sector_no)
			{
				if (sr.x1 >= sr.x2 || sr.x2 < sr.tmp->sx1 || sr.x1 > sr.tmp->sx2)
				{
					if (++sr.tmp == (d->render.queue + MAX_SECTORS_RENDERED))
						sr.tmp = d->render.queue;
					continue ;
				}
				pre_cycle_cal(&sr, d);
				while (++sr.win_x <= sr.end_x)
					cycling(&sr, d);
			}
			if (++sr.tmp == (d->render.queue + MAX_SECTORS_RENDERED))
				sr.tmp = d->render.queue;
		}
	}
}
