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
	int			opt;
	char		*t[3] = {"Exit", "Restart", "PAUSE"};
	SDL_Color	col[2] = {{255, 255, 255, 0}, {255, 0, 0, 0}};

	opt = 3;
	d->menu.m[0] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[0], col[0]);
	d->menu.m[1] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[1], col[0]);
	d->menu.m[2] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[2], col[1]);
	d->menu.pos[0].x = WIN_WIDTH / 2 - d->menu.m[0]->w / 2;
	d->menu.pos[0].y = WIN_HEIGHT / 2 - d->menu.m[0]->h;
	d->menu.pos[0].w = WIN_WIDTH / 7;
	d->menu.pos[0].h = WIN_HEIGHT / 7;
	d->menu.pos[1].x = WIN_WIDTH / 2 - d->menu.m[1]->w / 2;
	d->menu.pos[1].y = WIN_HEIGHT / 2 + d->menu.m[1]->h;
	d->menu.pos[1].w = WIN_WIDTH / 7;
	d->menu.pos[1].h = WIN_HEIGHT / 7;
	d->menu.pos[2].x = WIN_WIDTH / 2 - d->menu.m[2]->w / 2;
	SDL_BlitScaled(d->texture.pause, 0, d->sdl.surface, 0);
	draw_menu(d, opt, t, col);
}

void	show_lose(t_doom *d)
{
	int			opt;
	char		*t[3] = {"Exit", "Restart", "YOU ARE DEAD!"};
	SDL_Color	col[2] = {{102, 0, 0, 0}, {204, 229, 255, 0}};

	opt = 3;
	d->menu.m[0] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[0], col[0]);
	d->menu.m[1] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[1], col[0]);
	d->menu.m[2] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[2], (SDL_Color){255, 0, 0, 0});
	d->menu.pos[0].x = WIN_WIDTH / 2 - d->menu.m[0]->w / 2;
	d->menu.pos[0].y = WIN_HEIGHT / 2 - d->menu.m[0]->h;
	d->menu.pos[0].w = WIN_WIDTH / 7;
	d->menu.pos[0].h = WIN_HEIGHT / 7;
	d->menu.pos[1].x = WIN_WIDTH / 2 - d->menu.m[1]->w / 2;
	d->menu.pos[1].y = WIN_HEIGHT / 2 + d->menu.m[1]->h;
	d->menu.pos[1].w = WIN_WIDTH / 7;
	d->menu.pos[1].h = WIN_HEIGHT / 7;
	d->menu.pos[2].x = WIN_WIDTH / 2 - d->menu.m[2]->w / 2;
	SDL_BlitScaled(d->texture.lose, 0, d->sdl.surface, 0);
	draw_menu(d, opt, t, col);
}

void	show_start(t_doom *d)
{
	int			opt;
	char		*t[3] = {"Play", "Createmap", "DOOM-NUKEM 3D"};
	SDL_Color	col[2] = {{255, 255, 255, 0}, {200, 20, 10, 0}};

	opt = 3;
	d->menu.m[0] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[0], col[0]);
	d->menu.m[1] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[1], col[0]);
	d->menu.m[2] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[2], col[1]);
	d->menu.pos[0].x = WIN_WIDTH / 2 - d->menu.m[0]->w / 2;
	d->menu.pos[0].y = WIN_HEIGHT / 2 - d->menu.m[0]->h;
	d->menu.pos[0].w = WIN_WIDTH / 7;
	d->menu.pos[0].h = WIN_HEIGHT / 7;
	d->menu.pos[1].x = WIN_WIDTH / 2 - d->menu.m[1]->w / 2;
	d->menu.pos[1].y = WIN_HEIGHT / 2 + d->menu.m[1]->h;
	d->menu.pos[1].w = WIN_WIDTH / 7;
	d->menu.pos[1].h = WIN_HEIGHT / 7;
	d->menu.pos[2].x = WIN_WIDTH / 2 - d->menu.m[2]->w / 2;
	SDL_BlitScaled(d->texture.start, 0, d->sdl.surface, 0);
	draw_menu(d, opt, t, col);
}

void	draw_menu(t_doom *d, int opt, char **title, SDL_Color *col)
{
	int			i;

	i = -1;
	if (d->ev.type == SDL_MOUSEMOTION)
		menu_mouse(d, opt, title, col);
	else if (d->ev.type == SDL_MOUSEBUTTONDOWN)
	{
		if (d->ev.motion.x >= d->menu.pos[0].x &&
			d->ev.motion.x <= d->menu.pos[0].x + d->menu.pos[0].w &&
			d->ev.motion.y >= d->menu.pos[0].y &&
			d->ev.motion.y <= d->menu.pos[0].y + d->menu.pos[0].h)
			exit(1);
		else if (d->ev.motion.x >= d->menu.pos[1].x &&
				d->ev.motion.x <= d->menu.pos[1].x + d->menu.pos[1].w &&
				d->ev.motion.y >= d->menu.pos[1].y &&
				d->ev.motion.y <= d->menu.pos[1].y + d->menu.pos[1].h)
			system("./doom-nukem play maps/fool && exit");
            // system("exec ./doom-nukem && exit");
	}
	else if (d->ev.type == SDL_KEYDOWN && d->ev.key.keysym.sym == PAUSE)
		while (++i < opt)
			SDL_FreeSurface(d->menu.m[i]);
	i = -1;
	while (++i < opt)
		SDL_BlitSurface(d->menu.m[i], NULL, d->sdl.surface, &d->menu.pos[i]);
}

void	menu_mouse(t_doom *d, int opt, char **t, SDL_Color *col)
{
	int			i;
	int			select[2] = {0, 0};

	i = -1;
	while (++i < opt - 1)
	{
		if (d->ev.motion.x >= d->menu.pos[i].x &&
			d->ev.motion.x <= d->menu.pos[i].x + d->menu.pos[i].w &&
			d->ev.motion.y >= d->menu.pos[i].y &&
			d->ev.motion.y <= d->menu.pos[i].y + d->menu.pos[i].h)
		{
			if (select[i] == 0)
			{
				select[i] = 1;
				SDL_FreeSurface(d->menu.m[i]);
				d->menu.m[i] = TTF_RenderText_Solid(
					d->texture.fonts[MENU_F].text_font, t[i], col[1]);
			}
		}
		else
		{
			select[i] = 0;
			SDL_FreeSurface(d->menu.m[i]);
			d->menu.m[i] = TTF_RenderText_Solid(
				d->texture.fonts[MENU_F].text_font, t[i], col[0]);
		}
	}
}
