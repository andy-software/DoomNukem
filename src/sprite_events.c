/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:09:33 by apavlov           #+#    #+#             */
/*   Updated: 2019/07/31 12:09:34 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			win_spr_event(t_doom *d, t_sprite *sprite)
{
	(void)d;
	(void)sprite;
	exit(1);
	return (0);
}

int			talk_event(t_doom *d, t_sprite *sprite)
{
	if (sprite->changes == 0)
	{
		d->map.sprites[sprite->spr_num].speed_x = 0;
		d->map.sprites[sprite->spr_num].speed_y = 0;
		d->map.sprites[sprite->spr_num].changes = 1;
	}
	else
	{
		d->map.sprites[sprite->spr_num].speed_x += \
		d->game.dt / 10000.f * sprite->speed;
		d->map.sprites[sprite->spr_num].speed_y += \
		d->game.dt / 10000.f * sprite->speed;
		if (d->map.sprites[sprite->spr_num].speed_x >= sprite->speed)
		{
			d->map.sprites[sprite->spr_num].speed_x = sprite->speed;
			d->map.sprites[sprite->spr_num].speed_y = sprite->speed;
			d->map.sprites[sprite->spr_num].changes = 0;
		}
	}
	return (0); // sound of speech
}
