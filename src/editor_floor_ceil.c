/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_floor_ceil.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 20:46:39 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/22 20:06:43 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	info_ceil_floor2(t_doom *doom, int nb)
{
	char			*str1;
	SDL_Surface		*message;

	str1 = ft_itoa(nb);
	message = TTF_RenderText_Solid(doom->editor.font.text_font,
	str1, doom->editor.font.text_color);
	SDL_BlitSurface(message, NULL, doom->editor.sdl.surface,
	&doom->editor.font.text_rect);
	free(str1);
	SDL_FreeSurface(message);
}

void	info_ceil_floor(t_doom *doom)
{
	doom->editor.font.text_rect = (SDL_Rect){935, 275, 0, 0};
	info_ceil_floor2(doom,
	FLOOR_A);
	doom->editor.font.text_rect.y += 30;
	info_ceil_floor2(doom,
	FLOOR_B);
	doom->editor.font.text_rect.y += 30;
	info_ceil_floor2(doom,
	doom->map.sectors[doom->player.sector].floor_plane.c);
	doom->editor.font.text_rect.y += 31;
	info_ceil_floor2(doom,
	FLOOR_H);
	doom->editor.font.text_rect.x = 1070;
	doom->editor.font.text_rect.y = 277;
	info_ceil_floor2(doom, CEIL_A);
	doom->editor.font.text_rect.y += 30;
	info_ceil_floor2(doom, CEIL_B);
	doom->editor.font.text_rect.y += 30;
	info_ceil_floor2(doom, doom->map.sectors[doom->player.sector].ceil_plane.c);
	doom->editor.font.text_rect.y += 30;
	info_ceil_floor2(doom, CEIL_H);
}

void	key_floor_ceil(t_doom *doom)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (doom->editor.fl_or_ceil == FLOOR)
	{
		if (!state[SDL_SCANCODE_TAB])
		{
			if (state[SDL_SCANCODE_KP_1] && FLOOR_A < 2)
				FLOOR_A += 0.01;
			else if (state[SDL_SCANCODE_KP_2] && FLOOR_B < 2)
				FLOOR_B += 0.01;
			else if (state[SDL_SCANCODE_KP_3] && FLOOR_H < 1000)
				FLOOR_H += 0.6;
		}
		else if (state[SDL_SCANCODE_TAB])
		{
			if (state[SDL_SCANCODE_KP_1] && FLOOR_A > -2)
				FLOOR_A -= 0.01;
			else if (state[SDL_SCANCODE_KP_2] && FLOOR_B > -2)
				FLOOR_B -= 0.01;
			else if (state[SDL_SCANCODE_KP_3] && FLOOR_H > -1000)
				FLOOR_H -= 0.6;
		}
	}
	key_ceil(doom, state);
}

void	key_ceil(t_doom *doom, const Uint8 *state)
{
	if (doom->editor.fl_or_ceil == CEIL)
	{
		if (!state[SDL_SCANCODE_TAB])
		{
			if (state[SDL_SCANCODE_KP_1] && CEIL_A < 2)
				CEIL_A += 0.01;
			else if (state[SDL_SCANCODE_KP_2] && CEIL_B < 2)
				CEIL_B += 0.01;
			else if (state[SDL_SCANCODE_KP_3] && CEIL_H < 1000)
				CEIL_H += 0.6;
		}
		else if (state[SDL_SCANCODE_TAB])
		{
			if (state[SDL_SCANCODE_KP_1] && CEIL_A > -2)
				CEIL_A -= 0.01;
			else if (state[SDL_SCANCODE_KP_2] && CEIL_B > -2)
				CEIL_B -= 0.01;
			else if (state[SDL_SCANCODE_KP_3] && CEIL_H > -1000)
				CEIL_H -= 0.6;
		}
	}
}

void	change_floor_ceil(t_doom *doom, SDL_Event *event)
{
	if ((event->button.x > 850 && event->button.x < 1150)
	&& (event->button.y > 230 && event->button.y < 530))
	{
		if (doom->editor.fl_or_ceil == FLOOR)
			doom->editor.fl_or_ceil = CEIL;
		else
			doom->editor.fl_or_ceil = FLOOR;
	}
	if (is_in_sector(doom, event->button.x, event->button.y) != -1)
		doom->player.sector =
		is_in_sector(doom, event->button.x, event->button.y);
}
