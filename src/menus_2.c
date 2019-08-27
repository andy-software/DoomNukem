/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 19:00:59 by mdanylch          #+#    #+#             */
/*   Updated: 2019/08/24 19:04:20 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	chose_dificulty(t_doom *d)
{
	d->menu.opt = 3;
	d->menu.title[0] = "Easy";
	d->menu.title[1] = "Classic";
	d->menu.title[2] = "SupaHard";
	d->menu.title[3] = "CHOOSE DIFFICULTY";
	d->menu.col[0] = (SDL_Color){255, 255, 255, 0};
	d->menu.col[1] = (SDL_Color){200, 20, 10, 0};
	d->menu.m[0] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, d->menu.title[0], d->menu.col[0]);
	d->menu.m[1] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, d->menu.title[1], d->menu.col[0]);
	d->menu.m[2] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, d->menu.title[2], d->menu.col[0]);
	d->menu.m[3] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, d->menu.title[3], d->menu.col[1]);
	d->menu.pos[0].x = WIN_WIDTH / 2 - d->menu.m[0]->w / 2;
	d->menu.pos[0].y = WIN_HEIGHT / 2 - d->menu.m[0]->h;
	d->menu.pos[1].x = WIN_WIDTH / 2 - d->menu.m[1]->w / 2;
	d->menu.pos[1].y = WIN_HEIGHT / 2 + d->menu.m[1]->h;
	d->menu.pos[2].x = WIN_WIDTH / 2 - d->menu.m[2]->w / 2;
	d->menu.pos[2].y = WIN_HEIGHT / 2 + (d->menu.m[2]->h * 3);
	d->menu.pos[3].x = WIN_WIDTH / 2 - d->menu.m[3]->w / 2;
	d->menu.pos[3].y = 0;
	SDL_BlitScaled(d->texture.start, 0, d->sdl.surface, 0);
}

void	start_events(t_doom *d)
{
	int			i;
	SDL_Event	ev;

	i = -1;
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_KEYDOWN)
			if (ev.key.keysym.sym == SDLK_ESCAPE)
				exit(1);
		if (ev.type == SDL_QUIT)
			exit(1);
		if (ev.type == SDL_MOUSEBUTTONUP)
			while (++i < d->menu.opt)
				if (in_rect(&d->menu, i) != 0)
				{
					if (i == 0)
						d->start_quit = 1;
					else if (i == 1)
						exit(1);
					Mix_PlayChannel(3, d->sound.click, 0);
				}
	}
}

void	pause_events(t_doom *d)
{
	INT_1(i);
	if (d->ev.type == SDL_KEYDOWN)
		if (d->ev.key.keysym.sym == SDLK_ESCAPE)
			exit(1);
	if (d->ev.type == SDL_QUIT)
		exit(1);
	if (d->ev.type == SDL_MOUSEBUTTONDOWN)
		while (++i < d->menu.opt)
			if (in_rect(&d->menu, i) != 0)
			{
				if (i == 0)
					d->game.story = 1;
				else if (i == 1)
				{
					free_file_data(&d->map);
					free_game_params(d);
					free_menu(d);
					game_mod(d, d->file_name);
					exit(1);
				}
				else if (i == 2)
					exit(1);
				Mix_PlayChannel(3, d->sound.click, 0);
			}
}

void	lose_events(t_doom *d)
{
	int		i;

	i = -1;
	if (d->ev.type == SDL_KEYDOWN)
		if (d->ev.key.keysym.sym == SDLK_ESCAPE)
			exit(1);
	if (d->ev.type == SDL_QUIT)
		exit(1);
	if (d->ev.type == SDL_MOUSEBUTTONDOWN)
		while (++i < d->menu.opt)
			if (in_rect(&d->menu, i) != 0)
			{
				if (i == 0)
				{
					free_file_data(&d->map);
					free_game_params(d);
					free_menu(d);
					game_mod(d, d->file_name);
					exit(1);
				}
				else if (i == 1)
					exit(1);
				Mix_PlayChannel(3, d->sound.click, 0);
			}
}

void	level_events(t_doom *d)
{
	int			i;
	SDL_Event	ev;

	i = -1;
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_KEYDOWN)
			if (ev.key.keysym.sym == SDLK_ESCAPE)
				exit(1);
		if (ev.type == SDL_QUIT)
			exit(1);
		if (ev.type == SDL_MOUSEBUTTONUP)
			while (++i < d->menu.opt)
				if (in_rect(&d->menu, i) != 0)
				{
					if (i == 0)
						ft_strcpy(d->file_name, "maps/portal");
					else if (i == 1)
						ft_strcpy(d->file_name, "maps/level1");
					else if (i == 2)
						ft_strcpy(d->file_name, "maps/level2");
					Mix_PlayChannel(3, d->sound.click, 0);
				}
	}
}
