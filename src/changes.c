/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:04:00 by apavlov           #+#    #+#             */
/*   Updated: 2019/07/17 18:04:01 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			first_own_moves(t_doom *d, t_sprite *spr)
{
	float	next_x;
	float	next_y;
	int		i;
	t_sector	*sect;
	t_vertex	*vert;
	t_vertex	vertex;
	int			moved;

	sect = d->map.sectors + spr->sector_no;
	vert = sect->vert;
	spr->speed_x = spr->anglecos * spr->move_speed;
	spr->speed_y = spr->anglesin * spr->move_speed;
	

	next_x = spr->coord.x + spr->speed_x;
	next_y = spr->coord.y + spr->speed_y;

	i = -1;
	moved = 0;
	while (++i < sect->num_vert)
	{
		if (CTL(spr->coord.x, spr->coord.y, next_x, next_y, vert[i].x, vert[i].y, vert[i + 1].x, vert[i + 1].y))
		{
			vertex = intersect((t_vertex){spr->coord.x, spr->coord.y}, (t_vertex){next_x, next_y}, (t_vertex){vert[i].x, vert[i].y}, (t_vertex){vert[i + 1].x, vert[i + 1].y});
			spr->coord.x = vertex.x;
			spr->coord.y = vertex.y;
			spr->anglecos *= -1;
			spr->anglesin *= -1;
			spr->angle = find_angle_2pi(spr->anglesin, spr->anglecos);
			moved = 1;
			break ;
		}
	}
	if (!moved)
	{
		spr->coord.x = next_x;
		spr->coord.y = next_y;
	}

	spr->coord.z = get_z(sect->floor_plane, spr->coord.x, spr->coord.y);
	return (1);
}

int			mirror_own_moves(t_doom *d, t_sprite *spr)
{
	float	next_x;
	float	next_y;
	int		i;
	t_sector	*sect;
	t_vertex	*vert;
	t_vertex	vertex;
	int			moved;
	float		scalar_prod;
	t_vertex	wall_vector;
	t_vertex	norm_to_wall;
	float		len;
	float		prev_cos;
	float		prev_sin;

	sect = d->map.sectors + spr->sector_no;
	vert = sect->vert;
	spr->speed_x = spr->anglecos * spr->move_speed;
	spr->speed_y = spr->anglesin * spr->move_speed;
	

	next_x = spr->coord.x + spr->speed_x;
	next_y = spr->coord.y + spr->speed_y;

	i = -1;
	moved = 0;
	while (++i < sect->num_vert)
	{
		if (CTL(spr->coord.x, spr->coord.y, next_x, next_y, vert[i].x, vert[i].y, vert[i + 1].x, vert[i + 1].y))
		{
			vertex = intersect((t_vertex){spr->coord.x, spr->coord.y}, (t_vertex){next_x, next_y}, (t_vertex){vert[i].x, vert[i].y}, (t_vertex){vert[i + 1].x, vert[i + 1].y});
			spr->coord.x = vertex.x;
			spr->coord.y = vertex.y;
			wall_vector = (t_vertex){vert[i + 1].x - vert[i].x, vert[i + 1].y - vert[i].y};
			len = v2dlenght(wall_vector.x, wall_vector.y);
			norm_to_wall = (t_vertex){wall_vector.y / len, -wall_vector.x / len}; // does it need to be lenght 1?
			prev_cos = spr->anglecos;
			prev_sin = spr->anglesin;
			scalar_prod = 2 * (prev_cos * norm_to_wall.x + prev_sin * norm_to_wall.y);
			spr->anglecos = prev_cos - scalar_prod * norm_to_wall.x;
			spr->anglesin = prev_sin - scalar_prod * norm_to_wall.y;
			
			spr->angle = find_angle_2pi(spr->anglesin, spr->anglecos);
			moved = 1;

			break ;
		}
	}
	if (!moved)
	{
		spr->coord.x = next_x;
		spr->coord.y = next_y;
	}
	if (dvp(spr->anglecos, spr->anglesin, d->player.anglecos, d->player.anglesin) > 0)
		spr->text_no = 9;
	else if (dvp(spr->anglecos, spr->anglesin, d->player.anglecos, d->player.anglesin) < 0)
		spr->text_no = 0;
	else if (vxs(spr->anglecos, spr->anglesin, d->player.anglecos, d->player.anglesin) < 0)
		spr->text_no = 3;
	else
		spr->text_no = 6;
	spr->coord.z = get_z(sect->floor_plane, spr->coord.x, spr->coord.y);
	return (1);
}


void		move_sprite(t_doom *d, t_sprite *spr, t_vector coord)
{

}

void		move_mobs(t_doom *d)
{
	int			m;
	t_vector	coord;
	t_sprite	*spr;

	m = -1;
	spr = d->map.sprites;
	while (++m < d->map.num_sprites)
	{
		if (spr[m].mob && spr[m].draw)
		{
			coord = d->player.coord;
			coord.x -= spr[m].coord.x;
			coord.y -= spr[m].coord.y;

			rotate_vector_xy(&coord, spr[m].anglesin, spr[m].anglecos); //anglesin, anglecos -1, 0, 1
			// if (coord.y < 1 && coord.y > -1) // max vision rate forward and min backward // should also check if not a wall
			// 	move_sprite(d, spr + m, coord);
			if (spr[m].own_moves > -1)
				d->changes.moves[spr[m].own_moves](d, spr + m);
		}
	}
}