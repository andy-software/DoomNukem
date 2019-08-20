/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:04:00 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/09 17:15:35 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		move_sprites(t_doom *d, float dx, float dy, t_sprite *spr)
{
	float px = spr->coord.x;
	float py = spr->coord.y;
	t_sector *sect = d->map.sectors + spr->sector_no;
	t_vertex *vert = sect->vert;
	float hole_high = get_z(sect->ceil_plane, px + dx, py + dy);
	float hole_low = get_z(sect->floor_plane, px + dx, py + dy);

	if (hole_high > spr->coord.z + spr->start_z && hole_low < spr->coord.z + spr->end_z)
	{
		for(unsigned s = 0; s < sect->num_vert; s++)
			if(sect->neighbors[s] >= 0 && CTL(px, py, px + dx, py + dy, \
				vert[s].x, vert[s].y, vert[s + 1].x, vert[s + 1].y))
			{
				spr->sector_no = sect->neighbors[s];
			}
		spr->coord.x += dx;
		spr->coord.y += dy;
	}
}

int			first_own_moves(t_doom *d, t_sprite *spr)
{
	float	next_x;
	float	next_y;
	Uint32		i;
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
	Uint32		i;
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
			norm_to_wall = (t_vertex){wall_vector.y / len, -wall_vector.x / len};
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
	spr->coord.z = get_z(sect->floor_plane, spr->coord.x, spr->coord.y);
	return (1);
}

void		chase(t_doom *d, t_sprite *spr)
{
	t_vertex	move_vector;
	float		len;
	t_sector	*sect;

	sect = d->map.sectors + spr->sector_no;
	move_vector = (t_vertex){d->player.coord.x - spr->coord.x, d->player.coord.y - spr->coord.y};
	len = v2dlenght(move_vector.x, move_vector.y);
	move_vector.x /= len;
	move_vector.y /= len;

	spr->anglecos = move_vector.x;
	spr->anglesin = move_vector.y;
	spr->angle = find_angle_2pi(spr->anglesin, spr->anglecos);
	if (len > ATTACK_RANGE)
	{
		spr->speed_x = spr->anglecos * spr->move_speed;
		spr->speed_y = spr->anglesin * spr->move_speed;
		move_sprites(d, spr->speed_x, spr->speed_y, spr);
		spr->coord.z = get_z(sect->floor_plane, spr->coord.x, spr->coord.y);
	}
	else if (comp_real(d->player.coord.z - d->game.eye_height, spr->coord.z, 1) && spr->sector_no == (int)d->player.sector)
	{
		if (!(Mix_Playing(2)))
			Mix_PlayChannel(2, d->sound.hurt, 0);
		if (spr->num_sheet == 8)
			d->game.hp_level -= 2 * d->difficulty;
		else if (spr->num_sheet == 6)
			d->game.hp_level -= 0.5 * d->difficulty;
		else if (spr->num_sheet == 5)
			d->game.hp_level -= 1 * d->difficulty;
	}
}

void		get_sprite_for_mob(t_sprite	*spr, t_doom *d)
{
	if (vxs(spr->anglecos, spr->anglesin, d->player.anglecos, d->player.anglesin) > 0)
	{
		if (dvp(spr->anglecos, spr->anglesin, d->player.anglecos, d->player.anglesin) < -1.0 / 2)
			spr->text_no = 0;
		else if (dvp(spr->anglecos, spr->anglesin, d->player.anglecos, d->player.anglesin) < 1.0 / 2)
			spr->text_no = d->texture.sprt[spr->num_sheet].w;
		else
			spr->text_no = d->texture.sprt[spr->num_sheet].w * 2;
	}
	else 
	{
		if (dvp(spr->anglecos, spr->anglesin, d->player.anglecos, d->player.anglesin) < -1.0 / 2)
			spr->text_no = 0;
		else if (dvp(spr->anglecos, spr->anglesin, d->player.anglecos, d->player.anglesin) < 1.0 / 2)
			spr->text_no =  d->texture.sprt[spr->num_sheet].w * 3;
		else
			spr->text_no = d->texture.sprt[spr->num_sheet].w * 2;
	}
}

void		move_mobs(t_doom *d)
{
	Uint32		m;
	t_vector	coord;
	t_sprite	*spr;

	m = -1;
	spr = d->map.sprites;
	while (++m < d->map.num_sprites)
	{
		if (spr[m].mob && spr[m].live)
		{
			coord = d->player.coord;
			coord.x -= spr[m].coord.x;
			coord.y -= spr[m].coord.y;

			rotate_vector_xy(&coord, spr[m].anglesin, spr[m].anglecos);
			if (coord.y < spr[m].vision_forward && coord.y > spr[m].vision_backward)
				chase(d, spr + m);
			else if (spr[m].own_moves > -1)
				d->changes.moves[spr[m].own_moves](d, spr + m);
			get_sprite_for_mob(spr + m, d);
		}
		else if (spr[m].mob && !spr[m].live)
		{
			if (spr[m].death_time == 0)
			{
				spr[m].text_no = d->texture.sprt[spr[m].num_sheet].w * 4;
				spr[m].death_time = d->ui.prevTime;
			}
		}
	}
}