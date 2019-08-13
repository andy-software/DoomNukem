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

void		play_phrase(Mix_Music *mus, int distance)
{

	//Mix_VolumeMusic(128);
	// else if (Mix_PausedMusic())
	// 	Mix_ResumeMusic();
	// else
	// 	Mix_PauseMusic();
}

int			radio_event(t_doom *d, t_sprite *sprite)
{
	static int	mus_num = -1;

	if (sprite->key_state == 0)
		sprite->key_state = 1;
	if (sprite->key_state)
	{
		if (!(Mix_PlayingMusic()))
			Mix_PlayMusic(d->sound.music[++mus_num], 1);
		else if ((Mix_PlayingMusic() && d->game.click))
			Mix_PlayMusic(d->sound.music[++mus_num], 1);
		if (mus_num >= 2)
			mus_num = -1;
	}
	return (1);
}

int			talk_event(t_doom *d, t_sprite *sprite)
{
	if (sprite->num_of_sound > -1)
		if (!(Mix_Playing(4)))
			Mix_PlayChannel(4, d->sound.mobsound[sprite->num_of_sound], 0);
	return (0);
}

int			give_event(t_doom *d, t_sprite *sprite)
{
	static int click = 0;
	if (sprite->num_of_sound > -1 && click == 0)
	{
		Mix_PlayChannel(4, d->sound.mobsound[sprite->num_of_sound], 0);
		click++;
	}
	else if (click == 1 && d->game.picked_key[0] == 0)
	{
		d->game.picked_key[0] = 1;
		Mix_PlayChannel(6, d->sound.pickup[2], 0);
	}
	else
	{
		d->game.picked_key[0] = 1;
		if (!(Mix_Playing(4)))
			Mix_PlayChannel(4, d->sound.mobsound[0], 0);
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
