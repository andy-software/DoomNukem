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
	char		*t[3] = {"Resume", "Exit", "PAUSE"};
	SDL_Color	col[2] = {{255, 255, 255, 0}, {255, 0, 0, 0}};

	opt = 2;
	d->menu.m[0] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[0], col[0]);
	d->menu.m[1] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[1], col[0]);
	d->menu.m[2] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[2], col[1]);
	d->menu.pos[0].x = WIN_WIDTH / 2 - d->menu.m[0]->w / 2;
	d->menu.pos[0].y = WIN_HEIGHT / 2 - d->menu.m[0]->h;
	d->menu.pos[0].h = WIN_HEIGHT / 7;
	d->menu.pos[1].x = WIN_WIDTH / 2 - d->menu.m[1]->w / 2;
	d->menu.pos[1].y = WIN_HEIGHT / 2 + d->menu.m[1]->h;
	d->menu.pos[1].h = WIN_HEIGHT / 7;
	d->menu.pos[2].x = WIN_WIDTH / 2 - d->menu.m[2]->w / 2;
	SDL_BlitScaled(d->texture.pause, 0, d->sdl.surface, 0);
	draw_menu(d, opt, t, col);
}

void	    show_start(t_doom *d)
{
	int			opt;
	char		*t[4] = {"Play", "Change difficulty", "Exit", "DOOM-NUKEM 3D"};
	SDL_Color	col[2];

	*col = 		(SDL_Color){255, 255, 255, 0};
 	*(col + 1)  = (SDL_Color){200, 20, 10, 0};
	opt = 3;
	d->menu.m[0] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[0], col[0]);
	d->menu.m[1] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[1], col[0]);
	d->menu.m[2] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[2], col[0]);
	d->menu.m[3] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[3], col[1]);
	d->menu.pos[0].x = WIN_WIDTH / 2 - d->menu.m[0]->w / 2;
	d->menu.pos[0].y = WIN_HEIGHT / 2 - d->menu.m[0]->h;
	d->menu.pos[1].x = WIN_WIDTH / 2 - d->menu.m[1]->w / 2;
	d->menu.pos[1].y = WIN_HEIGHT / 2 + d->menu.m[1]->h;
	d->menu.pos[2].x = WIN_WIDTH / 2 - d->menu.m[2]->w / 2;
	d->menu.pos[2].y = WIN_HEIGHT / 2 + (d->menu.m[2]->h * 3);
	d->menu.pos[3].x = WIN_WIDTH / 2 - d->menu.m[3]->w / 2;
	SDL_BlitScaled(d->texture.start, 0, d->sdl.surface, 0);
	draw_menu(d, opt, t, col);
}

void	show_lose(t_doom *d)
{
	int			opt;
	char		*t[3] = {"Exit", "Restart", "YOU ARE DEAD!"};
	SDL_Color	col[2] = {{102, 0, 0, 0}, {204, 229, 255, 0}};

	opt = 2;
	d->menu.m[0] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[0], col[0]);
	d->menu.m[1] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[1], col[0]);
	d->menu.m[2] = TTF_RenderText_Solid(
		d->texture.fonts[MENU_F].text_font, t[2], (SDL_Color){255, 0, 0, 0});
	d->menu.pos[0].x = WIN_WIDTH / 2 - d->menu.m[0]->w / 2;
	d->menu.pos[0].y = WIN_HEIGHT / 2 - d->menu.m[0]->h;
	d->menu.pos[1].x = WIN_WIDTH / 2 - d->menu.m[1]->w / 2;
	d->menu.pos[1].y = WIN_HEIGHT / 2 + d->menu.m[1]->h;
	d->menu.pos[2].x = WIN_WIDTH / 2 - d->menu.m[2]->w / 2;
	SDL_BlitScaled(d->texture.lose, 0, d->sdl.surface, 0);
	draw_menu(d, opt, t, col);
}

void	draw_menu(t_doom *d, int opt, char **title, SDL_Color *col)
{
	int			i;
	int			x;
	int			y;

	i = -1;
	if (d->ev.type == SDL_MOUSEMOTION)
		menu_mouse(d, opt, title, col);
	else if (d->ev.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);
		while (++i < opt)
		{
			if (x >= d->menu.pos[i].x &&
				x <= d->menu.pos[i].x + d->menu.m[i]->w &&
				y >= d->menu.pos[i].y &&
				y <= d->menu.pos[i].y + d->menu.m[i]->h)
				{
					if (i == opt - 1)
						exit(1);
					else if (i == 0 && d->game.start == 1)
					{
						d->game.start = 0;
						set_mouse(d);
					}
				}
		}
	}
	else if (d->ev.type == SDL_KEYDOWN && d->ev.key.keysym.sym == PAUSE)
		while (++i <= opt)
			SDL_FreeSurface(d->menu.m[i]);
	// }
	i = -1;
	while (++i <= opt)
    {
		SDL_BlitSurface(d->menu.m[i], NULL, d->sdl.surface, d->menu.pos+i);
        SDL_FreeSurface(d->menu.m[i]);
    }
}

void	menu_mouse(t_doom *d, int opt, char **t, SDL_Color *col)
{
	int			i;
	int			select[3] = {0, 0, 0};
	int			x;
	int			y;

	i = -1;
	SDL_GetMouseState(&x, &y);
	while (++i < opt)
	{
		if (x >= d->menu.pos[i].x &&
			x <= d->menu.pos[i].x + d->menu.m[i]->w &&
			y >= d->menu.pos[i].y &&
			y <= d->menu.pos[i].y + d->menu.m[i]->h)
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
