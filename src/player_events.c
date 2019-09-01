/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:14:59 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/31 18:31:46 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	change_move(t_vertex *move, t_doom *d, int str, int dir)
{
	if (str == STRAIGHT)
	{
		move->x += d->player.anglecos * d->game.speed * dir;
		move->y += d->player.anglesin * d->game.speed * dir;
	}
	else
	{
		move->x += d->player.anglesin * d->game.speed * dir;
		move->y -= d->player.anglecos * d->game.speed * dir;
	}
	if (d->game.ground)
	{
		Mix_HaltChannel(0);
		if (d->game.speed == 0.5f)
		{
			if (!(Mix_Playing(1)))
				Mix_PlayChannel(1, d->sound.run, 0);
		}
		else if (!(Mix_Playing(1)))
			Mix_PlayChannel(1, d->sound.steps, 0);
	}
}

int			is_movement_key(const Uint8 *keyboard_state)
{
	return (keyboard_state[SDL_SCANCODE_W] ||
	keyboard_state[SDL_SCANCODE_A] \
	|| keyboard_state[SDL_SCANCODE_D] || keyboard_state[SDL_SCANCODE_S] \
	|| keyboard_state[SDL_SCANCODE_LSHIFT]);
}

void		moves_modify(const Uint8 *keyboard_state, t_doom *d)
{
	if (keyboard_state[SDL_SCANCODE_LCTRL])
		d->game.ducking = 1;
	else
		d->game.ducking = 0;
	if (keyboard_state[SDL_SCANCODE_LSHIFT] &&
		!keyboard_state[SDL_SCANCODE_LCTRL])
		d->game.speed = 0.5f;
	else
		d->game.speed = 0.2f;
}

static void	movement_keys(t_doom *d)
{
	t_game		*g;
	t_vertex	move;
	const Uint8	*keyboard_state = SDL_GetKeyboardState(0);

	g = &d->game;
	move.x = 0;
	move.y = 0;
	g->moving = is_movement_key(keyboard_state);
	if (keyboard_state[SDL_SCANCODE_W])
		change_move(&move, d, STRAIGHT, 1);
	if (keyboard_state[SDL_SCANCODE_A])
		change_move(&move, d, STRAFE, 1);
	if (keyboard_state[SDL_SCANCODE_D])
		change_move(&move, d, STRAFE, -1);
	if (keyboard_state[SDL_SCANCODE_S])
		change_move(&move, d, STRAIGHT, -1);
	moves_modify(keyboard_state, d);
	g->velocity.x = g->velocity.x *
		(1 - g->acceleration) + move.x * g->acceleration;
	g->velocity.y = g->velocity.y *
		(1 - g->acceleration) + move.y * g->acceleration;
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
				key_events(d);
			else if (d->ev.type == SDL_MOUSEBUTTONUP && \
				d->ev.button.button == SDL_BUTTON_LEFT &&
					d->start_quit != 0 && d->game.pause == 0)
				mouse_events(d);
			else if (d->ev.type == SDL_QUIT)
				d->game.quit = 1;
		}
	}
}
