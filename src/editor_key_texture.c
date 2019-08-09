/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_key_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 11:24:53 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/09 13:19:33 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	editor_wal_texture_bt(t_doom *doom, const Uint8 *state)
{
	if (doom->editor.which_wall == TOP)
	{
		if ((state[SDL_SCANCODE_TAB]) &&
		SECTOR_PL.lines[doom->editor.nb_vert].top != 0)
			SECTOR_PL.lines[doom->editor.nb_vert].top--;
		else if (!(state[SDL_SCANCODE_TAB])
		&& SECTOR_PL.lines[doom->editor.nb_vert].top != NUM_TEXT)
			SECTOR_PL.lines[doom->editor.nb_vert].top++;
	}
	else if (doom->editor.which_wall == BOTTOM)
	{
		if ((state[SDL_SCANCODE_TAB])
		&& SECTOR_PL.lines[doom->editor.nb_vert].bot != 0)
			SECTOR_PL.lines[doom->editor.nb_vert].bot--;
		else if (!(state[SDL_SCANCODE_TAB])
		&& SECTOR_PL.lines[doom->editor.nb_vert].bot != NUM_TEXT)
			SECTOR_PL.lines[doom->editor.nb_vert].bot++;
	}
}

void	editor_wall_texture(t_doom *doom, const Uint8 *state)
{
	if (doom->editor.fl_or_ceil == WALL)
	{
		doom->editor.nb_vert = check_what_line_player_are_looking(doom);
		p("here\n");
		if (doom->editor.which_wall == MIDDLE && doom->editor.nb_vert != -1)
		{
			if ((state[SDL_SCANCODE_TAB])
			&& SECTOR_PL.lines[doom->editor.nb_vert].wall != 0)
				SECTOR_PL.lines[doom->editor.nb_vert].wall--;
			else if (!(state[SDL_SCANCODE_TAB])
			&& SECTOR_PL.lines[doom->editor.nb_vert].wall != NUM_TEXT)
				SECTOR_PL.lines[doom->editor.nb_vert].wall++;
		}
		else
			editor_wal_texture_bt(doom, state);
	}
}

void	editor_fc_texture(t_doom *doom, const Uint8 *state)
{
	if (doom->editor.fl_or_ceil == FLOOR)
	{
		if ((state[SDL_SCANCODE_TAB]) && SECTOR_PL.floor_tex != 0)
			SECTOR_PL.floor_tex--;
		else if (!(state[SDL_SCANCODE_TAB]) && SECTOR_PL.floor_tex != NUM_TEXT)
			SECTOR_PL.floor_tex++;
	}
	else if (doom->editor.fl_or_ceil == CEIL)
	{
		if ((state[SDL_SCANCODE_TAB]) && SECTOR_PL.ceil_tex != 0)
			SECTOR_PL.ceil_tex--;
		else if (!(state[SDL_SCANCODE_TAB]) && SECTOR_PL.ceil_tex != NUM_TEXT)
			SECTOR_PL.ceil_tex++;
	}
}