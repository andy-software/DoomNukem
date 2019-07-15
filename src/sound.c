/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:47:33 by mmasyush          #+#    #+#             */
/*   Updated: 2019/07/04 13:47:33 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

Mix_Music	*load_music(char *path)
{
	Mix_Music *load;

	load = Mix_LoadMUS(path);
	if (load == NULL)
		stop("\033[22;31mERROR: failed to load musi1c");
	return (load);
}

Mix_Chunk	*load_sound(char *path)
{
	Mix_Chunk *load;

	load = Mix_LoadWAV(path);
	if (load == NULL)
		stop("\033[22;31mERROR: failed to load sound");
	return (load);
}

void	move_sound(t_sound *sound)
{
	if (!(Mix_Playing(-1)))
		Mix_PlayChannel(-1, sound->steps, 0);
}

void		switch_music(t_sound *sound, SDL_Event ev)
{
	if (ev.type == SDL_KEYDOWN)
	{
		if (ev.key.keysym.sym == SDLK_m)
        {
            printf("KGIUDHGNS");
            printf("%d\n", sound->n);
			play_music(sound, sound->n);
        }
        else if (ev.key.keysym.sym == GREATER && sound->n < 4)
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
	if (!(Mix_PlayingMusic()))
		Mix_PlayMusic(sound->music[n], -1);
	else if (Mix_PausedMusic())
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
}

void	load_sounds(t_sound *sound)
{
    sound->n = 0;
    if (!(sound->gun2 = ft_memalloc(sizeof(Mix_Chunk*) * 3)))
		stop("\033[22;31mERROR: failed to malloc textures");
	if (!(sound->gun1 = ft_memalloc(sizeof(Mix_Chunk*) * 3)))
		stop("\033[22;31mERROR: failed to malloc textures");
	sound->win = load_sound("./materials/sounds/win.wav"); // 5
    sound->steps = load_sound("./materials/sounds/step.wav"); // -1chanell
	sound->jump = load_sound("./materials/sounds/jump.wav"); // 1 chanel
    sound->gun1[0] = load_sound("./materials/sounds/gun1.wav"); // 2
	sound->gun1[1] = load_sound("./materials/sounds/gun1_short.wav"); // 3
	sound->gun1[2] = load_sound("./materials/sounds/gun1_empty.wav"); // 4
    sound->gun2[0] = load_sound("./materials/sounds/saw_start.wav"); // 2
    sound->gun2[1] = load_sound("./materials/sounds/saw_idle.wav"); // 3 
    sound->gun2[2] = load_sound("./materials/sounds/saw_atac.wav"); // 4 
    sound->music[0] = load_music("./materials/sounds/classic.mp3");
}
