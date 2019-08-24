/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:04:00 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/24 19:24:37 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		move_sprites(t_doom *d, float dx, float dy, t_sprite *spr)
{
	t_sector	*sect;
	t_vertex	*vert;
	float		hole_high;
	float		hole_low;

	INT_1(s);
	IVER2(p, next);
	sect = d->map.sectors + spr->sector_no;
	vert = sect->vert;
	p = (t_vertex){spr->coord.x, spr->coord.y};
	next = (t_vertex){spr->coord.x + dx, spr->coord.y + dy};
	hole_high = get_z(sect->ceil_plane, next.x, next.y);
	hole_low = get_z(sect->floor_plane, next.x, next.y);
	if (hole_high > spr->coord.z + spr->start_z \
		&& hole_low < spr->coord.z + spr->end_z)
	{
		while (++s < sect->num_vert)
			if (sect->neighbors[s] >= 0 && ctl(p, next, vert[s], vert[s + 1]))
				spr->sector_no = sect->neighbors[s];
		spr->coord.x += dx;
		spr->coord.y += dy;
	}
}

void		mob_hit_player(t_sprite *spr, t_doom *d)
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

void		chase(t_doom *d, t_sprite *spr)
{
	t_vertex	move_vector;
	float		len;
	t_sector	*sect;

	sect = d->map.sectors + spr->sector_no;
	move_vector = (t_vertex){d->player.coord.x - \
		spr->coord.x, d->player.coord.y - spr->coord.y};
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
	else if (comp_real(d->player.coord.z - d->game.eye_height, \
	spr->coord.z, 1) && spr->sector_no == (int)d->player.sector)
		mob_hit_player(spr, d);
}

void		get_sprite_for_mob(t_sprite *spr, t_doom *d)
{
	if (VXS(spr->anglecos, spr->anglesin, \
		d->player.anglecos, d->player.anglesin) > 0)
	{
		if (DVP(spr->anglecos, spr->anglesin, \
			d->player.anglecos, d->player.anglesin) < -1.0 / 2)
			spr->text_no = 0;
		else if (DVP(spr->anglecos, spr->anglesin, \
			d->player.anglecos, d->player.anglesin) < 1.0 / 2)
			spr->text_no = d->texture.sprt[spr->num_sheet].w;
		else
			spr->text_no = d->texture.sprt[spr->num_sheet].w * 2;
	}
	else
	{
		if (DVP(spr->anglecos, spr->anglesin, \
			d->player.anglecos, d->player.anglesin) < -1.0 / 2)
			spr->text_no = 0;
		else if (DVP(spr->anglecos, spr->anglesin, \
			d->player.anglecos, d->player.anglesin) < 1.0 / 2)
			spr->text_no = d->texture.sprt[spr->num_sheet].w * 3;
		else
			spr->text_no = d->texture.sprt[spr->num_sheet].w * 2;
	}
}

void		move_mobs(t_doom *d)
{
	t_vector	coord;
	t_sprite	*spr;

	INT_32(m);
	spr = d->map.sprites;
	while (++m < d->map.num_sprites)
	{
		if (spr[m].mob && spr[m].live)
		{
			coord = d->player.coord;
			coord.x -= spr[m].coord.x;
			coord.y -= spr[m].coord.y;
			rotate_vector_xy(&coord, spr[m].anglesin, spr[m].anglecos);
			if (coord.y < spr[m].vision_forward \
				&& coord.y > spr[m].vision_backward)
				chase(d, spr + m);
			else if (spr[m].own_moves > -1)
				d->changes.moves[spr[m].own_moves](d, spr + m);
			get_sprite_for_mob(spr + m, d);
		}
		else if (spr[m].mob && !spr[m].live)
			if (spr[m].death_time == 0)
				move_mobs_death(spr, d, m);
	}
}
