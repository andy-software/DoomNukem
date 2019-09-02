/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_txt_chg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 19:31:07 by myuliia           #+#    #+#             */
/*   Updated: 2019/09/01 12:45:07 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	editor_sprites_texture(t_doom *doom, const Uint8 *state)
{
	int		sp;

	sp = check_what_sprite_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == SPRITES && sp != -1)
	{
		doom->map.sprites[sp].changes = 0;
		doom->map.sprites[sp].mob = 0;
		if (state[SDL_SCANCODE_TAB])
		{
			if (doom->map.sprites[sp].num_sheet == 15)
				doom->map.sprites[sp].num_sheet = 11;
			else if (doom->map.sprites[sp].num_sheet == 11)
				doom->map.sprites[sp].num_sheet = 9;
			else if (doom->map.sprites[sp].num_sheet != 0)
				doom->map.sprites[sp].num_sheet--;
		}
		else if (!(state[SDL_SCANCODE_TAB]))
		{
			if (doom->map.sprites[sp].num_sheet == 9)
				doom->map.sprites[sp].num_sheet = 11;
			else if (doom->map.sprites[sp].num_sheet == 11)
				doom->map.sprites[sp].num_sheet = 15;
			else if (doom->map.sprites[sp].num_sheet < 9)
				doom->map.sprites[sp].num_sheet++;
		}
		if (doom->map.sprites[sp].num_sheet == 5 || doom->map.sprites[sp].num_sheet == 6 ||
		doom->map.sprites[sp].num_sheet == 8)
		{
			doom->map.sprites[sp].mob = 1;
		}
		if (doom->map.sprites[sp].num_sheet != 3)
			doom->map.sprites[sp].text_no = 0;
	}
}
