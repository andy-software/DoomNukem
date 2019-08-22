/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_change_scale.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:14:23 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/22 20:05:59 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	editor_scale_y(t_doom *doom, const Uint8 *state)
{
	if (doom->editor.fl_or_ceil == WALL)
	{
		doom->editor.nb_vert = check_what_line_player_are_looking(doom);
		if (doom->editor.which_wall == MIDDLE)
		{
			SECTOR_PL.lines[doom->editor.nb_vert].y_w_scale +=
			(state[SDL_SCANCODE_TAB]) ? -0.1 : 0.1;
		}
		else if (doom->editor.which_wall == BOTTOM)
			SECTOR_PL.lines[doom->editor.nb_vert].y_b_scale +=
			(state[SDL_SCANCODE_TAB]) ? -0.1 : 0.1;
		else if (doom->editor.which_wall == TOP)
			SECTOR_PL.lines[doom->editor.nb_vert].y_t_scale +=
			(state[SDL_SCANCODE_TAB]) ? -0.1 : 0.1;
	}
	if (doom->editor.fl_or_ceil == CEIL)
		SECTOR_PL.y_c_scale += (state[SDL_SCANCODE_TAB]) ? -0.01 : 0.01;
	if (doom->editor.fl_or_ceil == FLOOR)
		SECTOR_PL.y_f_scale += (state[SDL_SCANCODE_TAB]) ? -0.01 : 0.01;
}

void	editor_scale_x(t_doom *doom, const Uint8 *state)
{
	if (doom->editor.fl_or_ceil == WALL)
	{
		doom->editor.nb_vert = check_what_line_player_are_looking(doom);
		if (doom->editor.which_wall == MIDDLE)
		{
			SECTOR_PL.lines[doom->editor.nb_vert].x_w_scale +=
			(state[SDL_SCANCODE_TAB]) ? -0.1 : 0.1;
		}
		else if (doom->editor.which_wall == BOTTOM)
			SECTOR_PL.lines[doom->editor.nb_vert].x_b_scale +=
			(state[SDL_SCANCODE_TAB]) ? -0.1 : 0.1;
		else if (doom->editor.which_wall == TOP)
			SECTOR_PL.lines[doom->editor.nb_vert].x_t_scale +=
			(state[SDL_SCANCODE_TAB]) ? -0.1 : 0.1;
	}
	if (doom->editor.fl_or_ceil == CEIL)
		SECTOR_PL.x_c_scale += (state[SDL_SCANCODE_TAB]) ? -0.01 : 0.01;
	if (doom->editor.fl_or_ceil == FLOOR)
		SECTOR_PL.x_f_scale += (state[SDL_SCANCODE_TAB]) ? -0.01 : 0.01;
}

void	editor_shift_x(t_doom *doom, const Uint8 *state)
{
	if (doom->editor.fl_or_ceil == WALL)
	{
		doom->editor.nb_vert = check_what_line_player_are_looking(doom);
		if (doom->editor.which_wall == MIDDLE)
			SECTOR_PL.lines[doom->editor.nb_vert].x_w_shift +=
			(state[SDL_SCANCODE_TAB]) ? -1 : 1;
		else if (doom->editor.which_wall == BOTTOM)
			SECTOR_PL.lines[doom->editor.nb_vert].x_b_shift +=
			(state[SDL_SCANCODE_TAB]) ? -1 : 1;
		else if (doom->editor.which_wall == TOP)
			SECTOR_PL.lines[doom->editor.nb_vert].x_t_shift +=
			(state[SDL_SCANCODE_TAB]) ? -1 : 1;
	}
	if (doom->editor.fl_or_ceil == CEIL)
		SECTOR_PL.x_c_shift += (state[SDL_SCANCODE_TAB]) ? -1 : 1;
	if (doom->editor.fl_or_ceil == FLOOR)
		SECTOR_PL.x_f_shift += (state[SDL_SCANCODE_TAB]) ? -1 : 1;
}

void	editor_shift_y(t_doom *doom, const Uint8 *state)
{
	if (doom->editor.fl_or_ceil == WALL)
	{
		doom->editor.nb_vert = check_what_line_player_are_looking(doom);
		if (doom->editor.which_wall == MIDDLE)
			SECTOR_PL.lines[doom->editor.nb_vert].y_w_shift +=
			(state[SDL_SCANCODE_TAB]) ? -2 : 2;
		else if (doom->editor.which_wall == BOTTOM)
			SECTOR_PL.lines[doom->editor.nb_vert].y_b_shift +=
			(state[SDL_SCANCODE_TAB]) ? -2 : 2;
		else if (doom->editor.which_wall == TOP)
			SECTOR_PL.lines[doom->editor.nb_vert].y_t_shift +=
			(state[SDL_SCANCODE_TAB]) ? -2 : 2;
	}
	if (doom->editor.fl_or_ceil == CEIL)
		SECTOR_PL.y_c_shift += (state[SDL_SCANCODE_TAB]) ? -2 : 2;
	if (doom->editor.fl_or_ceil == FLOOR)
		SECTOR_PL.y_f_shift += (state[SDL_SCANCODE_TAB]) ? -2 : 2;
}
