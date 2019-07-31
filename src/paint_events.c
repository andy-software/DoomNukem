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
	return (1);
}

int			lift_ceil_event(t_doom *d, t_painting *paint)
{
	return (1);
}

int			first_aid_event(t_doom *d, t_painting *paint)
{
	d->game.hp_level--;
	return (0);
}

int			get_ammo_event(t_doom *d, t_painting *paint)
{
	d->ui.ammo_1++;
	return (0);
}

int			win_pnt_event(t_doom *d, t_painting *paint)
{
	exit(1);
	return (0);
}