/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:00:45 by mmasyush          #+#    #+#             */
/*   Updated: 2019/07/25 15:00:46 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	show_pause(t_doom *d)
{
	d->menu.opt = 3;
	d->menu.title[0] = "Continue";
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
	SDL_BlitScaled(d->texture.pause, 0, d->sdl.surface, 0);
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
	d->menu.pos[0].y = WIN_HEIGHT / 2 - d->menu.m[0]->h;
	d->menu.pos[1].x = WIN_WIDTH / 2 - d->menu.m[1]->w / 2;
	d->menu.pos[1].y = WIN_HEIGHT / 2 + d->menu.m[1]->h;
	d->menu.pos[2].x = WIN_WIDTH / 2 - d->menu.m[2]->w / 2;
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
	SDL_BlitScaled(d->texture.lose, 0, d->sdl.surface, 0);
}

void	    chose_level(t_doom *d)
{
	d->menu.opt = 3;
	d->menu.title[0] = "Level 1";
	d->menu.title[1] = "Level 2";
	d->menu.title[2] = "Level 3";
	d->menu.title[3] = "DOOM-NUKEM 3D";
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
	SDL_BlitScaled(d->texture.start, 0, d->sdl.surface, 0);
}

void	    chose_dificulty(t_doom *d)
{
	d->menu.opt = 3;
	d->menu.title[0] = "Easy";
	d->menu.title[1] = "Classic";
	d->menu.title[2] = "SupaHard";
	d->menu.title[3] = "DOOM-NUKEM 3D";
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
	SDL_BlitScaled(d->texture.start, 0, d->sdl.surface, 0);
}

void	start_events(t_doom *d)
{
	int			x;
	int			y;
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
		{
			SDL_GetMouseState(&x, &y);
			while (++i < d->menu.opt)
			{
				if (x >= d->menu.pos[i].x &&
					x <= d->menu.pos[i].x + d->menu.m[i]->w &&
					y >= d->menu.pos[i].y &&
					y <= d->menu.pos[i].y + d->menu.m[i]->h)
					{
						if (i == 0)
							d->start_quit = 1;
						else if (i == 1)
							exit(1);
					}
			}
		}
	}
}

void	pause_events(t_doom *d)
{
	int			x;
	int			y;
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
		if (ev.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_GetMouseState(&x, &y);
			while (++i < d->menu.opt)
			{
				printf("%d\n", i);
				if (x >= d->menu.pos[i].x &&
					x <= d->menu.pos[i].x + d->menu.m[i]->w &&
					y >= d->menu.pos[i].y &&
					y <= d->menu.pos[i].y + d->menu.m[i]->h)
					{
						if (i == 0)
							d->game.pause = 0;
						else if (i == 1)
							exit(1);
						else if (i == 2)
							exit(1);
					}
			}
		}
	}
}

void	lose_events(t_doom *d)
{
	int			x;
	int			y;
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
		{
			SDL_GetMouseState(&x, &y);
			while (++i < d->menu.opt)
			{
				if (x >= d->menu.pos[i].x &&
					x <= d->menu.pos[i].x + d->menu.m[i]->w &&
					y >= d->menu.pos[i].y &&
					y <= d->menu.pos[i].y + d->menu.m[i]->h)
					{
						if (i == 0)
							exit(1);
						else if (i == 1)
							exit(1);
					}
			}
		}
	}
}

void  	level_events(t_doom *d)
{
	int			x;
	int			y;
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
		{
			SDL_GetMouseState(&x, &y);
			while (++i < d->menu.opt)
			{
				if (x >= d->menu.pos[i].x &&
					x <= d->menu.pos[i].x + d->menu.m[i]->w &&
					y >= d->menu.pos[i].y &&
					y <= d->menu.pos[i].y + d->menu.m[i]->h)
					{
						if (i == 0)
						{
							ft_strcpy(d->file_name, "maps/level1");
						}
						else if (i == 1)
						{
							ft_strcpy(d->file_name, "maps/level6");
						}
						else if (i == 2)
						{
							ft_strcpy(d->file_name, "maps/level6");
						}
					}
			}
		}
	}
}

void	dificulty_events(t_doom *d)
{
	int			x;
	int			y;
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
		{
			SDL_GetMouseState(&x, &y);
			while (++i < d->menu.opt)
			{
				if (x >= d->menu.pos[i].x &&
					x <= d->menu.pos[i].x + d->menu.m[i]->w &&
					y >= d->menu.pos[i].y &&
					y <= d->menu.pos[i].y + d->menu.m[i]->h)
					{
						if (i == 0)
						{
							d->start_quit = 1;
							d->difficulty = 1;
						}
						else if (i == 1)
						{
							d->start_quit = 1;
							d->difficulty = 2;
						}
						else if (i == 2)
						{
							d->start_quit = 1;
							d->difficulty = 4;
						}
					}
			}
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
	int			x;
	int			y;

	i = -1;
	SDL_GetMouseState(&x, &y);
	while (++i < d->menu.opt)
	{
		if (x >= d->menu.pos[i].x &&
			x <= d->menu.pos[i].x + d->menu.m[i]->w &&
			y >= d->menu.pos[i].y &&
			y <= d->menu.pos[i].y + d->menu.m[i]->h)
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
