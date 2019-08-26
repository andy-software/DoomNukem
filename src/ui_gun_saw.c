/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_gun_saw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanylch <mdanylch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:39:22 by mdanylch          #+#    #+#             */
/*   Updated: 2019/08/26 20:56:06 by mdanylch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static	void	saw_atack(t_doom *d)
{
	d->game.fire = 1;
	if (d->ui.idle == 0)
	{
		SDL_BlitSurface(d->texture.gun2[14 + d->game.blood * 2], \
			0, d->sdl.surface, &d->texture.gun22_r);
		d->ui.idle = 1;
	}
	else if (d->ui.idle == 1)
	{
		SDL_BlitSurface(d->texture.gun2[15 + d->game.blood * 2], 0, \
			d->sdl.surface, &d->texture.gun22_r);
		d->ui.idle = 0;
	}
	if (!(Mix_Playing(3)))
		Mix_PlayChannel(3, d->sound.gun2[2], 0);
}

static	void	saw_hold(t_doom *d)
{
	if (d->ui.idle == 0)
	{
		SDL_BlitSurface(d->texture.gun2[10 + d->game.blood * 2], 0, \
			d->sdl.surface, &d->texture.gun21_r);
		d->ui.idle = 1;
	}
	else if (d->ui.idle == 1)
	{
		SDL_BlitSurface(d->texture.gun2[11 + d->game.blood * 2], 0, \
			d->sdl.surface, &d->texture.gun21_r);
		d->ui.idle = 0;
	}
	if (!(Mix_Playing(3)))
		Mix_PlayChannel(3, d->sound.gun2[1], 0);
}

void			ui_gun_num_1(t_doom *d)
{
	if (d->ui.start_saw < 10)
	{
		SDL_BlitSurface(d->texture.gun2[d->ui.start_saw], 0, \
			d->sdl.surface, &d->texture.gun21_r);
		d->ui.start_saw = ((d->ui.prevTime - d->ui.clickTime) / 50);
		if (!(Mix_Playing(3)))
			Mix_PlayChannel(3, d->sound.gun2[0], 0);
	}
	else if (d->ui.start_saw == 10 && d->ui.fire == 1)
	{
		saw_atack(d);
	}
	else if (d->ui.start_saw == 10)
	{
		saw_hold(d);
	}
}
