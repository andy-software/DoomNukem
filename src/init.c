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
	SDL_UpdateWindowSurface(sdl->window);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowGrab(sdl->window, 1);
	SDL_SetRelativeMouseMode(1);
	return (1);
}
