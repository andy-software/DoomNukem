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

static void	draw_dot(int x, int y, t_doom *d, int color)
{
	Uint32	*pixels = (Uint32*)d->sdl.surface->pixels;

	if (y >= 0 && y < WIN_HEIGHT - 1 && x >= 0 && x < WIN_WIDTH - 1)
		pixels[y * d->sdl.surface->w + x] = color;
}

static void	cycling(t_sprite_render *sr, t_doom *d)
{
	t_rend_sector	*tail;

	tail = sr->tmp;
	sr->clmp_top = 0;
	sr->clmp_bot = WIN_HEIGHT - 1;
	while (tail != 0)
	{
		sr->percent_of_wall = fpercent(tail->sx1, tail->sx2, sr->win_x);
		if (sr->percent_of_wall < 0 || sr->percent_of_wall > 1)
			printf("hey\n");
		sr->clmp_top = MAX(line_point(tail->ztop1, tail->ztop2, sr->percent_of_wall), sr->clmp_top);
		sr->clmp_bot = MIN(line_point(tail->zbot1, tail->zbot2, sr->percent_of_wall), sr->clmp_bot);
		tail = tail->prev;
	}
	sr->x_text = (sr->surr->w * sr->percent) / \
		((1 - sr->percent) * sr->doomy + sr->percent);
	sr->clmp_top = MAX(sr->clmp_top, 0);
	sr->clmp_bot = MIN(sr->clmp_bot, WIN_HEIGHT - 1);
draw_dot(sr->win_x, sr->clmp_top, d, 0xff0000);
		draw_dot(sr->win_x, sr->clmp_bot, d, 0xff0000);
	draw_line_of_sprite(sr, sr->surr, &d->render);
	sr->y += sr->d_y;
	sr->za += sr->d_za;
	sr->zb += sr->d_zb;
	sr->percent += sr->d_percent;
	// sr->percent_of_wall += sr->d_percent_of_wall;
}

static void	pre_cycle_cal(t_sprite_render *sr, t_doom *d)
{
	sr->curr_sect = d->map.sectors + sr->paint[sr->i].sector_no;
	sr->xscale1_p = HFOV / sr->v1.y;
	sr->xscale2_p = HFOV / sr->v2.y;
	sr->x1_p = WIN_WIDTH / 2 - (sr->v1.x * sr->xscale1_p);
	sr->x2_p = WIN_WIDTH / 2 - (sr->v2.x * sr->xscale2_p);
	sr->begin_x = MAX(sr->x1, sr->tmp->sx1);
	sr->end_x = MIN(sr->x2, sr->tmp->sx2);
	sr->win_x = sr->begin_x - 1;
	sr->z1a = WIN_HEIGHT / 2 - ((sr->z1 + \
		sr->t1.y * d->player.angle_z) * sr->zscale1);
	sr->z1b = WIN_HEIGHT / 2 - ((sr->z2 + \
		sr->t1.y * d->player.angle_z) * sr->zscale1);
	sr->z2a = WIN_HEIGHT / 2 - ((sr->z1 + \
		sr->t2.y * d->player.angle_z) * sr->zscale2);
	sr->z2b = WIN_HEIGHT / 2 - ((sr->z2 + \
		sr->t2.y * d->player.angle_z) * sr->zscale2);
	sr->d_percent = 1.0 / (sr->x2_p - sr->x1_p);
	sr->percent = (sr->begin_x - sr->x1_p) * sr->d_percent;
	sr->d_za = (sr->z2a - sr->z1a) / (sr->x2 - sr->x1);
	sr->d_zb = (sr->z2b - sr->z1b) / (sr->x2 - sr->x1);
	sr->za = (sr->begin_x - sr->x1) * sr->d_za + sr->z1a;
	sr->zb = (sr->begin_x - sr->x1) * sr->d_zb + sr->z1b;
	sr->percent_of_wall = fpercent(sr->tmp->sx1, sr->tmp->sx2, sr->begin_x);
	// sr->d_percent_of_wall = 1.0 / ((float)sr->tmp->sx2 - sr->tmp->sx1);
	sr->d_y = (sr->t2.y - sr->t1.y) / (sr->x2 - sr->x1);
}

void		paint_vert_cal(t_vector *t1, t_vector *t2, \
									t_painting *pnt, t_player p)
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

void		painting_render_cycle(t_sprite_render *sr, t_doom *d)
{
	while (sr->tmp != d->render.tail)
	{
		if ((int)sr->tmp->num == sr->paint[sr->i].sector_no)
		{
			if (sr->x1 >= sr->x2 || \
					sr->x2 < sr->tmp->sx1 || sr->x1 > sr->tmp->sx2)
			{
				if (++sr->tmp == (d->render.queue + MAX_SECTORS_RENDERED))
					sr->tmp = d->render.queue;
				continue ;
			}
			pre_cycle_cal(sr, d);
			sr->y = (sr->begin_x - sr->x1) * sr->d_y + sr->t1.y;
			sr->doomy = sr->v2.y / sr->v1.y;
			while (++sr->win_x <= sr->end_x)
				cycling(sr, d);
		}
		if (++sr->tmp == (d->render.queue + MAX_SECTORS_RENDERED))
			sr->tmp = d->render.queue;
	}
}
