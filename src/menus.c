/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:00:45 by mmasyush          #+#    #+#             */
/*   Updated: 2019/08/20 06:33:40 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	show_story(t_doom *d)
{
	if (d->ev.type == SDL_KEYDOWN)
	{
		if (d->ev.key.keysym.sym == SDLK_ESCAPE) 
			exit(1);
		else if (d->ev.key.keysym.sym == PAUSE)
			d->game.story = 0;
	}
	if (d->ev.type == SDL_QUIT)
			exit(1);
	SDL_BlitScaled(d->texture.story, 0, d->sdl.surface, 0);
}

void	show_pause(t_doom *d)
{
	d->menu.opt = 3;
	d->menu.title[0] = "Story";
	d->menu.title[1] = "Restart";
	d->menu.title[2] = "Exit";
	d->menu.title[3] = "PAUSE";
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
}

void	    show_start(t_doom *d)
{
	d->menu.opt = 2;
	d->menu.title[0] = "Play";
	d->menu.title[1] = "Exit";
	d->menu.title[2] = "DOOM-NUKEM 3D";
	d->menu.col[0] = (SDL_Color){255, 255, 255, 0};
 	d->menu.col[1] = (SDL_Color){200, 20, 10, 0};
	d->menu.m[0] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, d->menu.title[0], d->menu.col[0]);
	d->menu.m[1] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, d->menu.title[1], d->menu.col[0]);
	d->menu.m[2] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, d->menu.title[2], d->menu.col[1]);
	d->menu.pos[0].x = WIN_WIDTH / 2 - d->menu.m[0]->w / 2;
	d->menu.pos[0].y = WIN_HEIGHT / 2 - d->menu.m[0]->h * 2;
	d->menu.pos[1].x = WIN_WIDTH / 2 - d->menu.m[1]->w / 2;
	d->menu.pos[1].y = WIN_HEIGHT / 2 + d->menu.m[1]->h * 2;
	d->menu.pos[2].x = WIN_WIDTH / 2 - d->menu.m[2]->w / 2;
	d->menu.pos[2].y = WIN_HEIGHT / 2;
	SDL_BlitScaled(d->texture.start, 0, d->sdl.surface, 0);
}

void	show_lose(t_doom *d)
{
	d->menu.opt = 2;
	d->menu.title[0] = "Restart";
	d->menu.title[1] = "Exit";
	d->menu.title[2] = "!YOU ARE DEAD!";
	d->menu.col[0] = (SDL_Color){255, 255, 255, 0};
 	d->menu.col[1] = (SDL_Color){200, 20, 10, 0};
	d->menu.m[0] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, d->menu.title[0], d->menu.col[0]);
	d->menu.m[1] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, d->menu.title[1], d->menu.col[0]);
	d->menu.m[2] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, d->menu.title[2], d->menu.col[1]);
	d->menu.pos[0].x = WIN_WIDTH / 2 - d->menu.m[0]->w / 2;
	d->menu.pos[0].y = WIN_HEIGHT / 2 - d->menu.m[0]->h;
	d->menu.pos[1].x = WIN_WIDTH / 2 - d->menu.m[1]->w / 2;
	d->menu.pos[1].y = WIN_HEIGHT / 2 + d->menu.m[1]->h;
	d->menu.pos[2].x = WIN_WIDTH / 2 - d->menu.m[2]->w / 2;
	d->menu.pos[2].y = 0;
	if (!Mix_Playing(6) && d->game.dead == 0)
	{
		d->game.dead = 1;
		Mix_PlayChannel(6, d->sound.death, 0);
	}
	SDL_BlitScaled(d->texture.lose, 0, d->sdl.surface, 0);
}

void	    chose_level(t_doom *d)
{
	d->menu.opt = 3;
	d->menu.title[0] = "Portal";
	d->menu.title[1] = "Bridge";
	d->menu.title[2] = "Towers";
	d->menu.title[3] = "CHOOSE LEVEL";
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

void	    chose_dificulty(t_doom *d)
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
	int i;
	
	i = -1;
	SDL_Event		ev;
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
	int i;
	
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
					d->game.story = 1;
				else if (i == 1)
				{
					free_file_data(&d->map);
					free_game_params(d);
					free_menu(d);
					game_mod(d);
					exit(1);
				}
				else if (i == 2)
					exit(1);
				Mix_PlayChannel(3, d->sound.click, 0);
			}
}

void	lose_events(t_doom *d)
{
	int i;
	
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
					game_mod(d);
					exit(1);
				}
				else if (i == 1)
					exit(1);
				Mix_PlayChannel(3, d->sound.click, 0);
			}
}

void  	level_events(t_doom *d)
{
	int i;
	
	i = -1;
	SDL_Event		ev;
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
						ft_strcpy(d->file_name, "maps/ff"); //bridge
					else if (i == 2)
						ft_strcpy(d->file_name, "maps/towers");
					Mix_PlayChannel(3, d->sound.click, 0);
				}
	}
}

void	dificulty_events(t_doom *d)
{
	int i;
	
	i = -1;
	SDL_Event		ev;
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
						d->difficulty = 1;
					else if (i == 1)
						d->difficulty = 2;
					else if (i == 2)
						d->difficulty = 4;
					d->start_quit = 1;
					Mix_PlayChannel(3, d->sound.click, 0);
				}
	}
}

void	draw_menu(t_doom *d)
{
	int			i;

	i = -1;
	menu_mouse(d);
	while (++i <= d->menu.opt)
		SDL_BlitSurface(d->menu.m[i], NULL, d->sdl.surface, &d->menu.pos[i]);
	
}

void	menu_mouse(t_doom *d)
{
	int			i;
	int			select[3] = {0, 0, 0};
	
	i = -1;
	while (++i < d->menu.opt)
	{
		if (in_rect(&d->menu, i) != 0)
		{
			select[i] = 1;
			SDL_FreeSurface(d->menu.m[i]);
			d->menu.m[i] = TTF_RenderText_Solid(
				d->texture.fonts[MENU_F].text_font, d->menu.title[i], d->menu.col[1]);
		}
		else
		{
			select[i] = 0;
			SDL_FreeSurface(d->menu.m[i]);
			d->menu.m[i] = TTF_RenderText_Solid(
				d->texture.fonts[MENU_F].text_font, d->menu.title[i], d->menu.col[0]);
		}
	}
}

int in_rect(t_menu *menu, int opt)
{
	int			x;
	int			y;

	SDL_GetMouseState(&x, &y);
	if (x >= menu->pos[opt].x &&
		x <= menu->pos[opt].x + menu->m[opt]->w &&
		y >= menu->pos[opt].y &&
		y <= menu->pos[opt].y + menu->m[opt]->h)
		return (1);
	return (0);
}