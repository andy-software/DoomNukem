/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:14:51 by apavlov           #+#    #+#             */
/*   Updated: 2019/03/23 18:14:52 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
//CROSS_THE_LINE
#define CTL(x0, y0, x1, y1, x2, y2, x3, y3) \
	(IntersectBox(x0, y0, x1, y1, x2, y2, x3, y3) && \
		PointSide(x1, y1, x2, y2, x3, y3) < 0)

void		move_player(t_doom *d, float dx, float dy)
{
	float px = d->player.coord.x;
	float py = d->player.coord.y;
	t_sector *sect = d->map.sectors + d->player.sector;
	t_vertex *vert = sect->vert;
	float hole_high = get_z(sect->ceil_plane, px + dx, py + dy);
	float hole_low = get_z(sect->floor_plane, px + dx, py + dy);

	if (hole_high > d->player.coord.z + HEAD_HEIGHT && hole_low < d->player.coord.z - EYE_HEIGHT + KNEE_HEIGHT)
	{
		for(unsigned s = 0; s < sect->num_vert; s++)
			if(sect->neighbors[s] >= 0 && CTL(px, py, px + dx, py + dy, \
				vert[s].x, vert[s].y, vert[s + 1].x, vert[s + 1].y))
			{
				d->player.sector = sect->neighbors[s];
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

	g->velocity.z -= 0.02f;
	if (g->velocity.z < 0 && \
		nextz <= floor_z + g->eye_height)
	{
		p->coord.z = floor_z + g->eye_height;
		g->velocity.z = 0;
		g->falling = 0;
		g->ground = 1;
	}
	else if(g->velocity.z > 0 && nextz > get_z(ceil_p, p->coord.x, p->coord.y))
	{
		g->velocity.z = 0;
		g->falling = 1;
	}
	if (g->falling)
	{
		p->coord.z += g->velocity.z;
		//p->angle_z -= 0.3 * g->velocity.z; //optional
		g->moving = 1;
	}
}

static void	move(t_player *p, t_map	m, t_game *g)
{
	const	t_sector *sect = &m.sectors[p->sector];
	const	t_vertex *const vert = sect->vert;
	int		i;
	float 	hole_low;
	float	hole_high;
	t_plane	ceil_p = m.sectors[p->sector].ceil_plane;
	t_plane	floor_p = m.sectors[p->sector].floor_plane;
	t_plane	nceil_p;
	t_plane	nfloor_p;
	float	next_x = p->coord.x + g->velocity.x;
	float	next_y = p->coord.y + g->velocity.y;

	i = -1;
	while (++i < sect->num_vert)
		if (CTL(p->coord.x, p->coord.y, next_x, next_y, vert[i].x, vert[i].y, vert[i + 1].x, vert[i + 1].y))
		{
			nceil_p = m.sectors[(int)sect->neighbors[i]].ceil_plane;
			nfloor_p = m.sectors[(int)sect->neighbors[i]].floor_plane;
			hole_low  = sect->neighbors[i] < 0 ? BIG_VALUE : \
				max(get_z(floor_p, p->coord.x, p->coord.y), get_z(nfloor_p, next_x, next_y));
			hole_high = sect->neighbors[i] < 0 ? -BIG_VALUE : \
				min(get_z(ceil_p, p->coord.x, p->coord.y), get_z(nceil_p, next_x, next_y));
			if (hole_high > p->coord.z + HEAD_HEIGHT && \
				hole_low < p->coord.z - EYE_HEIGHT + KNEE_HEIGHT)
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
			}
		}
	g->dx = g->velocity.x;
	g->dy = g->velocity.y;
}

void		game_events(t_doom *d)
{
	t_game	*g;

	g = &d->game;
	g->eye_height = g->ducking ? SIT_EYE_HEIGHT : EYE_HEIGHT;
	g->ground = !g->falling;
	if (g->falling)
		fall(&d->player, d->map, &d->game);
	if (g->moving)
	{
		move(&d->player, d->map, &d->game);
		move_player(d, g->dx, g->dy);
		g->falling = 1;
	}
}
