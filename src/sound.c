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

void	load_sounds(t_sound *sound)
{
    sound->n = 0;
	sound->win = load_sound("./materials/sounds/win.wav"); // 2
    sound->steps = load_sound("./materials/sounds/step.wav"); // 1
	sound->jump = load_sound("./materials/sounds/jump.wav"); // 0
	sound->fly = load_sound("./materials/sounds/fly.wav"); // 0
	sound->hurt = load_sound("./materials/sounds/hurt.wav"); // 2
	sound->death = load_sound("./materials/sounds/death.wav"); // 2
	sound->click = load_sound("./materials/sounds/menu_click.wav"); // 2
    sound->gun1[0] = load_sound("./materials/sounds/gun1.wav"); // 3
	sound->gun1[1] = load_sound("./materials/sounds/gun1_short.wav"); // 3
	sound->gun1[2] = load_sound("./materials/sounds/gun1_empty.wav"); // 3
    sound->gun2[0] = load_sound("./materials/sounds/saw_start.wav"); // 3
    sound->gun2[1] = load_sound("./materials/sounds/saw_idle.wav"); // 3 
    sound->gun2[2] = load_sound("./materials/sounds/saw_atac.wav"); // 3
	sound->mobdeath[0] = load_sound("./materials/sounds/enemy1_d.wav"); // 4
	sound->mobdeath[1] = load_sound("./materials/sounds/enemy2_d.wav"); // 4
	sound->mobdeath[2] = load_sound("./materials/sounds/boss_d.wav"); // 4// will change
	sound->mobsound[0] = load_sound("./materials/sounds/enemy1_s.wav"); // 4   
	sound->mobsound[1] = load_sound("./materials/sounds/enemy2_s.wav"); // 4
	sound->mobsound[2] = load_sound("./materials/sounds/boss_s.wav"); // 4
	sound->mobsound[3] = load_sound("./materials/sounds/npc_1.wav"); // 4   
	sound->mobsound[4] = load_sound("./materials/sounds/npc_2.wav"); // 4  
	sound->mobhurt[0] = load_sound("./materials/sounds/enemy1_h.wav"); // 4   
	sound->mobhurt[1] = load_sound("./materials/sounds/enemy2_h.wav"); // 4     
	sound->mobhurt[2] = load_sound("./materials/sounds/boss_h.wav"); // 4// will change
	sound->pickup[0] = load_sound("./materials/sounds/heal.wav"); // 5
	sound->pickup[1] = load_sound("./materials/sounds/ammo.wav"); // 5
	sound->pickup[2] = load_sound("./materials/sounds/key.wav"); // 5  
	sound->pickup[3] = load_sound("./materials/sounds/pick.wav"); // 5   
    sound->music[0] = load_music("./materials/sounds/mus_old1.mp3");
	sound->music[1] = load_music("./materials/sounds/mus_old2.mp3");
	sound->music[2] = load_music("./materials/sounds/mus_old3.mp3");
	sound->music[3] = load_music("./materials/sounds/mus_new1.mp3");
	sound->music[4] = load_music("./materials/sounds/mus_new2.mp3");
	sound->music[5] = load_music("./materials/sounds/mus_new3.mp3");
	sound->music[6] = load_music("./materials/sounds/mus_menu1.mp3");
}
