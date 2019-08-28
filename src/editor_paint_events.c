/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_paint_events.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:20:42 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/28 18:37:48 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		normalniy_l_fl_event(t_doom *d, t_painting *paint)
{
	float	dist;
	float	*curr;
	static	int lift;

	lift = 0;
	if (paint->click == 1)
	{
			paint->changes = 1;
			paint->key_state = !paint->key_state;
			paint->click = 0;
	}
	if (paint->changes)
	{
		if (!(Mix_Playing(2)))
			Mix_PlayChannel(2, d->sound.lift[2], 0);
		curr = &d->map.sectors[paint->num_of_sect_to_lift].floor_plane.h;
		dist = paint->speed * d->game.dt / 500.f * (paint->key_state - 0.5f);
		*curr += dist;
		paint->changes = 0;
		if (*curr > paint->low_point && paint->key_state == 1)
			*curr = MIN(*curr, paint->low_point);
		else if (*curr < paint->high_point && paint->key_state == 0)
			*curr = MAX(*curr, paint->high_point);
		else
			paint->changes = 1;
	}
	return (1);
}