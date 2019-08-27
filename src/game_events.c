/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:14:51 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/14 06:29:36 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		move_player(t_doom *d, float dx, float dy)
{
	t_vertex	p;
	t_sector *sect;
	t_vertex *vert;
	float hole_high;
	float hole_low;

	p = (t_vertex){d->player.coord.x, d->player.coord.y};
	sect = d->map.sectors + d->player.sector;
	vert = sect->vert;
	hole_high = get_z(sect->ceil_plane, p.x + dx, p.y + dy);
	hole_low = get_z(sect->floor_plane, p.x + dx, p.y + dy);
	if (hole_high > d->player.coord.z + d->game.eye_height && hole_low < d->player.coord.z - d->game.eye_height + KNEE_HEIGHT)
	{
		for(unsigned s = 0; s < sect->num_vert; s++)
			if(sect->neighbors[s] >= 0 && ctl(p, (t_vertex){p.x + dx, p.y + dy}, vert[s], vert[s + 1]))
			{
				d->player.sector = sect->neighbors[s];
				d->game.falling = 1;
			}
		d->player.coord.x += dx;
		d->player.coord.y += dy;
	}
}

static void	fall(t_player *p, t_map	m, t_game *g)
{
	const float nextz = p->coord.z + g->velocity.z;
	t_plane		ceil_p = m.sectors[p->sector].ceil_plane;
	t_plane		floor_p = m.sectors[p->sector].floor_plane;
	float floor_z = get_z(floor_p, p->coord.x, p->coord.y);
	float ceil_z = get_z(ceil_p, p->coord.x, p->coord.y);

	g->velocity.z -= 0.04f;
	if (g->velocity.z < 0 && \
		nextz <= floor_z + g->eye_height)
	{
		p->coord.z = floor_z + g->eye_height;
		if (g->velocity.z < -1.2)
			g->hp_level += g->velocity.z * 25;
		g->velocity.z = 0;
		g->falling = 0;
	}
	else if(g->velocity.z > 0 && nextz > ceil_z - HEAD_HEIGHT)
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

static void	move(t_player *p, t_map	m, t_game *g)
{
	t_sector *sect = m.sectors + p->sector;
	t_vertex *const vert = sect->vert;
	int		i;
	float 	hole_low;
	float	hole_high;
	t_plane	ceil_p = m.sectors[p->sector].ceil_plane;
	t_plane	floor_p = m.sectors[p->sector].floor_plane;
	t_plane	nceil_p;
	t_plane	nfloor_p;
	t_vertex	next;
	int		j;

	i = -1;
	next = (t_vertex){p->coord.x + g->velocity.x, p->coord.y + g->velocity.y};
	while (++i < (int)sect->num_vert)
		if (ctl((t_vertex){p->coord.x, p->coord.y}, next, vert[i], vert[i + 1]))
		{
			if (sect->neighbors[i] < 0)
			{
				hole_low = BIG_VALUE;
				hole_high = -BIG_VALUE;
				nceil_p = m.sectors[0].ceil_plane;
				nfloor_p = m.sectors[0].floor_plane;
			}
			else
			{
				nceil_p = m.sectors[(int)sect->neighbors[i]].ceil_plane;
				nfloor_p = m.sectors[(int)sect->neighbors[i]].floor_plane;
				hole_low = MAX(get_z(floor_p, p->coord.x, p->coord.y), get_z(nfloor_p, next.x, next.y));
				hole_high = MIN(get_z(ceil_p, p->coord.x, p->coord.y), get_z(nceil_p, next.x, next.y));
			}
			if (hole_high > p->coord.z + HEAD_HEIGHT && \
				hole_low < p->coord.z - g->eye_height + KNEE_HEIGHT)
			{
				printf("neightbor to player sector : %i\n", sect->neighbors[i]);
				//printf("{%f, %f}\n", p->coord.x, p->coord.y);
				fflush(stdout);
			}
			else
			{
				project_vector2d(&g->velocity.x, &g->velocity.y, \
					vert[i + 1].x - vert[i].x, vert[i + 1].y - vert[i].y);
				g->moving = 0;
				j = -1;
				next.x = p->coord.x + g->velocity.x;
				next.y = p->coord.y + g->velocity.y;
				while (++j < (int)sect->num_vert) // TODO: check only neightbors walls
				{
					if (j != i && ctl((t_vertex){p->coord.x, p->coord.y}, next, vert[j], vert[j + 1]))
					{
						hole_low  = sect->neighbors[i] < 0 ? BIG_VALUE : \
							MAX(get_z(floor_p, p->coord.x, p->coord.y), get_z(nfloor_p, next.x, next.y));
						hole_high = sect->neighbors[i] < 0 ? -BIG_VALUE : \
							MIN(get_z(ceil_p, p->coord.x, p->coord.y), get_z(nceil_p, next.x, next.y));
						if (!(hole_high > p->coord.z + HEAD_HEIGHT && \
							hole_low < p->coord.z - g->eye_height + KNEE_HEIGHT))
							{
								g->velocity = (t_vector){0, 0, g->velocity.z};
								break ;
							}
					}
				}
				if (j != (int)sect->num_vert)
					break ;
			}
		}
	g->dx = g->velocity.x;
	g->dy = g->velocity.y;
}

void		check_mobs_while_movement(t_player *p, t_doom *d, t_game *g)
{
	int		i;
	t_vector	t1;
	t_vector	t2;
	t_vertex	next_step;

	i = -1;
	while (++i < (int)d->map.num_sprites)
		if (d->sr.sprites[i].coord.y < 0)
			break ;
	
	next_step.x = g->dx;
	next_step.y = g->dy;
	rotate_vertex_xy(&next_step, p->anglesin, p->anglecos);

	while (--i >= 0)
	{
		sprite_vert_cal(&t1, &t2, d->sr.sprites + i, d->player);
		if (d->sr.sprites[i].draw == 0)
			continue;
		if (ctl((t_vertex){0, 0}, next_step, (t_vertex){t1.x, t1.y}, (t_vertex){t2.x, t2.y}) && \
		(d->player.coord.z >= d->sr.sprites[i].coord.z + d->sr.sprites[i].start_z \
			&& d->player.coord.z - g->eye_height <= d->sr.sprites[i].coord.z + d->sr.sprites[i].end_z))
				{
					if (d->sr.sprites[i].num_sheet == 1 && d->game.hp_level < 100 && d->sr.sprites[i].pick == 1)
					{
						Mix_PlayChannel(5, d->sound.pickup[0], 0);
						d->game.hp_level += 30;
						d->map.sprites[d->sr.sprites[i].spr_num].draw = 0;
						if (d->game.hp_level > 100)
							d->game.hp_level = 100;
					}
					else if (d->sr.sprites[i].num_sheet == 2 && d->ui.ammo_1 < 60 && d->sr.sprites[i].pick == 1 )
					{
						Mix_PlayChannel(6, d->sound.pickup[1], 0);
						d->ui.ammo_1 += 16;
						d->map.sprites[d->sr.sprites[i].spr_num].draw = 0;
						if (d->ui.ammo_1 > 60)
							d->ui.ammo_1 = 60;
					}
					else if (d->sr.sprites[i].num_sheet == 7 && d->sr.sprites[i].pick == 1)
					{
						Mix_PlayChannel(6, d->sound.pickup[3], 0);
						d->game.flying = 1;
						d->map.sprites[d->sr.sprites[i].spr_num].draw = 0;
					}
					else if (d->sr.sprites[i].num_sheet == 3 && d->sr.sprites[i].pick == 1)
					{
						Mix_PlayChannel(6, d->sound.pickup[2], 0);
						d->game.picked_key[d->sr.sprites[i].text_no] = 1;
						d->map.sprites[d->sr.sprites[i].spr_num].draw = 0;
					}
					project_vector2d(&next_step.x, &next_step.y, t2.x - t1.x, t2.y - t1.y);
					rotate_vertex_xy(&next_step, p->anglesin, -p->anglecos);
					g->dx = next_step.x;
					g->dy = next_step.y;
				}
	}
}

void		check_sprite_intersection(t_doom *d)
{
	int			i;
	t_vector	t1;
	t_vector	t2;
	float		attack_range;

	i = -1;
	while (++i < (int)d->map.num_sprites)
		if (d->sr.sprites[i].coord.y < 0)
			break ;
	if ( d->ui.gun_num == 0)
		attack_range = 100;
	else if (d->ui.gun_num == 1)
		attack_range = 2;
	else
		return ;

	while (--i >= 0)
	{
		if (!d->sr.sprites[i].live)
			continue ;
		sprite_vert_cal(&t1, &t2, d->sr.sprites + i, d->player);
		if (t1.x > 0 && t2.x < 0 && d->ui.ammo_1 >= -2)
		{
			if (t1.y < attack_range)
			{
				if (t1.z + t1.y * d->player.angle_z > 0 && t2.z + t1.y * d->player.angle_z < 0)
				{
					if (d->ui.gun_num == 0)
					{
						d->map.sprites[d->sr.sprites[i].spr_num].hp -= d->game.damage;
						printf("%d\n", d->sr.sprites[i].hp);
					}
					else
					{
						d->map.sprites[d->sr.sprites[i].spr_num].hp -= d->game.damage / 10;
						d->game.blood = 1;
					}
					if (d->map.sprites[d->sr.sprites[i].spr_num].hp <= 0)
					{
						d->map.sprites[d->sr.sprites[i].spr_num].live = 0;
						if (d->sr.sprites[i].num_sheet == 5)
							Mix_PlayChannel(4, d->sound.mobdeath[1], 0);
						else if (d->sr.sprites[i].num_sheet == 6)
							Mix_PlayChannel(4, d->sound.mobdeath[0], 0);
						else if (d->sr.sprites[i].num_sheet == 8)
							Mix_PlayChannel(4, d->sound.mobdeath[2], 0);
					}
					else
					{
						if (d->sr.sprites[i].num_sheet == 5)
							Mix_PlayChannel(4, d->sound.mobhurt[1], 0);
						else if (d->sr.sprites[i].num_sheet == 6)
							Mix_PlayChannel(4, d->sound.mobhurt[0], 0);
						else if (d->sr.sprites[i].num_sheet == 8)
							Mix_PlayChannel(4, d->sound.mobhurt[2], 0);
					}
					break ;
				}
			}
		}
	}
}

static int	sprite_sort_cal(t_doom *d) //sort one time at game_events when start
{
	int		i;

	i = -1;
	while (++i < (int)d->map.num_sprites)
		d->sr.sprites[i] = d->map.sprites[i];

	translate_and_rotate_sprites(d->sr.sprites, d->map.num_sprites, d->player);
	sprite_sort(d->sr.sprites, d->map.num_sprites);
	return (1);
}

void		game_events(t_doom *d)
{
	t_game	*g;

	g = &d->game;
	g->eye_height = g->ducking ? SIT_EYE_HEIGHT : EYE_HEIGHT;
	g->ground = !g->falling;
	sprite_sort_cal(d);
	if (g->falling)
		fall(&d->player, d->map, &d->game);
	if (g->ground)
		d->player.coord.z = get_z(d->map.sectors[d->player.sector].floor_plane, d->player.coord.x, d->player.coord.y) + g->eye_height;
	if (g->moving)
	{
		move(&d->player, d->map, &d->game);
		check_mobs_while_movement(&d->player, d, &d->game);
		move_player(d, g->dx, g->dy);
	}
	if (d->game.fire == 1)
	{
		if (d->game.fire == 1)
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