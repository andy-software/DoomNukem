/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events_mobs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanylch <mdanylch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 20:05:31 by mdanylch          #+#    #+#             */
/*   Updated: 2019/08/27 20:05:37 by mdanylch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static	void	mobs_events_2(t_doom *d, int i, int j)
{
	if (j == 1)
	{
		Mix_PlayChannel(6, d->sound.pickup[3], 0);
		d->game.flying = 1;
		d->game.fuel = 100;
		d->map.sprites[d->sr.sprites[i].spr_num].draw = 0;
	}
	else if (j == 2)
	{
		Mix_PlayChannel(6, d->sound.pickup[2], 0);
		d->game.picked_key[d->sr.sprites[i].text_no] = 1;
		d->map.sprites[d->sr.sprites[i].spr_num].draw = 0;
	}
}

static	void	mobs_events(t_doom *d, int i)
{
	if (d->sr.sprites[i].num_sheet == 1 && \
		d->game.hp_level < 100 && d->sr.sprites[i].pick == 1)
	{
		Mix_PlayChannel(5, d->sound.pickup[0], 0);
		d->game.hp_level += 30;
		d->map.sprites[d->sr.sprites[i].spr_num].draw = 0;
		if (d->game.hp_level > 100)
			d->game.hp_level = 100;
	}
	else if (d->sr.sprites[i].num_sheet == 2 && \
		d->ui.ammo_1 < 60 && d->sr.sprites[i].pick == 1)
	{
		Mix_PlayChannel(6, d->sound.pickup[1], 0);
		d->ui.ammo_1 += 16;
		d->map.sprites[d->sr.sprites[i].spr_num].draw = 0;
		if (d->ui.ammo_1 > 60)
			d->ui.ammo_1 = 60;
	}
	else if (d->sr.sprites[i].num_sheet == 7 && d->sr.sprites[i].pick == 1)
	{
		mobs_events_2(d, i, 1);
	}
	else if (d->sr.sprites[i].num_sheet == 3 && d->sr.sprites[i].pick == 1)
		mobs_events_2(d, i, 2);
}

void			check_mobs_while_movement(t_player *p, t_doom *d, t_game *g)
{
	INT_1(i);
	INITMOBS_VAR(t1, t2, next_step);
	while (++i < (int)d->map.num_sprites)
		if (d->sr.sprites[i].coord.y < 0)
			break ;
	INIT2(next_step.x, g->dx, next_step.y, g->dy);
	rotate_vertex_xy(&next_step, p->anglesin, p->anglecos);
	while (--i >= 0)
	{
		sprite_vert_cal(&t1, &t2, d->sr.sprites + i, d->player);
		if (d->sr.sprites[i].draw == 0)
			continue;
		if (ctl((t_vertex){0, 0}, next_step, (t_vertex){t1.x, t1.y}, \
			(t_vertex){t2.x, t2.y}) && (d->player.coord.z >= \
			d->sr.sprites[i].coord.z + d->sr.sprites[i].start_z \
			&& d->player.coord.z - g->eye_height <= \
			d->sr.sprites[i].coord.z + d->sr.sprites[i].end_z))
		{
			mobs_events(d, i);
			project_vector2d(&next_step.x, &next_step.y, \
							t2.x - t1.x, t2.y - t1.y);
			rotate_vertex_xy(&next_step, p->anglesin, -p->anglecos);
			INIT2(g->dx, next_step.x, g->dy, next_step.y);
		}
	}
}
