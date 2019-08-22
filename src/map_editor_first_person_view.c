/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor_first_person_view.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:01:16 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 14:48:28 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		check_what_line_player_are_looking(t_doom *d)
{
	int			v;
	t_sector	*sect;
	t_vertex	t1;
	t_vertex	t2;

	sect = d->map.sectors + d->player.sector;
	v = -1;
	while (++v < (int)sect->num_vert)
	{
		t1.x = sect->vert[v].x - d->player.coord.x;
		t1.y = sect->vert[v].y - d->player.coord.y;
		t2.x = sect->vert[v + 1].x - d->player.coord.x;
		t2.y = sect->vert[v + 1].y - d->player.coord.y;
		rotate_vertex_xy(&t1, d->player.anglesin, d->player.anglecos);
		rotate_vertex_xy(&t2, d->player.anglesin, d->player.anglecos);
		if (t1.y < 0 && t2.y < 0)
			continue;
		if (t1.x > 0 && t2.x < 0)
			return (v);
	}
	return (-1);
}

int		check_what_sprite_player_are_looking(t_doom *d)
{
	int			s;
	t_vector	t1;
	t_vector	t2;
	t_sprite	*spr;

	s = -1;
	while (++s < (int)d->map.num_sprites)
		if (d->sr.sprites[s].coord.y < 0)
			break ;
	while (--s >= 0)
	{
		spr = d->sr.sprites + s;
		sprite_vert_cal(&t1, &t2, spr, d->player);
		if (t1.x > 0 && t2.x < 0)
			if (t1.z + t1.y * d->player.angle_z > 0 \
					&& t2.z + t1.y * d->player.angle_z < 0)
				return (spr->spr_num);
	}
	return (-1);
}

int		check_what_paint_player_are_looking(t_doom *d)
{
	int			p;
	t_vector	t1;
	t_vector	t2;
	t_painting	*pnt;
	t_vertex	inter;

	p = -1;
	while (++p < (int)d->map.num_paint)
	{
		pnt = d->map.paint + p;
		if (pnt->sector_no != (int)d->player.sector)
			continue ;
		paint_vert_cal(&t1, &t2, pnt, d->player);
		if (t1.y < 0 && t2.y < 0)
			continue ;
		if (t1.x * t2.x > 0)
			continue ;
		inter = intersect(vec_to_ver(t1), vec_to_ver(t2), \
			(t_vertex){0, 0}, (t_vertex){0, 10});
		if (inter.y > 0)
			if (t1.z + t1.y * d->player.angle_z > 0 \
					&& t2.z + t2.y * d->player.angle_z < 0)
				return (p);
	}
	return (-1);
}
