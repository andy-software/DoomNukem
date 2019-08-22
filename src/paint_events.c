/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:09:40 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/14 19:14:29 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			inverse_colors_event(t_doom *d, t_painting *paint)
{
	if (paint->key_state == 1)
	{
		d->map.inverse_colors = !d->map.inverse_colors;
		paint->key_state = 0;
	}
	else
	{
		d->map.inverse_colors = !d->map.inverse_colors;
		paint->key_state = 1;
	}
	return (0);
}

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

int			radio_event(t_doom *d, t_painting *paint)
{
	static int	mus_num = -1;

	if (paint->key_state == 0)
		paint->key_state = 1;
	if (paint->key_state)
	{
		if (!(Mix_PlayingMusic()))
			Mix_PlayMusic(d->sound.music[++mus_num], 1);
		else if ((Mix_PlayingMusic() && d->game.click))
			Mix_PlayMusic(d->sound.music[++mus_num], 1);
		if (mus_num >= 6)
		{
			Mix_PauseMusic();
			mus_num = -1;
		}

	}
	return (1);
}

int			lift_floor_event(t_doom *d, t_painting *paint)
{
	float	dist;
	float	*curr;

		printf("we are here %f\n", *curr);
	if (paint->click == 1)
	{
		paint->changes = 1;
		paint->key_state = !paint->key_state;
		paint->click = 0;
	}
	if (paint->changes)
	{
		curr = &d->map.sectors[paint->num_of_sect_to_lift].floor_plane.h;
		dist = paint->speed * d->game.dt / 500.f * (paint->key_state - 0.5f);
		*curr += dist;
		paint->changes = 0;
		if (*curr > paint->low_point  && paint->key_state == 1)
		{
			printf("Where are stoping at low point %f\n", *curr);
			*curr = min(*curr, paint->low_point);
			printf("Where are stoping at low point %f\n", *curr);
			fflush(stdout);
		}
		else if (*curr < paint->high_point && paint->key_state == 0)
		{
			printf("Where are stoping at high point %f\n", *curr);
			*curr = max(*curr, paint->high_point);
			printf("Where are stoping at high point %f\n", *curr);
			fflush(stdout);
		}
		else
		{
			printf("Where are changes at high point %f\n", *curr);
			paint->changes = 1;
		}
	}
	return (1);
}

int			lift_ceil_event(t_doom *d, t_painting *paint)
{
	float	dist;
	float	*curr;

	if (paint->click == 1)
	{
		paint->changes = 1;
		paint->key_state = !paint->key_state;
		paint->click = 0;
	}
	else
	{
		curr = &d->map.sectors[paint->num_of_sect_to_lift].ceil_plane.h;
		dist = paint->speed * d->game.dt / 500.f * (paint->key_state - 0.5f);
		*curr += dist;
		paint->changes = 0;
		if (*curr > paint->low_point)
			*curr = min(*curr, paint->low_point);
		else if (*curr < paint->high_point)
			*curr = max(*curr, paint->high_point);
		else
			paint->changes = 1;
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
