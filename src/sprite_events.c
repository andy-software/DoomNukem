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

	if (!(Mix_PlayingMusic()))
		Mix_PlayMusic(mus, 1);
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
		play_phrase(d->sound.mobsound[sprite->num_of_sound], 10); // sound of speech
	return (0);
}

int			win_pnt_event(t_doom *d, t_painting *paint)
{
	(void)d;
	(void)paint;
	exit(1);
	return (0);
}

int			toxic_event(t_doom *d, t_sprite *sprite)
{
	static Uint32	start_time = 0;
	static int		i = 0;
	static Uint32	toxicity_rate = 20000;

	if (start_time == 0)
		d->map.inverse_colors = !d->map.inverse_colors;
	if (start_time < toxicity_rate)
	{
		
		d->map.sprites[sprite->spr_num].changes = 1;
		if (((start_time + d->game.dt) / 200) > (start_time / 200))
			d->map.fog_color = d->changes.fog_colors[i++ % 9];
		start_time += d->game.dt;
	}
	else
	{
		d->map.sprites[sprite->spr_num].changes = 0;
		d->map.inverse_colors = !d->map.inverse_colors;
		i = 0;
		start_time = 0;
		d->map.fog_color = d->changes.map_fog_color_before;
		toxicity_rate -= 2000;
	}
	return (0);
}