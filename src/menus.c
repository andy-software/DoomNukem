/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanylch <mdanylch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:00:45 by mmasyush          #+#    #+#             */
/*   Updated: 2019/08/23 19:00:48 by mdanylch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	dificulty_events(t_doom *d)
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
	int		i;

	i = -1;
	menu_mouse(d);
	while (++i <= d->menu.opt)
		SDL_BlitSurface(d->menu.m[i], NULL, d->sdl.surface, &d->menu.pos[i]);
}

void	menu_mouse(t_doom *d)
{
	INT_1(i);
	INTARR(select, 3);
	while (++i < d->menu.opt)
	{
		if (in_rect(&d->menu, i) != 0)
		{
			select[i] = 1;
			SDL_FreeSurface(d->menu.m[i]);
			d->menu.m[i] = TTF_RenderText_Solid(\
			d->texture.fonts[MENU_F].text_font, d->menu.title[i], \
			d->menu.col[1]);
		}
		else
		{
			select[i] = 0;
			SDL_FreeSurface(d->menu.m[i]);
			d->menu.m[i] = TTF_RenderText_Solid(\
			d->texture.fonts[MENU_F].text_font, d->menu.title[i], \
			d->menu.col[0]);
		}
	}
}

int		in_rect(t_menu *menu, int opt)
{
	int		x;
	int		y;

	SDL_GetMouseState(&x, &y);
	if (x >= menu->pos[opt].x &&
		x <= menu->pos[opt].x + menu->m[opt]->w &&
		y >= menu->pos[opt].y &&
		y <= menu->pos[opt].y + menu->m[opt]->h)
		return (1);
	return (0);
}
