/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 15:21:31 by mmasyush          #+#    #+#             */
/*   Updated: 2019/08/28 17:54:54 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		jump_event(t_doom *d)
{
	Mix_HaltChannel(1);
	if (d->game.ground || d->game.flying)
	{
		if ((!(Mix_Playing(0)) && d->game.flying))
			Mix_PlayChannel(0, d->sound.fly, 0);
		if (d->game.velocity.z < MAX_SPEED_UPWARD)
			d->game.velocity.z += 1.3;
		else
			d->game.velocity.z = MAX_SPEED_UPWARD;
		d->game.falling = 1;
		d->game.fuel -= 1;
		if (d->game.fuel == 0)
		{
			Mix_HaltChannel(0);
			d->game.flying = 0;
		}
	}
	if (!(Mix_Playing(0)) && !d->game.flying && d->game.ground)
		Mix_PlayChannel(0, d->sound.jump, 0);
}

void		change_gun(t_doom *d)
{
	if (d->ev.key.keysym.sym == SDLK_1)
	{
		Mix_HaltChannel(-1);
		d->ui.fire = 0;
		d->ui.gun_num = 0;
	}
	else if (d->ev.key.keysym.sym == SDLK_2)
	{
		Mix_HaltChannel(-1);
		d->ui.start_saw = 0;
		d->ui.click_time = d->ui.prev_time;
		d->ui.fire = 0;
		d->ui.gun_num = 1;
	}
	else if (d->ev.key.keysym.sym == SDLK_3 && d->game.win == 1)
	{
		Mix_HaltChannel(-1);
		d->ui.fire = 0;
		d->ui.gun_num = 2;
	}
}

void		key_events(t_doom *d)
{
	if (d->ev.key.keysym.sym == SDLK_ESCAPE)
		d->game.quit = 1;
	else if (d->ev.key.keysym.sym == SDLK_SPACE && !d->game.pause)
		jump_event(d);
	else if (d->ev.key.keysym.sym == SDLK_e)
		d->game.click = 1;
	else if (d->ev.key.keysym.sym == PAUSE)
	{
		if (d->game.pause == 0)
			d->game.pause = 1;
		else if (d->game.story == 1)
			d->game.story = 0;
		else
			d->game.pause = 0;
		set_mouse(d);
	}
	change_gun(d);
}
