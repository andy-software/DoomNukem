/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_player_events.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 22:53:52 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/22 18:22:48 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	editor_player_events2(t_doom *doom, const Uint8 *state)
{
	if (doom->ev.key.keysym.sym == SDLK_r)
		doom->map.sectors[doom->player.sector].render_ceil =
		!doom->map.sectors[doom->player.sector].render_ceil;
	editor_events_down_up(doom);
	if (doom->ev.key.keysym.sym == SDLK_m || doom->ev.key.keysym.sym == SDLK_q)
	{
		doom->map.editing = 0;
		write_sprites(doom);
	}
	else if (doom->ev.key.keysym.sym == SDLK_z)
		editor_start_z(doom, state);
	else if (doom->ev.key.keysym.sym == SDLK_x)
		editor_end_z(doom, state);
	else if (doom->ev.key.keysym.sym == SDLK_c)
		editor_sp_width(doom, state);
	else if (doom->ev.key.keysym.sym == SDLK_e)
	{
		editor_action_sp(doom, state);
		editor_action(doom, state);
	}
	else if (doom->ev.key.keysym.sym == SDLK_1)
		fog_change(doom);
}

void	editor_player_events3(t_doom *doom, const Uint8 *state)
{
	editor_events_texture(doom, state);
	editor_player_events2(doom, state);
	if (doom->ev.key.keysym.sym == SDLK_i)
		doom->map.inverse_colors = !doom->map.inverse_colors;
	if (doom->ev.key.keysym.sym == PAUSE)
	{
		doom->game.pause = !doom->game.pause;
		if (doom->game.pause == 1)
			SDL_BlitSurface(SECTOR[5].image, NULL,
			doom->sdl.surface, &(SDL_Rect){0, 0, 0, 0});
	}
	if (doom->ev.key.keysym.sym == SDLK_SPACE && !doom->game.pause)
	{
		if (doom->game.velocity.z < MAX_SPEED_UPWARD)
			doom->game.velocity.z += 0.6;
		else
			doom->game.velocity.z = MAX_SPEED_UPWARD;
		doom->game.falling = 1;
		doom->game.flying = 1;
	}
}

void	editor_lift(t_doom *doom, const Uint8 *state)
{
	int		pain;

	pain = check_what_paint_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == PAINTINGS &&
	(PT.event_num == LIFT_FL ||
	PT.event_num == LIFT_CEIL) && pain != -1)
	{
		if (doom->ev.key.keysym.sym == SDLK_KP_7)
		{
			if (state[SDL_SCANCODE_TAB] &&
			PT.num_of_sect_to_lift > 0)
				PT.num_of_sect_to_lift--;
			else if (!(state[SDL_SCANCODE_TAB]) &&
			PT.num_of_sect_to_lift < (int)(doom->map.num_sect - 1))
				PT.num_of_sect_to_lift++;
		}
		if (doom->ev.key.keysym.sym == SDLK_KP_8)
			PT.high_point += (state[SDL_SCANCODE_TAB]) ? -1 : 1;
		if (doom->ev.key.keysym.sym == SDLK_KP_9)
			PT.low_point += (state[SDL_SCANCODE_TAB]) ? -1 : 1;
		info_lift(doom, pain);
	}
}

void	editor_player_events(t_doom *doom)
{
	const Uint8	*state;

	state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&doom->ev) && doom->game.quit != 1)
	{
		if (doom->ev.type == SDL_KEYDOWN)
		{
			key_floor_ceil(doom);
			key_editor_change(doom, state);
			editor_player_events3(doom, state);
			editor_lift(doom, state);
		}
	}
	ft_render_editor(doom);
	SDL_UpdateWindowSurface(doom->editor.sdl.window);
}
