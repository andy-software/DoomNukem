/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_player_events.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 22:53:52 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/14 02:36:14 by myuliia          ###   ########.fr       */
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
		doom->map.editing = 0;
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
		}
	}
	ft_render_editor(doom);
	SDL_UpdateWindowSurface(doom->editor.sdl.window);
}
