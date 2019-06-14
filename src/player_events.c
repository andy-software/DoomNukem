/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_events.c                                    :+:      :+:    :+:   */
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

	g = &d->game; //should it be used?
	SDL_GetRelativeMouseState(&x,&y);
	d->player.angle += x * SPEED_ROTATION;
	d->player.angle_z = clamp(d->player.angle_z - y * SPEED_ROTATION_Z, -MAX_Z_ANGLE, MAX_Z_ANGLE);
	d->player.anglesin = sinf(d->player.angle);
	d->player.anglecos = cosf(d->player.angle);
}

void		player_events(t_doom *d)
{
	SDL_Event	ev;

	while (SDL_PollEvent(&ev) && d->game.quit != 1)
	{
		if (ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP)
		{
			if (ev.key.keysym.sym == SDLK_ESCAPE) 
				d->game.quit = 1;
			else if (ev.key.keysym.sym == SDLK_SPACE)
			{
				//printf("velocity z %f\n", d->game.velocity.z);
				if (d->game.ground || (d->game.velocity.z > -0.4 && d->game.velocity.z < 0))
				{
					d->game.velocity.z += 0.6;
					d->game.falling = 1;
				}
			}
		}
		if (ev.type == SDL_KEYDOWN)
		{
			if (ev.key.keysym.sym == SDLK_k)
			{
				if (d->game.pause == 0)
					d->game.pause = 1;
				else
					d->game.pause = 0;
			}
		}
		else if (ev.type == SDL_QUIT)
			d->game.quit = 1;
	}
	movement_keys(d);
	mouse_rotation(d);
}
