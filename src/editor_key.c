/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 11:23:05 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/07 20:41:47 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	fog_change(t_doom *doom)
{
	if (doom->map.fog == 1)
	{
		doom->editor.ind_fog += doom->editor.ind_fog < 8 ? 1 : -8;
		doom->map.fog_color = doom->editor.fog_colors[doom->editor.ind_fog];
	}
}

void	editor_events_down_up(t_doom *doom)
{
	if (doom->ev.key.keysym.sym == SDLK_PAGEUP ||
	doom->ev.key.keysym.sym == SDLK_PAGEDOWN)
	{
		if (doom->ev.key.keysym.sym == SDLK_PAGEDOWN &&
		doom->editor.fl_or_ceil > 1 && (doom->editor.fl_or_ceil--))
			info_f_c_w_s(doom, 1);
		else if (doom->ev.key.keysym.sym == SDLK_PAGEUP &&
		doom->editor.fl_or_ceil < PAINTINGS && (doom->editor.fl_or_ceil++))
			info_f_c_w_s(doom, 1);
	}
	else if (doom->editor.fl_or_ceil == WALL
	&& (doom->ev.key.keysym.sym == 1073741898 ||
	doom->ev.key.keysym.sym == 1073741901))
	{
		if (doom->ev.key.keysym.sym == 1073741901 &&
		doom->editor.which_wall > BOTTOM && (doom->editor.which_wall--))
			info_f_c_w_s(doom, 2);
		else if (doom->ev.key.keysym.sym == 1073741898 &&
		doom->editor.which_wall < TOP && (doom->editor.which_wall++))
			info_f_c_w_s(doom, 2);
	}
}

void	editor_player_events2(t_doom *doom, const Uint8 *state)
{
	if (doom->ev.key.keysym.sym == SDLK_r)
	{
		if (doom->editor.fl_or_ceil == CEIL)
		{
			if (doom->map.sectors[doom->player.sector].render_ceil == 1)
				doom->map.sectors[doom->player.sector].render_ceil = 0;
			else
				doom->map.sectors[doom->player.sector].render_ceil = 1;
		}
	}
	editor_events_down_up(doom);
	if (doom->ev.key.keysym.sym == SDLK_m)
		doom->map.editing = 0;
	else if (doom->ev.key.keysym.sym == SDLK_z)
		editor_start_z(doom, state);
	else if (doom->ev.key.keysym.sym == SDLK_x)
		editor_end_z(doom, state);
	else if (doom->ev.key.keysym.sym == SDLK_c)
		editor_sp_width(doom, state);
	else if (doom->ev.key.keysym.sym == SDLK_e)
		editor_action(doom, state);
	else if (doom->ev.key.keysym.sym == SDLK_1)
		fog_change(doom);
}

void	editor_player_events(t_doom *doom)
{
	const Uint8	*state;

	state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&doom->ev) && doom->game.quit != 1)
	{
		key_floor_ceil(doom);
		key_editor_change(doom, state);
		if (doom->ev.type == SDL_KEYDOWN)
		{
			if (doom->ev.key.keysym.sym == SDLK_t)
			{
				editor_wall_texture(doom, state);
				editor_fc_texture(doom, state);
				editor_sprites_texture(doom, state);
			}
			else if (doom->ev.key.keysym.sym == SDLK_COMMA)
				editor_scale_x(doom, state);
			else if (doom->ev.key.keysym.sym == SDLK_PERIOD)
				editor_scale_y(doom, state);
			editor_player_events2(doom, state);
			if (doom->ev.type == SDL_KEYDOWN)
			{
				if (doom->ev.key.keysym.sym == PAUSE)
				{
					if (doom->game.pause == 0)
					{
						doom->game.pause = 1;
						SDL_ShowCursor(SDL_ENABLE);
						SDL_SetRelativeMouseMode(SDL_DISABLE);
						SDL_SetWindowGrab(doom->sdl.window, 0);
						if (doom->game.pause == 1)
						{
							SDL_Rect bigger = (SDL_Rect){0, 0, 0, 0};
							SDL_BlitSurface(SECTOR[5].image, NULL, doom->sdl.surface, &bigger);
						}
					}
					else
					{
							doom->game.pause = 0;
						// SDL_ShowCursor(SDL_DISABLE);  das useless
						SDL_SetWindowGrab(doom->sdl.window, 1);
						SDL_SetRelativeMouseMode(SDL_ENABLE);
						SDL_GetRelativeMouseState(NULL, NULL);
					}
				}
			}
			if (doom->ev.key.keysym.sym == SDLK_SPACE && !doom->game.pause)
			{
				if (doom->game.ground || doom->game.flying)
				{
					if (doom->game.velocity.z < MAX_SPEED_UPWARD)
						doom->game.velocity.z += 0.6;
					else
						doom->game.velocity.z = MAX_SPEED_UPWARD;					
					doom->game.falling = 1;
				}
			}
		}
	}
	ft_render_editor(doom);
	SDL_UpdateWindowSurface(doom->editor.sdl.window);
}

void	key_editor_change(t_doom *doom, const Uint8 *state)
{
	if (state[SDL_SCANCODE_L] && state[SDL_SCANCODE_TAB]
	&& doom->map.sectors[doom->player.sector].light_lvl > 0)
		doom->map.sectors[doom->player.sector].light_lvl--;
	else if (state[SDL_SCANCODE_L]
	&& doom->map.sectors[doom->player.sector].light_lvl < 90)
		doom->map.sectors[doom->player.sector].light_lvl++;
}
