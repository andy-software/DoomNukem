/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:59:21 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/10 11:41:12 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		check_keys_intersection(t_doom *d)
{
	int				i;
	t_vector		t1;
	t_vector		t2;
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
		if (t1.x > 0 && t2.x < 0)
			if (t1.y < MAX_RANGE_SPRITE_CLICKING)
				if (t1.z + t1.y * d->player.angle_z > 0 && \
					t2.z + t1.y * d->player.angle_z < 0)
					ev(d, d->sr.sprites + i);
	}
}

void		check_painting_intersection(t_doom *d)
{
	int				i;
	t_vector		t1;
	t_vector		t2;
	pnt_event_type	ev;
	t_vertex		inter;

	i = -1;
	while (++i < (int)d->map.num_paint)
	{
		ev = d->changes.pnt_events[d->map.paint[i].event_num];
		if (!d->map.paint[i].key)
			continue ;
		d->map.paint->click = 0;
		paint_vert_cal(&t1, &t2, d->map.paint + i, d->player);
		if (t1.y < 0 && t1.y < 0)
			continue ;
		if (t1.x * t2.x > 0)
			continue ;
		inter = intersect(vec_to_ver(t1), vec_to_ver(t2), (t_vertex){0, 0}, (t_vertex){0, 10});
		if (inter.y > 0 && inter.y < MAX_RANGE_SPRITE_CLICKING)
			if (t1.z + t1.y * d->player.angle_z > 0 && t2.z + t2.y * d->player.angle_z < 0)
			{
				d->map.paint[i].click = 1;
				ev(d, d->map.paint + i);
			}
	}
}

void		check_keys_state(t_doom *d)
{
	int				i;
	pnt_event_type	pnt_ev;
	spr_event_type	spr_ev;

	i = -1;
	while (++i < (int)d->map.num_paint)
		if (d->map.paint[i].key && d->map.paint[i].changes)
		{
			pnt_ev = d->changes.pnt_events[d->map.paint[i].event_num];
			pnt_ev(d, d->map.paint + i);
		}
	i = -1;
	while (++i < (int)d->map.num_sprites) /// FIX
		if (d->map.sprites[i].key && d->map.sprites[i].changes)
		{
			spr_ev = d->changes.spr_events[d->map.sprites[i].event_num];
			spr_ev(d, d->map.sprites + i);
		}
}
