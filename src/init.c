/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:54:32 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/23 18:14:19 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (error_message((char *)SDL_GetError()));
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG))
		return (error_message((char *)SDL_GetError()));
	if (!(sdl->window = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, \
		WIN_HEIGHT, SDL_WINDOW_SHOWN)))
		return (error_message((char *)SDL_GetError()));
	if (!(sdl->surface = SDL_GetWindowSurface(sdl->window)))
		return (error_message((char *)SDL_GetError()));
	if (TTF_Init() == -1)
		return (error_message((char *)SDL_GetError()));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (error_message((char *)SDL_GetError()));
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowGrab(sdl->window, 1);
	SDL_SetRelativeMouseMode(1);
	return (1);
}

int		init_moves(t_doom *d)
{
	d->changes.moves[0] = first_own_moves;
	d->changes.moves[1] = mirror_own_moves;
	d->changes.pnt_events[0] = turn_light_event;
	d->changes.pnt_events[1] = lift_floor_event;
	d->changes.pnt_events[2] = lift_ceil_event;
	d->changes.pnt_events[3] = radio_event;
	d->changes.pnt_events[4] = inverse_colors_event;
	d->changes.spr_events[0] = win_spr_event;
	d->changes.spr_events[1] = talk_event;
	d->changes.spr_events[2] = toxic_event;
	d->changes.spr_events[3] = give_event;
	d->changes.fog_colors[0] = 0x00FF00;
	d->changes.fog_colors[1] = 0xFF0000;
	d->changes.fog_colors[2] = 0x0000FF;
	d->changes.fog_colors[3] = 0x00FFFF;
	d->changes.fog_colors[4] = 0xFFFFFF;
	d->changes.fog_colors[5] = 0xAAB200;
	d->changes.fog_colors[6] = 0x45361E;
	INIT2(d->changes.fog_colors[7], 0X303B2F, d->changes.fog_colors[8], 0);
	d->changes.map_fog_color_before = d->map.fog_color;
	d->changes.start_inversion_type = d->map.inverse_colors;
	return (1);
}

int		*intset(int *b, int c, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
		b[i++] = c;
	return (b);
}
