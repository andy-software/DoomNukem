/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:09:40 by apavlov           #+#    #+#             */
/*   Updated: 2019/07/31 12:09:41 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			turn_light_event(t_doom *d, t_painting *paint)
{
	if (paint->key_state == 1)
	{
		d->map.sectors[paint->sector_no].light_lvl = 60;
		paint->key_state = 0;
	}
	else
	{
		d->map.sectors[paint->sector_no].light_lvl = 20;
		paint->key_state = 1;
	}
	return (0);
}

int			lift_floor_event(t_doom *d, t_painting *paint)
{
	float	dist;
	float	*curr;

	if (paint->click)
	{
		paint->changes = 1;
		printf("1 %i\n", paint->key_state);
		paint->key_state = !paint->key_state;
		printf("2 %i\n", paint->key_state);
		paint->click = 0;
	}
	if (paint->changes)
	{
		curr = &d->map.sectors[paint->num_of_sect_to_lift].floor_plane.h;
		printf("3 %i\n", paint->key_state);
		dist = paint->speed * d->game.dt / 500.f * (paint->key_state - 0.5f);
		*curr += dist;
		if (*curr > paint->low_point)
		{
			*curr = min(*curr, paint->low_point);
			paint->changes = 0;
		}
		else if (*curr < paint->high_point)
		{
			*curr = max(*curr, paint->high_point);
			paint->changes = 0;
		}		
	}
	return (1);
}

int			lift_ceil_event(t_doom *d, t_painting *paint)
{
	float	dist;
	float	*curr;

	if (paint->changes == 0)
	{
		paint->changes = 1;
		paint->key_state = !paint->key_state;
	}
	else
	{
		curr = &d->map.sectors[paint->num_of_sect_to_lift].ceil_plane.h;
		dist = paint->speed * d->game.dt / 500.f * (paint->key_state - 0.5f);
		*curr += dist;
		if (paint->high_point < *curr && *curr > paint->low_point)
		{
			*curr = clamp(*curr, paint->high_point, paint->low_point);
			paint->changes = 0;
		}
	}
	return (1);
}

int			first_aid_event(t_doom *d, t_painting *paint)
{
	if (paint->charge > 0)
	{
		d->game.hp_level++;
		paint->changes--;
	}
	return (0);
}

int			get_ammo_event(t_doom *d, t_painting *paint)
{
	if (paint->charge > 0)
	{
		d->ui.ammo_1++;
		paint->changes--;
	}
	return (0);
}

int			win_pnt_event(t_doom *d, t_painting *paint)
{
	(void)d;
	(void)paint;
	exit(1);
	return (0);
}