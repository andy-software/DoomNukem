/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 18:32:39 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/24 17:25:47 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		load_sounds2(t_sound *sound)
{
	sound->mobhurt[0] = load_sound("./materials/sounds/enemy1_h.wav");
	sound->mobhurt[1] = load_sound("./materials/sounds/enemy2_h.wav");
	sound->mobhurt[2] = load_sound("./materials/sounds/boss_h.wav");
	sound->pickup[0] = load_sound("./materials/sounds/heal.wav");
	sound->pickup[1] = load_sound("./materials/sounds/ammo.wav");
	sound->pickup[2] = load_sound("./materials/sounds/key.wav");
	sound->pickup[3] = load_sound("./materials/sounds/pick.wav");
	sound->music[0] = load_music("./materials/sounds/mus_old1.mp3");
	sound->music[1] = load_music("./materials/sounds/mus_old2.mp3");
	sound->music[2] = load_music("./materials/sounds/mus_old3.mp3");
	sound->music[3] = load_music("./materials/sounds/mus_new1.mp3");
	sound->music[4] = load_music("./materials/sounds/mus_new2.mp3");
	sound->music[5] = load_music("./materials/sounds/mus_new3.mp3");
	sound->music[6] = load_music("./materials/sounds/win_song.mp3");
	sound->lift[0] = load_sound("./materials/sounds/acess.wav");
	sound->lift[1] = load_sound("./materials/sounds/noacess.wav");
	sound->lift[2] = load_sound("./materials/sounds/elevator.wav");
}

void		load_sounds(t_sound *sound)
{
	sound->n = 0;
	sound->win = load_sound("./materials/sounds/win.wav");
	sound->steps = load_sound("./materials/sounds/step.wav");
	sound->jump = load_sound("./materials/sounds/jump.wav");
	sound->fly = load_sound("./materials/sounds/fly.wav");
	sound->hurt = load_sound("./materials/sounds/hurt.wav");
	sound->death = load_sound("./materials/sounds/death.wav");
	sound->click = load_sound("./materials/sounds/menu_click.wav");
	sound->gun1[0] = load_sound("./materials/sounds/gun1.wav");
	sound->gun1[1] = load_sound("./materials/sounds/gun1_short.wav");
	sound->gun1[2] = load_sound("./materials/sounds/gun1_empty.wav");
	sound->gun2[0] = load_sound("./materials/sounds/saw_start.wav");
	sound->gun2[1] = load_sound("./materials/sounds/saw_idle.wav");
	sound->gun2[2] = load_sound("./materials/sounds/saw_atac.wav");
	sound->mobdeath[0] = load_sound("./materials/sounds/enemy1_d.wav");
	sound->mobdeath[1] = load_sound("./materials/sounds/enemy2_d.wav");
	sound->mobdeath[2] = load_sound("./materials/sounds/boss_d.wav");
	sound->mobsound[0] = load_sound("./materials/sounds/enemy1_s.wav");
	sound->mobsound[1] = load_sound("./materials/sounds/enemy2_s.wav");
	sound->mobsound[2] = load_sound("./materials/sounds/boss_s.wav");
	sound->mobsound[3] = load_sound("./materials/sounds/npc_1.wav");
	sound->mobsound[4] = load_sound("./materials/sounds/npc_2.wav");
	load_sounds2(sound);
}
