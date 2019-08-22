/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_sprites_change.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:06:54 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/22 19:36:28 by myuliia          ###   ########.fr       */
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
	if (doom->editor.fl_or_ceil == SPRITES
	&& sp != -1 && doom->map.sprites[sp].width > 0)
	{
		doom->map.sprites[sp].width += (state[SDL_SCANCODE_TAB]) ? -1 : 1;
		if (state[SDL_SCANCODE_TAB] && doom->map.sprites[sp].width == 0)
			doom->map.sprites[sp].width = 1;
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
		&& doom->map.paint[pain].event_num != INV_COLORS)
		{
			doom->map.paint[pain].event_num++;
			info_action(doom, pain);
		}
	}
}
