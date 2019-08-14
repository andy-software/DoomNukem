/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 02:47:48 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/14 03:26:51 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	editor_load_textures(t_doom *doom)
{
	doom->editor.font.text_color = (SDL_Color){255, 255, 250, 1};
	doom->editor.font.text_font =
	TTF_OpenFont("./materials/textures/editor/font.ttf", 30);
	FT_LOAD(str, str1, str2, i);
	while (++i < NB_BUTTONS)
	{
		str2 = ft_itoa(i);
		str1 = ft_strjoin("./materials/textures/editor/photo", str2);
		str = ft_strjoin(str1, ".png");
		doom->editor.images[i].image = load_tex(str, SDL_SURF->format->format);
		FRE_STR(str, str1, str2);
		if (!doom->editor.images[i].image)
			exit(0);
	}
	i = 0;
	while (++i < NB_IMAGES)
	{
		str2 = ft_itoa(i);
		str1 = ft_strjoin("./materials/textures/editor/sector", str2);
		str = ft_strjoin(str1, ".png");
		doom->editor.sector[i].image = load_tex(str, SDL_SURF->format->format);
		FRE_STR(str, str1, str2);
		if (!doom->editor.sector[i].image)
			exit(0);
	}
}

int		ft_create_window(t_doom *doom, char *name)
{
	int		i;
	char	*win_n;

	i = 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (error_message((char *)SDL_GetError()));
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG))
		return (error_message((char *)SDL_GetError()));
	win_n = ft_strjoin("DOOM  ", name);
	if (!(doom->editor.sdl.window = SDL_CreateWindow(win_n, 1500, \
		5, WIN_WIDTH, \
		WIN_HEIGHT, SDL_WINDOW_SHOWN)))
		return (error_message((char *)SDL_GetError()));
	free(win_n);
	if (!(SDL_SURF = SDL_GetWindowSurface(doom->editor.sdl.window)))
		return (error_message((char *)SDL_GetError()));
	if (TTF_Init() < 0)
		return (error_message((char *)SDL_GetError()));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (error_message((char *)SDL_GetError()));
	editor_load_textures(doom);
	if (load_all(&doom->texture, SDL_SURF->format->format, doom) == 0)
		return (error_message("Error with textures") + 1);
	SDL_UpdateWindowSurface(doom->editor.sdl.window);
	return (1);
}
