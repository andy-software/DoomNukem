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
		WIN_HEIGHT, SDL_WINDOW_RESIZABLE)))
		return (error_message((char *)SDL_GetError()));
	
	if (!(sdl->render = SDL_CreateRenderer(sdl->window, -1, \
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		return (error_message((char *)SDL_GetError()));
	if (!(sdl->texture = SDL_CreateTexture(sdl->render, SDL_PIXELFORMAT_ARGB8888, \
		SDL_TEXTUREACCESS_TARGET, WIN_WIDTH, WIN_HEIGHT)))
		return (error_message((char *)SDL_GetError()));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (error_message((char *)SDL_GetError()));
	sdl->surface = SDL_CreateRGBSurface(0, WIN_WIDTH, WIN_HEIGHT, 32, 0, 0, 0, 0);
	if (sdl->surface == NULL)
		return (error_message((char *)SDL_GetError()));
	return (1);
}
