/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:47:33 by mmasyush          #+#    #+#             */
/*   Updated: 2019/08/23 18:33:11 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

Mix_Music	*load_music(char *path)
{
	Mix_Music *load;

	load = Mix_LoadMUS(path);
	if (load == NULL)
		error_message("\033[22;31mERROR: failed to load musi1c");
	return (load);
}

Mix_Chunk	*load_sound(char *path)
{
	Mix_Chunk *load;

	load = Mix_LoadWAV(path);
	if (load == NULL)
		error_message("\033[22;31mERROR: failed to load sound");
	return (load);
}

void		switch_music(t_sound *sound, SDL_Event ev)
{
	if (ev.type == SDL_KEYDOWN)
	{
		if (ev.key.keysym.sym == SDLK_m)
		{
			play_music(sound, sound->n);
		}
		else if (ev.key.keysym.sym == GREATER && sound->n < 5)
		{
			Mix_HaltMusic();
			sound->n += 1;
			play_music(sound, sound->n);
		}
		else if (ev.key.keysym.sym == LESER && sound->n > 0)
		{
			Mix_HaltMusic();
			sound->n -= 1;
			play_music(sound, sound->n);
		}
	}
}

void		play_music(t_sound *sound, int n)
{
	Mix_VolumeMusic(MIX_MAX_VOLUME / 1.5);
	if (!(Mix_PlayingMusic()))
		Mix_PlayMusic(sound->music[n], -1);
	else if (Mix_PausedMusic())
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
}
