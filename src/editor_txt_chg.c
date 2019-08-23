/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_txt_chg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 19:31:07 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/22 20:29:50 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	editor_sprites_texture2(t_doom *doom, const Uint8 *state, int sp)
{
	if (state[SDL_SCANCODE_TAB])
	{
		if (doom->map.sprites[sp].num_sheet == 9)
			doom->map.sprites[sp].num_sheet = 7;
		else if (doom->map.sprites[sp].num_sheet == 7)
			doom->map.sprites[sp].num_sheet = 4;
		else if (doom->map.sprites[sp].num_sheet == 11)
			doom->map.sprites[sp].num_sheet = 9;
		else if (doom->map.sprites[sp].num_sheet != 0)
			doom->map.sprites[sp].num_sheet--;
	}
	else if (!(state[SDL_SCANCODE_TAB]))
	{
		if (doom->map.sprites[sp].num_sheet == 4)
			doom->map.sprites[sp].num_sheet = 7;
		else if (doom->map.sprites[sp].num_sheet == 7)
			doom->map.sprites[sp].num_sheet = 9;
		else if (doom->map.sprites[sp].num_sheet == 9)
			doom->map.sprites[sp].num_sheet = 11;
		else if (doom->map.sprites[sp].num_sheet < 4)
			doom->map.sprites[sp].num_sheet++;
	}
}

void	editor_sprites_texture(t_doom *doom, const Uint8 *state)
{
	int		sp;

	sp = check_what_sprite_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == SPRITES && sp != -1)
	{
		if (doom->map.sprites[sp].mob == 1)
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
		else if (doom->map.sprites[sp].mob == 0)
			editor_sprites_texture2(doom, state, sp);
	}
}
