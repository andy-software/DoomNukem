/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changes_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:15:58 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/24 19:38:50 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		move_mobs_death(t_sprite *spr, t_doom *d, int m)
{
	spr[m].text_no = d->texture.sprt[spr[m].num_sheet].w * 4;
	spr[m].death_time = d->ui.prevTime;
}

void		sprite_coordin(t_sprite *spr, t_vertex *vert, t_vertex next, int i)
{
	t_vertex	vertex;

	vertex = intersect((t_vertex){spr->coord.x, spr->coord.y}, \
			next, vert[i], vert[i + 1]);
	spr->coord.x = vertex.x;
	spr->coord.y = vertex.y;
	spr->anglecos *= -1;
	spr->anglesin *= -1;
	spr->angle = find_angle_2pi(spr->anglesin, spr->anglecos);
}

int			first_own_moves(t_doom *d, t_sprite *spr)
{
	t_sector	*sect;
	t_vertex	*vert;
	t_vertex	next;

	INT_2(i, moved);
	sect = d->map.sectors + spr->sector_no;
	vert = sect->vert;
	spr->speed_x = spr->anglecos * spr->move_speed;
	spr->speed_y = spr->anglesin * spr->move_speed;
	next = (t_vertex){spr->coord.x + spr->speed_x, spr->coord.y + spr->speed_y};
	moved = 0;
	while (++i < (int)sect->num_vert)
	{
		if (ctl((t_vertex){spr->coord.x, spr->coord.y}, \
				next, vert[i], vert[i + 1]))
		{
			sprite_coordin(spr, vert, next, i);
			moved = 1;
			break ;
		}
	}
	if (!moved && (spr->coord.x = next.x))
		spr->coord.y = next.y;
	spr->coord.z = get_z(sect->floor_plane, spr->coord.x, spr->coord.y);
	return (1);
}

void		spite_coord_mirror(t_sprite *spr, t_vertex *vert, t_vertex next, int i)
{
	float		len;
	float		prev_cos;
	float		prev_sin;
	float		scalar_prod;

	IVER3(vertex, norm_to_wall, wall_vector);
	vertex = intersect((t_vertex){spr->coord.x, spr->coord.y}, \
			next, vert[i], vert[i + 1]);
	spr->coord.x = vertex.x;
	spr->coord.y = vertex.y;
	wall_vector = (t_vertex){vert[i + 1].x - vert[i].x, \
			vert[i + 1].y - vert[i].y};
	len = v2dlenght(wall_vector.x, wall_vector.y);
	norm_to_wall = (t_vertex){wall_vector.y / len, -wall_vector.x / len};
	prev_cos = spr->anglecos;
	prev_sin = spr->anglesin;
	scalar_prod = 2 * (prev_cos * norm_to_wall.x + prev_sin * norm_to_wall.y);
	spr->anglecos = prev_cos - scalar_prod * norm_to_wall.x;
	spr->anglesin = prev_sin - scalar_prod * norm_to_wall.y;
	spr->angle = find_angle_2pi(spr->anglesin, spr->anglecos);
}

int			mirror_own_moves(t_doom *d, t_sprite *spr)
{
	t_sector	*sect;
	t_vertex	*vert;
	t_vertex	next;

	INT_2(i, moved);
	sect = d->map.sectors + spr->sector_no;
	vert = sect->vert;
	spr->speed_x = spr->anglecos * spr->move_speed;
	spr->speed_y = spr->anglesin * spr->move_speed;
	next = (t_vertex){spr->coord.x + spr->speed_x, spr->coord.y + spr->speed_y};
	moved = 0;
	while (++i < (int)sect->num_vert)
	{
		if (ctl((t_vertex){spr->coord.x, spr->coord.y}, \
				next, vert[i], vert[i + 1]))
		{
			spite_coord_mirror(spr, vert, next, i);
			moved = 1;
			break ;
		}
	}
	if (!moved && (spr->coord.x = next.x))
		spr->coord.y = next.y;
	spr->coord.z = get_z(sect->floor_plane, spr->coord.x, spr->coord.y);
	return (1);
}
