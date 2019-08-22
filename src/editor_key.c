/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 11:23:05 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/22 20:03:53 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	fog_change(t_doom *doom)
{
	if (doom->map.fog == 1)
	{
		doom->editor.ind_fog += doom->editor.ind_fog < 8 ? 1 : -8;
		doom->map.fog_color = doom->changes.fog_colors[doom->editor.ind_fog];
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

void	editor_action_sp(t_doom *doom, const Uint8 *state)
{
	int		sp;

	sp = check_what_sprite_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == SPRITES && (sp != -1))
	{
		doom->map.sprites[sp].key = 1;
		if ((state[SDL_SCANCODE_TAB]) && doom->map.sprites[sp].event_num != 0)
		{
			doom->map.sprites[sp].event_num--;
			info_action_sprites(doom, sp);
		}
		else if (!(state[SDL_SCANCODE_TAB])
		&& doom->map.sprites[sp].event_num != (COUNT_OF_SPRITE_EVENTS - 1))
		{
			doom->map.sprites[sp].event_num++;
			info_action_sprites(doom, sp);
		}
	}
}

void	editor_painitngs_texture(t_doom *doom, const Uint8 *state)
{
	int		pain;

	pain = check_what_paint_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == PAINTINGS && pain != -1)
	{
		if (state[SDL_SCANCODE_TAB])
		{
			if (doom->map.paint[pain].num_sheet == 12)
				doom->map.paint[pain].num_sheet = 10;
		}
		else if (!(state[SDL_SCANCODE_TAB]))
		{
			if (doom->map.paint[pain].num_sheet == 10)
				doom->map.paint[pain].num_sheet = 12;
		}
	}
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
