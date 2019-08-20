/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_sprites_change.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:06:54 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/18 18:15:27 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	editor_start_z(t_doom *doom, const Uint8 *state)
{
	int		sp;
	int		pain;

	sp = check_what_sprite_player_are_looking(doom);
	pain = check_what_paint_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == SPRITES && sp != -1)
		doom->map.sprites[sp].start_z += (state[SDL_SCANCODE_TAB]) ? -1 : 1;
	if (doom->editor.fl_or_ceil == PAINTINGS && pain != -1)
		doom->map.paint[pain].v2.z += (state[SDL_SCANCODE_TAB]) ? -1 : 1;
}

void	editor_end_z(t_doom *doom, const Uint8 *state)
{
	int		sp;
	int		pain;

	sp = check_what_sprite_player_are_looking(doom);
	pain = check_what_paint_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == SPRITES && sp != -1)
		doom->map.sprites[sp].end_z += (state[SDL_SCANCODE_TAB]) ? -1 : 1;
	if (doom->editor.fl_or_ceil == PAINTINGS && pain != -1)
		doom->map.paint[pain].v1.z += (state[SDL_SCANCODE_TAB]) ? -1 : 1;
}

void	editor_sp_width(t_doom *doom, const Uint8 *state)
{
	int		sp;

	sp = check_what_sprite_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == SPRITES && sp != -1 && doom->map.sprites[sp].width > 0)
	{
		doom->map.sprites[sp].width += (state[SDL_SCANCODE_TAB]) ? -1 : 1;
		if (state[SDL_SCANCODE_TAB] && doom->map.sprites[sp].width == 0)
			doom->map.sprites[sp].width = 1;
	}
}

void	editor_sprites_texture(t_doom *doom, const Uint8 *state)
{
	int		sp;

	sp = check_what_sprite_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == SPRITES && sp != -1)
	{
		if (doom->map.sprites[sp].pick == 0)
		{
			if (state[SDL_SCANCODE_TAB])
			{
				if (doom->map.sprites[sp].num_sheet == 8)
					doom->map.sprites[sp].num_sheet = 6;
				else if (doom->map.sprites[sp].num_sheet == 6)
				doom->map.sprites[sp].num_sheet = 5;
			}
			else if (!(state[SDL_SCANCODE_TAB]))
			{
				if (doom->map.sprites[sp].num_sheet == 5)
					doom->map.sprites[sp].num_sheet = 6;
				else if (doom->map.sprites[sp].num_sheet == 6)
					doom->map.sprites[sp].num_sheet = 8;
			}
			
		}
		else if (doom->map.sprites[sp].pick == 1)
		{
			if (state[SDL_SCANCODE_TAB])
			{
				if (doom->map.sprites[sp].num_sheet == 9)
					doom->map.sprites[sp].num_sheet = 7;
				else if (doom->map.sprites[sp].num_sheet == 7)
					doom->map.sprites[sp].num_sheet = 4;
				else if (doom->map.sprites[sp].num_sheet != 0)
					doom->map.sprites[sp].num_sheet--;

			}
			else if (!(state[SDL_SCANCODE_TAB]))
			{
				if (doom->map.sprites[sp].num_sheet == 4)
					doom->map.sprites[sp].num_sheet = 7;
				else if (doom->map.sprites[sp].num_sheet == 7)
					doom->map.sprites[sp].num_sheet = 9;
				else if (doom->map.sprites[sp].num_sheet < 4)
					doom->map.sprites[sp].num_sheet++;

			}
		}
	}
}

void	editor_action(t_doom *doom, const Uint8 *state)
{
	int		pain;

	pain = check_what_paint_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == PAINTINGS && (pain != -1))
	{
		doom->map.paint[pain].key = 1;
		if ((state[SDL_SCANCODE_TAB]) && doom->map.paint[pain].event_num != 0)
		{
			doom->map.paint[pain].event_num--;
			info_action(doom, pain);
		}
		else if (!(state[SDL_SCANCODE_TAB])
		&& doom->map.paint[pain].event_num != NUM_TEXT)
		{
			doom->map.paint[pain].event_num++;
			info_action(doom, pain);
		}
	}
}
