/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_txt_chg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 19:31:07 by myuliia           #+#    #+#             */
/*   Updated: 2019/09/03 18:40:16 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	editor_spr_txt(t_doom *doom, int sp)
{
	if (doom->map.sprites[sp].num_sheet == 9)
		doom->map.sprites[sp].num_sheet = 11;
	else if (doom->map.sprites[sp].num_sheet == 11)
		doom->map.sprites[sp].num_sheet = 15;
	else if (doom->map.sprites[sp].num_sheet < 9)
		doom->map.sprites[sp].num_sheet++;
}

void	editor_pnt_txt(t_doom *doom, int pain)
{
	if (doom->map.paint[pain].num_sheet == 10)
		doom->map.paint[pain].num_sheet = 12;
	else if (doom->map.paint[pain].num_sheet == 12)
		doom->map.paint[pain].num_sheet = 13;
	else if (doom->map.paint[pain].num_sheet == 13)
		doom->map.paint[pain].num_sheet = 14;
	else if (doom->map.paint[pain].num_sheet == 14)
		doom->map.paint[pain].num_sheet = 16;
}

void	editor_but_left(t_doom *doom, SDL_Event *event)
{
	doom->editor.ind_img = ((EVX / 100) - 7);
	ft_null_items(doom, doom->editor.ind_img, 0);
	if (EXIST != 0)
	{
		if (doom->editor.ind_img == 4)
			ft_free_items(doom, EXIST - 1);
		EXIST--;
	}
}

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
			editor_spr_txt(doom, sp);
		if (doom->map.sprites[sp].num_sheet == 5 || \
			doom->map.sprites[sp].num_sheet == 6 ||
			doom->map.sprites[sp].num_sheet == 8)
			doom->map.sprites[sp].mob = 1;
		if (doom->map.sprites[sp].num_sheet != 3)
			doom->map.sprites[sp].text_no = 0;
	}
}
