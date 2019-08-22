/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_d->events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:14:59 by apavlov           #+#    #+#             */
/*   Updated: 2019/03/23 18:15:00 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	change_move(t_vertex *move, t_doom *d, int str, int dir)
{
	if (str == STRAIGHT)
	{
		move->x += d->player.anglecos * MOVE_SPEED * dir;
		move->y += d->player.anglesin * MOVE_SPEED * dir;
	}
	else
	{
		move->x += d->player.anglesin * MOVE_SPEED * dir;
		move->y -= d->player.anglecos * MOVE_SPEED * dir;
	}
	if (d->game.ground)
	{
		Mix_HaltChannel(0);
		if (!(Mix_Playing(1)))
			Mix_PlayChannel(1, d->sound.steps, 0);
	}
}

static void	movement_keys(t_doom *d)
{
	t_game		*g;
	t_vertex	move;
	const Uint8	*keyboard_state = SDL_GetKeyboardState(0);

	g = &d->game;
	move.x = 0;
	move.y = 0;
	g->moving = keyboard_state[SDL_SCANCODE_W] || keyboard_state[SDL_SCANCODE_A] \
	|| keyboard_state[SDL_SCANCODE_D] || keyboard_state[SDL_SCANCODE_S] \
	|| keyboard_state[SDL_SCANCODE_LSHIFT];
	if (keyboard_state[SDL_SCANCODE_W])
		change_move(&move, d, STRAIGHT, 1);
	if (keyboard_state[SDL_SCANCODE_A])
		change_move(&move, d, STRAFE, 1);
	if (keyboard_state[SDL_SCANCODE_D])
		change_move(&move, d, STRAFE, -1);
	if (keyboard_state[SDL_SCANCODE_S])
		change_move(&move, d, STRAIGHT, -1);
	if (keyboard_state[SDL_SCANCODE_LSHIFT])
		d->game.ducking = 1;
	else
		d->game.ducking = 0;
	g->velocity.x = g->velocity.x * (1 - g->acceleration) + move.x * g->acceleration;
	g->velocity.y = g->velocity.y * (1 - g->acceleration) + move.y * g->acceleration;
}

static void	mouse_rotation(t_doom *d)
{
	int				x;
	int				y;
	t_game			*g;

	g = &d->game; //should it be used? // actually yes, but NO!
	SDL_GetRelativeMouseState(&x,&y); //pislya pauzi nabuvae yakogos znachenya mojna postaviti kostilni flag pause?
	d->player.angle += x * SPEED_ROTATION;
	if (d->player.angle > 2 * M_PI)
		d->player.angle -= 2 * M_PI;
	else if (d->player.angle < 0)
		d->player.angle += 2 * M_PI;
	d->player.angle_z = clamp(d->player.angle_z - y * SPEED_ROTATION_Z, -MAX_Z_ANGLE, MAX_Z_ANGLE);
	d->player.anglesin = sinf(d->player.angle);
	d->player.anglecos = cosf(d->player.angle);
}

void		player_events(t_doom *d)
{
	if (d->map.editing)
	{
		movement_keys(d);
		mouse_rotation(d);
		editor_player_events(d);
	}
	else
	{
		if (!d->game.pause)
		{
			movement_keys(d);
			mouse_rotation(d);
		}
	while (SDL_PollEvent(&d->ev) && d->game.quit != 1)
	{
		if (d->ev.type == SDL_KEYDOWN)
		{
			if (d->ev.key.keysym.sym == SDLK_ESCAPE) 
				d->game.quit = 1;
			else if (d->ev.key.keysym.sym == SDLK_SPACE && !d->game.pause)
			{
				Mix_HaltChannel(1);
				if (d->game.ground || d->game.flying)
				{
					if ((!(Mix_Playing(0)) && d->game.flying)) 
						Mix_PlayChannel(0, d->sound.fly, 0);
					if (d->game.velocity.z < MAX_SPEED_UPWARD)
						d->game.velocity.z += 0.6;
					else
						d->game.velocity.z = MAX_SPEED_UPWARD;	
					d->game.falling = 1;
					d->game.fuel -= 1;
					if (d->game.fuel == 0)
						d->game.flying = 0;
				}
				if (!(Mix_Playing(0)) && !d->game.flying && d->game.ground)
					Mix_PlayChannel(0, d->sound.jump, 0);
			}
			else if (d->ev.key.keysym.sym == SDLK_f && !d->game.pause)
			{
				printf("Fly mod\n");
				d->game.flying = !d->game.flying;
			}
			else if (d->ev.key.keysym.sym == SDLK_1)
			{
				Mix_HaltChannel(-1);	
				d->ui.fire = 0;
				d->ui.gun_num = 0;
			}
			else if (d->ev.key.keysym.sym == SDLK_2)
			{
				Mix_HaltChannel(-1);
				d->ui.start_saw = 0;
				d->ui.clickTime = d->ui.prevTime;
				d->ui.fire = 0;
				d->ui.gun_num = 1;
			}
			else if (d->ev.key.keysym.sym == SDLK_3)
			{
				Mix_HaltChannel(-1);
				d->ui.fire = 0;
				d->ui.gun_num = 2;
			}
			else if (d->ev.key.keysym.sym == SDLK_g)
			{
				d->game.hp_level -= 15;
			}
			else if (d->ev.key.keysym.sym == SDLK_e)
			{
				d->game.click = 1;
			}
			else if (d->ev.key.keysym.sym == SDLK_h)
			{
				if (d->ui.ammo_1 + 20 <= 60)
					d->ui.ammo_1 += 20;
				else
					d->ui.ammo_1 = 60;
			}
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
		}
		else if (d->ev.type == SDL_MOUSEBUTTONUP &&
			d->ev.button.button == SDL_BUTTON_LEFT && d->start_quit != 0 && d->game.pause == 0)
		{
			if(d->ui.fire == 0)
			{
				d->ui.fire = 1;
				d->game.fire = 1;
				d->ui.clickTime = d->ui.prevTime;
				if (d->ui.gun_num == 0 && d->ui.ammo_1 >= -2)
					d->ui.ammo_1 -= 2;
				if (d->ui.gun_num == 1)
					Mix_HaltChannel(3);
			}
			else if(d->ui.fire == 1 && d->ui.gun_num == 1)
			{
				d->ui.fire = 0;
				Mix_HaltChannel(3);
			}
		}
		else if (d->ev.type == SDL_QUIT)
			d->game.quit = 1;
		switch_music(&d->sound, d->ev);
		
	}
	}

}
