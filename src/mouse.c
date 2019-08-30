/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 15:40:13 by mmasyush          #+#    #+#             */
/*   Updated: 2019/08/30 15:40:13 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	mouse_events(t_doom *d)
{
	if (d->ui.fire == 0)
	{
		d->ui.fire = 1;
		d->game.fire = 1;
		d->ui.click_time = d->ui.prev_time;
		if (d->ui.gun_num == 0 && d->ui.ammo_1 >= -2)
			d->ui.ammo_1 -= 2;
		if (d->ui.gun_num == 1)
			Mix_HaltChannel(3);
	}
	else if (d->ui.fire == 1 && d->ui.gun_num == 1)
	{
		d->ui.fire = 0;
		Mix_HaltChannel(3);
	}
}

void	mouse_rotation(t_doom *d)
{
	int				x;
	int				y;
	t_game			*g;

	g = &d->game;
	SDL_GetRelativeMouseState(&x, &y);
	d->player.angle += x * SPEED_ROTATION;
	if (d->player.angle > 2 * M_PI)
		d->player.angle -= 2 * M_PI;
	else if (d->player.angle < 0)
		d->player.angle += 2 * M_PI;
	d->player.angle_z = CLAMP(d->player.angle_z - y *
		SPEED_ROTATION_Z, -MAX_Z_ANGLE, MAX_Z_ANGLE);
	d->player.anglesin = sinf(d->player.angle);
	d->player.anglecos = cosf(d->player.angle);
}
