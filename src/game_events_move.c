/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanylch <mdanylch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 20:09:52 by mdanylch          #+#    #+#             */
/*   Updated: 2019/08/27 20:10:21 by mdanylch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static	void	move_calc_2(t_player *p, t_game *g, t_move *go)
{
	project_vector2d(&g->velocity.x, &g->velocity.y, go->vert[go->i + 1].x - \
		go->vert[go->i].x, go->vert[go->i + 1].y - go->vert[go->i].y);
	INIT2(g->moving, 0, go->j, -1);
	go->next.x = p->coord.x + g->velocity.x;
	go->next.y = p->coord.y + g->velocity.y;
	while (++go->j < (int)go->sect->num_vert)
	{
		if (go->j != go->i && ctl((t_vertex){p->coord.x, p->coord.y}, \
			go->next, go->vert[go->j], go->vert[go->j + 1]))
		{
			go->hole_low = go->sect->neighbors[go->i] < 0 ? BIG_VALUE : \
				MAX(get_z(go->floor_p, p->coord.x, p->coord.y), \
				get_z(go->nfloor_p, go->next.x, go->next.y));
			go->hole_high = go->sect->neighbors[go->i] < 0 ? -BIG_VALUE : \
						MIN(get_z(go->ceil_p, p->coord.x, p->coord.y), \
						get_z(go->nceil_p, go->next.x, go->next.y));
			if (!(go->hole_high > p->coord.z + HEAD_HEIGHT && \
			go->hole_low < p->coord.z - g->eye_height + KNEE_HEIGHT))
			{
				g->velocity = (t_vector){0, 0, g->velocity.z};
				break ;
			}
		}
	}
}

static	void	move_calc_1(t_player *p, t_map m, t_move *go)
{
	if (go->sect->neighbors[go->i] < 0)
	{
		go->hole_low = BIG_VALUE;
		go->hole_high = -BIG_VALUE;
		go->nceil_p = m.sectors[0].ceil_plane;
		go->nfloor_p = m.sectors[0].floor_plane;
	}
	else
	{
		go->nceil_p = m.sectors[(int)go->sect->neighbors[go->i]].ceil_plane;
		go->nfloor_p = m.sectors[(int)go->sect->neighbors[go->i]].floor_plane;
		go->hole_low = MAX(get_z(go->floor_p, p->coord.x, p->coord.y),\
			get_z(go->nfloor_p, go->next.x, go->next.y));
		go->hole_high = MIN(get_z(go->ceil_p, p->coord.x, p->coord.y),\
			get_z(go->nceil_p, go->next.x, go->next.y));
	}
}

void			move(t_player *p, t_map m, t_game *g)
{
	t_move		go;

	go.i = -1;
	go.sect = m.sectors + p->sector;
	go.vert = go.sect->vert;
	go.ceil_p = m.sectors[p->sector].ceil_plane;
	go.floor_p = m.sectors[p->sector].floor_plane;
	go.next = (t_vertex){p->coord.x + g->velocity.x, p->coord.y + \
		g->velocity.y};
	while (++go.i < (int)go.sect->num_vert)
		if (ctl((t_vertex){p->coord.x, p->coord.y}, go.next, go.vert[go.i], \
			go.vert[go.i + 1]))
		{
			move_calc_1(p, m, &go);
			if (!(go.hole_high > p->coord.z + HEAD_HEIGHT && \
				go.hole_low < p->coord.z - g->eye_height + KNEE_HEIGHT))
			{
				move_calc_2(p, g, &go);
				if (go.j != (int)go.sect->num_vert)
					break ;
			}
		}
	INIT2(g->dx, g->velocity.x, g->dy, g->velocity.y);
}
