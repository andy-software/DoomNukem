/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 18:17:42 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/23 18:17:43 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			sprite_render_cliping(t_sprite_render *sr)
{
	sr->v1 = sr->t1;
	sr->v2 = sr->t2;
	sr->t1_1_line = sr->t1.y < sr->t1.x * 1.455;
	sr->t1_2_line = sr->t1.y < -sr->t1.x * 1.455;
	sr->t2_1_line = sr->t2.y < sr->t2.x * 1.455;
	sr->t2_2_line = sr->t2.y < -sr->t2.x * 1.455;
	if ((sr->t1_1_line && sr->t2_1_line) || (sr->t1_2_line && sr->t2_2_line))
		return (1);
	if (sr->t1_1_line || sr->t1_2_line || sr->t2_1_line || sr->t2_2_line)
	{
		sr->i1 = intersect((t_vertex){sr->t1.x, sr->t1.y}, (t_vertex)\
		{sr->t2.x, sr->t2.y}, (t_vertex){0, 0}, (t_vertex){1, 1.455});
		sr->i2 = intersect((t_vertex){sr->t1.x, sr->t1.y}, (t_vertex)\
		{sr->t2.x, sr->t2.y}, (t_vertex){0, 0}, (t_vertex){-1, 1.455});
		if (sr->t1_1_line && sr->i1.y >= 0)
			sr->t1 = (t_vector){sr->i1.x, sr->i1.y, sr->t1.z};
		if (sr->t1_2_line && sr->i2.y >= 0)
			sr->t1 = (t_vector){sr->i2.x, sr->i2.y, sr->t1.z};
		if (sr->t2_1_line && sr->i1.y >= 0)
			sr->t2 = (t_vector){sr->i1.x, sr->i1.y, sr->t2.z};
		if (sr->t2_2_line && sr->i2.y >= 0)
			sr->t2 = (t_vector){sr->i2.x, sr->i2.y, sr->t2.z};
	}
	return (0);
}

static void	draw_dot(int x, int y, t_doom *d, int color)
{
	Uint32	*pixels = (Uint32*)d->sdl.surface->pixels;

	if (y >= 0 && y < WIN_HEIGHT - 1 && x >= 0 && x < WIN_WIDTH - 1)
		pixels[y * d->sdl.surface->w + x] = color;
}

static void	sprite_render_cycle_2(t_sprite_render *sr, t_doom *d)
{
	t_rend_sector	*tail;

	sr->za = (sr->win_x - sr->x1) * sr->d_za + sr->z1a;
	sr->zb = (sr->win_x - sr->x1) * sr->d_zb + sr->z1b;
	
	// sr->d_percent_of_wall = 1.0 / ((float)sr->tmp->sx2 - sr->tmp->sx1);
	while (sr->win_x <= sr->end_x)
	{
		sr->clmp_top = 0;
		sr->clmp_bot = WIN_HEIGHT - 1;
		tail = sr->tmp;
		while (tail != 0)
		{
			sr->percent_of_wall = fpercent(tail->sx1, tail->sx2, sr->win_x);
			if (sr->percent_of_wall < 0 || sr->percent_of_wall > 1)
				printf("hey\n");
			sr->clmp_top = MAX(line_point(tail->ztop1, tail->ztop2, sr->percent_of_wall), sr->clmp_top);
			sr->clmp_bot = MIN(line_point(tail->zbot1, tail->zbot2, sr->percent_of_wall), sr->clmp_bot);
			tail = tail->prev;
		}
		//add check if clmp top is less then clmp bot then continue
		sr->clmp_top = MAX(sr->clmp_top, 0);
		sr->clmp_bot = MIN(sr->clmp_bot, WIN_HEIGHT - 1);
		draw_dot(sr->win_x, sr->clmp_top, d, 0xff0000);
		draw_dot(sr->win_x, sr->clmp_bot, d, 0xff0000);
		draw_line_of_sprite(sr, sr->surr, &d->render);
		sr->za += sr->d_za;
		sr->zb += sr->d_zb;
		sr->percent += sr->d_percent;
		sr->x_text += sr->d_x_text;
		// sr->percent_of_wall += sr->d_percent_of_wall;
		sr->win_x++;
	}
}

static void	before_sprite_cycle(t_sprite_render *sr, t_doom *d)
{
	sr->curr_sect = d->map.sectors + sr->sprites[sr->i].sector_no;
	sr->xscale1_p = HFOV / sr->v1.y;
	sr->xscale2_p = HFOV / sr->v2.y;
	sr->x1_p = WIN_WIDTH / 2 - (sr->v1.x * sr->xscale1_p);
	sr->x2_p = WIN_WIDTH / 2 - (sr->v2.x * sr->xscale2_p);
	sr->begin_x = MAX(sr->x1, sr->tmp->sx1);
	sr->end_x = MIN(sr->x2, sr->tmp->sx2);
	sr->win_x = sr->begin_x;
	sr->z1a = WIN_HEIGHT / 2 - (int)((sr->t1.z + \
		sr->t1.y * d->player.angle_z) * sr->zscale1);
	sr->z1b = WIN_HEIGHT / 2 - (int)((sr->t2.z + \
		sr->t1.y * d->player.angle_z) * sr->zscale1);
	sr->z2a = WIN_HEIGHT / 2 - (int)((sr->t1.z + \
		sr->t2.y * d->player.angle_z) * sr->zscale2);
	sr->z2b = WIN_HEIGHT / 2 - (int)((sr->t2.z + \
		sr->t2.y * d->player.angle_z) * sr->zscale2);
	sr->d_percent = 1.0 / (sr->x2_p - sr->x1_p);
	sr->percent = (sr->win_x - sr->x1_p) * sr->d_percent;
	sr->y = sr->t1.y;
	sr->x_text = (sr->surr->w * sr->percent);
	sr->d_x_text = sr->surr->w * sr->d_percent;
	sr->d_za = (sr->z2a - sr->z1a) / (sr->x2 - sr->x1);
	sr->d_zb = (sr->z2b - sr->z1b) / (sr->x2 - sr->x1);
}

void		sprite_render_cycle(t_sprite_render *sr, t_doom *d)
{
	sr->tmp = sr->begin;
	while (sr->tmp != d->render.tail)
	{
		if ((int)sr->tmp->num == sr->sprites[sr->i].sector_no)
		{
			if (sr->x1 >= sr->x2 || \
				sr->x2 < sr->tmp->sx1 || sr->x1 > sr->tmp->sx2)
			{
				if (++sr->tmp == (d->render.queue + MAX_SECTORS_RENDERED))
					sr->tmp = d->render.queue;
				continue ;
			}
			before_sprite_cycle(sr, d);
			sprite_render_cycle_2(sr, d);
		}
		if (++sr->tmp == (d->render.queue + MAX_SECTORS_RENDERED))
			sr->tmp = d->render.queue;
	}
}
