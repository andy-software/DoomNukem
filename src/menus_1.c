/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanylch <mdanylch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 18:59:34 by mdanylch          #+#    #+#             */
/*   Updated: 2019/08/23 19:00:15 by mdanylch         ###   ########.fr       */
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

void	show_start(t_doom *d)
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

void	chose_level(t_doom *d)
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
