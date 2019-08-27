/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:09:40 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/23 16:45:25 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		inverse_colors_event(t_doom *d, t_painting *paint)
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

int		turn_light_event(t_doom *d, t_painting *paint)
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

int		radio_event(t_doom *d, t_painting *paint)
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

int		lift_floor_event(t_doom *d, t_painting *paint)
{
	float	dist;
	float	*curr;
	static	int lift;

	lift = 0;
	if (paint->click == 1)
	{
		if (d->game.access == 1)
		{
			if (!(Mix_Playing(2)))
				Mix_PlayChannel(2, d->sound.lift[0], 0);
			lift = 1;
		}
		if (lift == 1)
		{
			paint->changes = 1;
			paint->key_state = !paint->key_state;
			paint->click = 0;
		}
		else
			if (!(Mix_Playing(2)))
				Mix_PlayChannel(2, d->sound.lift[1], 0);
	}
	if (paint->changes)
	{
		if (!(Mix_Playing(2)))
			Mix_PlayChannel(2, d->sound.lift[2], 0);
		curr = &d->map.sectors[paint->num_of_sect_to_lift].floor_plane.h;
		dist = paint->speed * d->game.dt / 500.f * (paint->key_state - 0.5f);
		*curr += dist;
		paint->changes = 0;
		if (*curr > paint->low_point  && paint->key_state == 1)
			*curr = MIN(*curr, paint->low_point);
		else if (*curr < paint->high_point && paint->key_state == 0)
			*curr = MAX(*curr, paint->high_point);
		else
			paint->changes = 1;
	}
	return (1);
}

int		lift_ceil_event(t_doom *d, t_painting *paint)
{
	float	dist;
	float	*curr;
	static	int lift;

	lift = 0;
	if (paint->click == 1)
	{
		if (d->game.access == 1)
		{
			if (!(Mix_Playing(2)))
				Mix_PlayChannel(2, d->sound.lift[0], 0);
			lift = 1;
		}
		if (lift == 1)
		{
			paint->changes = 1;
			paint->key_state = !paint->key_state;
			paint->click = 0;
		}
		else
			if (!(Mix_Playing(2)))
				Mix_PlayChannel(2, d->sound.lift[1], 0);
	}
	if (paint->changes)
	{
		if (!(Mix_Playing(2)))
			Mix_PlayChannel(2, d->sound.lift[2], 0);
		curr = &d->map.sectors[paint->num_of_sect_to_lift].ceil_plane.h;
		dist = paint->speed * d->game.dt / 500.f * (paint->key_state - 0.5f);
		*curr += dist;
		paint->changes = 0;
		if (*curr > paint->low_point)
			*curr = MIN(*curr, paint->low_point);
		else if (*curr < paint->high_point)
			*curr = MAX(*curr, paint->high_point);
		else
			paint->changes = 1;
	}
	return (1);
}
