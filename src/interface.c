/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanylch <mdanylch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:58:28 by mmasyush          #+#    #+#             */
/*   Updated: 2019/08/26 21:05:32 by mdanylch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	draw_ui(t_doom *d)
{
	INT2(i, temp);
	i = -1;
	gun_anim(d);
	if (d->game.flying == 1)
		fule_show(d);
	temp = d->game.hp_level;
	while (i++ < 3)
	{
		if (d->game.hp_level == 100)
			d->ui.str[2 - i] = temp % 10 + '0';
		else
			d->ui.str[1 - i] = temp % 10 + '0';
		temp /= 10;
	}
	if (d->game.hp_level == 100)
		d->ui.str[3] = 0;
	else
		d->ui.str[2] = 0;
	d->ui.message = TTF_RenderText_Solid(d->texture.fonts[HP_F].text_font, \
		d->ui.str, d->texture.fonts[HP_F].text_color);
	SDL_BlitSurface(d->ui.message, 0, d->sdl.surface, &d->texture.hp_r);
	SDL_FreeSurface(d->ui.message);
	show_keys(d);
	SDL_BlitSurface(d->texture.visor, 0, d->sdl.surface, 0);
}

void	gun_anim(t_doom *d)
{
	INT2(i, temp);
	temp = d->ui.ammo_1;
	if (d->ui.gun_num == 0)
	{
		ui_gun_num_0(d, i, temp);
	}
	else if (d->ui.gun_num == 1)
		ui_gun_num_1(d);
	else if (d->ui.gun_num == 2)
	{
		if (d->ui.fire == 0)
			SDL_BlitSurface(DT.dude[0], 0, d->sdl.surface, &d->texture.dude_r);
		else if (d->ui.fire > 0)
		{
			if (!(Mix_Playing(3)))
				Mix_PlayChannel(3, d->sound.win, 0);
			SDL_BlitSurface(d->texture.dude[d->ui.gun_anim], 0, \
				d->sdl.surface, &d->texture.dude_r);
			d->ui.gun_anim = ((d->ui.prevTime - d->ui.clickTime) / 80);
			if (d->ui.gun_anim > 33)
				INIT2(d->ui.fire, 0, d->ui.gun_anim, 0);
		}
	}
}

void	fule_show(t_doom *d)
{
	SDL_Rect	fuel_r;
	int			i;
	int			temp;

	fuel_r.x = WIN_WIDTH / 1.6;
	fuel_r.y = WIN_HEIGHT / 7;
	ft_strcpy(d->ui.str, "Fuel: ");
	temp = d->game.fuel;
	i = (d->game.fuel == 100) ? 9 : 8;
	while (--i > 5)
	{
		d->ui.str[i] = temp % 10 + '0';
		temp /= 10;
	}
	if (d->game.fuel == 100)
		d->ui.str[9] = 0;
	else
		d->ui.str[8] = 0;
	d->ui.message = TTF_RenderText_Solid(d->texture.fonts[HP_F].text_font,
		d->ui.str, d->texture.fonts[HP_F].text_color);
	SDL_BlitSurface(d->ui.message, NULL, d->sdl.surface, &fuel_r);
	SDL_FreeSurface(d->ui.message);
}

void	show_keys(t_doom *d)
{
	SDL_Rect	pos[3];

	pos[0].x = WIN_WIDTH - d->texture.keys->w;
	pos[0].y = WIN_HEIGHT / 3;
	pos[1].x = WIN_WIDTH - d->texture.keys->w;
	pos[1].y = WIN_HEIGHT / 3 + d->texture.keys->h / 3;
	pos[2].x = WIN_WIDTH - d->texture.keys->w;
	pos[2].y = WIN_HEIGHT / 3 + DT.keys->h / 3 + DT.keys->h / 3;
	if (d->game.picked_key[0] == 0 || d->game.picked_key[1] == 0 || \
		d->game.picked_key[2] == 0)
		SDL_BlitSurface(DT.keys, 0, d->sdl.surface, &DT.keys_r);
	if (d->game.picked_key[0] == 1)
		SDL_BlitSurface(DT.sprt[3].sprites[0], 0, d->sdl.surface, &pos[0]);
	if (d->game.picked_key[1] == 1)
		SDL_BlitSurface(DT.sprt[3].sprites[1], 0, d->sdl.surface, &pos[1]);
	if (d->game.picked_key[2] == 1)
		SDL_BlitSurface(DT.sprt[3].sprites[2], 0, d->sdl.surface, &pos[2]);
}
