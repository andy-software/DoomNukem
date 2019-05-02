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
	float px;
	float py;
	t_sector *sect;
	t_vertex *vert;

	py = d->player.coord.y;
	px = d->player.coord.x;
	sect = &d->map.sectors[d->player.sector];
	vert = sect->vert;
	for(unsigned s = 0; s < sect->num_vert; s++)
		if(sect->neighbors[s] >= 0 && CTL(px, py, px + dx, py + dy, \
			vert[s].x, vert[s].y, vert[s + 1].x, vert[s + 1].y))
		{
			d->player.sector = sect->neighbors[s];
		}
	d->player.coord.x += dx;
	d->player.coord.y += dy;
}

static void	fall(t_player *p, t_map	m, t_game *g)
{
	const float nextz = p->coord.z + g->velocity.z;

	g->velocity.z -= 0.02f;
	if (g->velocity.z < 0 && \
		nextz <= m.sectors[p->sector].floor_z + g->eye_height)
	{
		p->coord.z = m.sectors[p->sector].floor_z + g->eye_height;
		g->velocity.z = 0;
		g->falling = 0;
		g->ground = 1;
	}
	else if(g->velocity.z > 0 && nextz > m.sectors[p->sector].ceil_z)
	{
		g->velocity.z = 0;
		g->falling = 1;
	}
	if (g->falling)
	{
		p->coord.z += g->velocity.z;
		p->angle_z -= 0.3 * g->velocity.z; //optional
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
	static int a = 0;

	i = -1;
	while (++i < sect->num_vert)
		if (CTL(p->coord.x, p->coord.y, p->coord.x + g->velocity.x, \
			p->coord.y + g->velocity.y, vert[i].x, vert[i].y, \
			vert[i + 1].x, vert[i + 1].y))
		{
			hole_low  = sect->neighbors[i] < 0 ? BIG_VALUE : \
				max(sect->floor_z, m.sectors[(int)sect->neighbors[i]].floor_z);
			hole_high = sect->neighbors[i] < 0 ? -BIG_VALUE : \
				min(sect->ceil_z,  m.sectors[(int)sect->neighbors[i]].ceil_z);
			if (hole_high < p->coord.z + HEAD_HEIGHT && \
				hole_low > p->coord.z - EYE_HEIGHT + KNEE_HEIGHT)
			{
				project_vector2d(&g->velocity.x, &g->velocity.y, \
					vert[i + 1].x - vert[i].x, vert[i + 1].y - vert[i].y);
				g->moving = 0;
			}
			else
			{
				printf("neightbor to player sector : %i kappa int %i\n", sect->neighbors[i], a++);
				printf("{%f, %f}\n", p->coord.x, p->coord.y);
				fflush(stdout);
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
