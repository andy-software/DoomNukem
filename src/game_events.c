/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanylch <mdanylch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:14:51 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/27 20:29:25 by mdanylch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void			move_player(t_doom *d, float dx, float dy)
{
	GE_VAR0(p, sect, vert);
	UNS_0(s);
	FLOAT2(hole_high, hole_low);
	p = (t_vertex){d->player.coord.x, d->player.coord.y};
	sect = d->map.sectors + d->player.sector;
	vert = sect->vert;
	hole_high = get_z(sect->ceil_plane, p.x + dx, p.y + dy);
	hole_low = get_z(sect->floor_plane, p.x + dx, p.y + dy);
	if (hole_high > d->player.coord.z && \
		hole_low < d->player.coord.z - d->game.eye_height + KNEE_HEIGHT)
	{
		while (s < sect->num_vert)
		{
			if (sect->neighbors[s] >= 0 && ctl(p, \
				(t_vertex){p.x + dx, p.y + dy}, vert[s], vert[s + 1]))
			{
				d->player.sector = sect->neighbors[s];
				d->game.falling = 1;
			}
			s++;
		}
		d->player.coord.x += dx;
		d->player.coord.y += dy;
	}
}

static	void	fall(t_player *p, t_map m, t_game *g)
{
	GE_VAR1(ceil_p, floor_p, floor_z, ceil_z);
	GE_VAR_1(nextz, p->coord.z, g->velocity.z);
	ceil_p = m.sectors[p->sector].ceil_plane;
	floor_p = m.sectors[p->sector].floor_plane;
	floor_z = get_z(floor_p, p->coord.x, p->coord.y);
	ceil_z = get_z(ceil_p, p->coord.x, p->coord.y);
	g->velocity.z -= 0.02f;
	//g->velocity.z -= m.gravity;
	if (g->velocity.z < 0 && nextz <= floor_z + g->eye_height)
	{
		p->coord.z = floor_z + g->eye_height;
		if (g->velocity.z < -1.2)
			g->hp_level += g->velocity.z * 25;
		INIT2(g->velocity.z, 0, g->falling, 0);
	}
	else if (g->velocity.z > 0 && nextz > ceil_z - HEAD_HEIGHT)
	{
		g->velocity.z = 0;
		g->falling = 1;
	}
	if (g->falling)
	{
		p->coord.z += g->velocity.z;
		g->moving = 1;
	}
}

static	int		sprite_sort_cal(t_doom *d)
{
	int		i;

	i = -1;
	while (++i < (int)d->map.num_sprites)
		d->sr.sprites[i] = d->map.sprites[i];
	translate_and_rotate_sprites(d->sr.sprites, d->map.num_sprites, d->player);
	sprite_sort(d->sr.sprites, d->map.num_sprites);
	return (1);
}

static	void	game_events_next(t_doom *d)
{
	if (d->game.fire == 1)
	{
		check_sprite_intersection(d);
		d->game.fire = 0;
	}
	if (d->game.click == 1)
	{
		check_keys_intersection(d);
		check_painting_intersection(d);
		d->game.click = 0;
	}
	if (d->map.sectors[d->player.sector].floor_tex == 3 && d->game.ground)
	{
		d->game.hp_level -= 1;
		if (!(Mix_Playing(2)))
			Mix_PlayChannel(2, d->sound.hurt, 0);
	}
	check_keys_state(d);
	if (!d->map.editing)
		move_mobs(d);
}

void			game_events(t_doom *d)
{
	t_game	*g;

	g = &d->game;
	g->eye_height = g->ducking ? SIT_EYE_HEIGHT : EYE_HEIGHT;
	g->ground = !g->falling;
	sprite_sort_cal(d);
	if (g->falling)
		fall(&d->player, d->map, &d->game);
	if (g->ground)
		d->player.coord.z = get_z(d->map.sectors[d->player.sector].\
		floor_plane, d->player.coord.x, d->player.coord.y) + g->eye_height;
	if (g->moving)
	{
		move(&d->player, d->map, &d->game);
		check_mobs_while_movement(&d->player, d, &d->game);
		move_player(d, g->dx, g->dy);
	}
	game_events_next(d);
}
