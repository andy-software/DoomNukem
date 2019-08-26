/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_gun_fire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanylch <mdanylch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:37:16 by mdanylch          #+#    #+#             */
/*   Updated: 2019/08/26 20:55:31 by mdanylch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static	void	gun_anim_2(t_doom *d, int i, int temp)
{
	ft_strcpy(d->ui.str, "2 / ");
	if (d->ui.ammo_1 >= 10)
	{
		i = 6;
		while (--i > 3)
		{
			d->ui.str[i] = temp % 10 + '0';
			temp /= 10;
		}
		d->ui.str[6] = 0;
	}
	else
	{
		d->ui.str[4] = temp % 10 + '0';
		d->ui.str[5] = 0;
	}
	SDL_BlitSurface(d->texture.gun1[0], 0, d->sdl.surface, &d->texture.gun1_r);
	if (d->ui.ammo_1 >= 0)
		d->ui.message = TTF_RenderText_Solid(DT.fonts[AMMO_F].text_font, \
			d->ui.str, DT.fonts[FPS_F].text_color);
	else if (d->ui.ammo_1 < 0)
		d->ui.message = TTF_RenderText_Solid(DT.fonts[AMMO_F].text_font, \
			" 0 / 0", d->texture.fonts[FPS_F].text_color);
}

static	void	gun_anim_3(t_doom *d, int i, int temp)
{
	ft_strcpy(d->ui.str, "- / ");
	if (d->ui.ammo_1 >= 10)
	{
		i = 6;
		while (--i > 3)
		{
			d->ui.str[i] = temp % 10 + '0';
			temp /= 10;
		}
		d->ui.str[6] = 0;
	}
	else
	{
		d->ui.str[4] = temp % 10 + '0';
		d->ui.str[5] = 0;
	}
	if (!(Mix_Playing(3)))
		Mix_PlayChannel(3, d->sound.gun1[0], 0);
	SDL_BlitSurface(DT.gun1[d->ui.gun_anim], 0, d->sdl.surface, &DT.gun1_r);
	d->ui.message = TTF_RenderText_Solid(DT.fonts[AMMO_F].text_font, \
					d->ui.str, DT.fonts[FPS_F].text_color);
	d->ui.gun_anim = ((d->ui.prevTime - d->ui.clickTime) / 50);
	if (d->ui.gun_anim > 17)
		INIT2(d->ui.fire, 0, d->ui.gun_anim, 0);
}

static	void	gun_anim_4(t_doom *d, int i, int temp)
{
	if (d->ui.ammo_1 == -2)
	{
		if (!(Mix_Playing(3)))
			Mix_PlayChannel(3, d->sound.gun1[1], 0);
		SDL_BlitSurface(DT.gun1[d->ui.gun_anim], 0, d->sdl.surface, \
			&d->texture.gun1_r);
		d->ui.message = TTF_RenderText_Solid(DT.fonts[AMMO_F].text_font, \
			" 0 / 0", d->texture.fonts[FPS_F].text_color);
		d->ui.gun_anim = ((d->ui.prevTime - d->ui.clickTime) / 50);
		if (d->ui.gun_anim > 1)
			INIT2(d->ui.fire, 0, d->ui.gun_anim, 0);
	}
	else if (d->ui.ammo_1 < -2)
	{
		if (!(Mix_Playing(3)))
			Mix_PlayChannel(3, d->sound.gun1[2], 0);
		SDL_BlitSurface(DT.gun1[0], 0, d->sdl.surface, &d->texture.gun1_r);
		d->ui.message = TTF_RenderText_Solid(DT.fonts[AMMO_F].text_font, \
			" 0 / 0", d->texture.fonts[FPS_F].text_color);
		d->ui.gun_anim = 0;
		d->ui.fire = 0;
		d->ui.ammo_1 = -2;
	}
}

void			ui_gun_num_0(t_doom *d, int i, int temp)
{
	if (d->ui.fire == 0)
	{
		gun_anim_2(d, i, temp);
	}
	else if (d->ui.fire == 1)
	{
		if (d->ui.ammo_1 >= 0)
			gun_anim_3(d, i, temp);
		else
			gun_anim_4(d, i, temp);
	}
	SDL_BlitSurface(d->ui.message, NULL, d->sdl.surface, &d->texture.ammo_r);
	SDL_FreeSurface(d->ui.message);
}
