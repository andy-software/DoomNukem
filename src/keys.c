/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:59:21 by apavlov           #+#    #+#             */
/*   Updated: 2019/07/29 13:59:22 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		check_keys_intersection(t_doom *d) //should be another events like talking
{
	int			i;
	t_vector	t1;
	t_vector	t2;
	spr_event_type	ev;

	i = -1;
	while (++i < (int)d->map.num_sprites)
		if (d->sr.sprites[i].coord.y < 0)
			break ;
	while (--i >= 0)
	{
		ev = d->changes.spr_events[d->sr.sprites[i].event_num];
		if (!d->sr.sprites[i].key)
			continue ;
		sprite_vert_cal(&t1, &t2, d->sr.sprites + i, d->player);
		if (d->sr.sprites[i].key_state && ev == talk_event)
		{
			printf("I keep talking\n");
		}
		else if (t1.x > 0 && t2.x < 0)
			if (t1.y < MAX_RANGE_SPRITE_CLICKING)
				if (t1.z + t1.y * d->player.angle_z > 0 && t2.z + t1.y * d->player.angle_z < 0)
					d->sr.sprites[i].key_state = ev(d, d->sr.sprites + i);
	}
}

void		check_painting_intersection(t_doom *d) //should do what sprites do right now
{
	int			i;
	t_vector	t1;
	t_vector	t2;
	pnt_event_type	ev;

	i = -1;
	while (++i < (int)d->map.num_paint);

	while (--i >= 0)
	{
		ev = d->changes.pnt_events[d->map.paint[i].event_num];
		if (!d->map.paint[i].key)
			continue ;
		t1.x = d->map.paint[i].v1.x - d->player.coord.x;
		t1.y = d->map.paint[i].v1.y - d->player.coord.y;
		t2.x = d->map.paint[i].v2.x - d->player.coord.x;
		t2.y = d->map.paint[i].v2.y - d->player.coord.y;
		t1.z = d->map.paint[i].v1.z - d->player.coord.z;
		t2.z = d->map.paint[i].v2.z - d->player.coord.z;
		rotate_vector_xy(&t1, d->player.anglesin, d->player.anglecos);
		rotate_vector_xy(&t2, d->player.anglesin, d->player.anglecos);
		if (d->map.paint[i].key_state && (ev == lift_floor_event || ev == lift_ceil_event))
		{
			printf("Im lifting\n");
		}
		else if (t1.x > 0 && t2.x < 0)
			if (t1.y < MAX_RANGE_SPRITE_CLICKING) //not right but keep that
				if (t1.z + t1.y * d->player.angle_z > 0 && t2.z + t2.y * d->player.angle_z < 0)
					d->map.paint[i].key_state = ev(d, d->map.paint + i);
	}
}