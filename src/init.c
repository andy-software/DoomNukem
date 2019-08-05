/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:54:32 by apavlov           #+#    #+#             */
/*   Updated: 2019/03/23 15:54:33 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		init_sdl(t_sdl *sdl, t_option *options)
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
	d->changes.pnt_events[3] = first_aid_event;
	d->changes.pnt_events[4] = get_ammo_event;
	d->changes.pnt_events[5] = win_pnt_event;
	d->changes.spr_events[0] = win_spr_event;
	d->changes.spr_events[1] = talk_event;
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
