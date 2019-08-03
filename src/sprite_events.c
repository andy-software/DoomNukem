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
	//if (!(Mix_PlayingMusic()))
		Mix_PlayMusic(mus, 1);
	//Mix_VolumeMusic(128);
	// else if (Mix_PausedMusic())
	// 	Mix_ResumeMusic();
	// else
	// 	Mix_PauseMusic();
}


int			talk_event(t_doom *d, t_sprite *sprite)
{
	if (sprite->num_of_sound > -1)
		play_phrase(d->sound.mobs_reaction[sprite->num_of_sound], 10); // sound of speech
	return (0);
}

int			win_pnt_event(t_doom *d, t_painting *paint)
{
	(void)d;
	(void)paint;
	exit(1);
	return (0);
}
