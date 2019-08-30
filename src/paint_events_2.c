/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_events_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 17:10:45 by mmasyush          #+#    #+#             */
/*   Updated: 2019/08/30 17:10:46 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	click_paint(t_doom *d, t_painting *paint)
{
	paint->changes = 1;
	paint->key_state = !paint->key_state;
	paint->click = 0;
	if (!(Mix_Playing(2)))
		Mix_PlayChannel(2, d->sound.lift[1], 0);
}

void	click_paint_lock(t_doom *d, t_painting *paint)
{
	static	int lift;

	lift = 0;
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
	else if (!(Mix_Playing(2)))
		Mix_PlayChannel(2, d->sound.lift[1], 0);
}

int		lift_block_event(t_doom *d, t_painting *paint)
{
	float		dist;
	float		*curr;

	if (paint->click == 1)
		click_paint_lock(d, paint);
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
