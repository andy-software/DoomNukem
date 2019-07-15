/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:58:28 by mmasyush          #+#    #+#             */
/*   Updated: 2019/07/02 14:58:28 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	draw_ui(t_doom *d)
{
	gun_anim(d);
   	// SDL_BlitSurface(d->texture.cross, 0, d->sdl.surface, &d->texture.cross_r);
    // SDL_BlitSurface(d->texture.visor, 0, d->sdl.surface, 0);
	// SDL_BlitSurface(d->texture.visor[1], 0, d->sdl.surface, 0);
}

void    gun_anim(t_doom *d)
{
	char *str = NULL;
	char *str1 = NULL;

    if (d->ui.gun_num == 0)
	{
   		if (d->ui.fire == 0)
		{
			str1 = ft_itoa(d->ui.ammo_1);
			str = ft_strjoin(" 2 / ", str1);
			SDL_BlitSurface(d->texture.gun1[0], 0, d->sdl.surface, &d->texture.gun1_r);
			if (d->ui.ammo_1 >= 0)
				d->ui.message = TTF_RenderText_Solid(d->texture.fonts[0].text_font, str, d->texture.fonts[0].text_color);
			else if (d->ui.ammo_1 < 0)
				d->ui.message = TTF_RenderText_Solid(d->texture.fonts[0].text_font,
					" 0 / 0", d->texture.fonts[0].text_color);
		}
		else if (d->ui.fire > 0)
		{
			if (d->ui.ammo_1 >= 0)
			{
				str1 = ft_itoa(d->ui.ammo_1);
				str = ft_strjoin(" - / ", str1);
				if (!(Mix_Playing(2)))
					Mix_PlayChannel(2, d->sound.gun1[0], 0);
				SDL_BlitSurface(d->texture.gun1[d->ui.fire], 0, d->sdl.surface, &d->texture.gun1_r);
				d->ui.message = TTF_RenderText_Solid(d->texture.fonts[0].text_font, str, d->texture.fonts[0].text_color);
				d->ui.fire = ((d->ui.prevTime - d->ui.start) * 400 / d->game.dt / 1000) % 21 + 1;
				if (d->ui.fire > 20)
					d->ui.fire = 0;
			}
			else if (d->ui.ammo_1 == -2)
			{
				if (!(Mix_Playing(3)))
					Mix_PlayChannel(3, d->sound.gun1[1], 0);
				SDL_BlitSurface(d->texture.gun1[d->ui.fire], 0, d->sdl.surface, &d->texture.gun1_r);
				d->ui.message = TTF_RenderText_Solid(d->texture.fonts[0].text_font,
					" 0 / 0", d->texture.fonts[0].text_color);
				d->ui.fire = ((d->ui.prevTime - d->ui.start) * 400 / d->game.dt / 1000) % 3 + 1;
				if (d->ui.fire > 2)
					d->ui.fire = 0;
			}
			else if (d->ui.ammo_1 < -2)
			{
				if (!(Mix_Playing(4)))
					Mix_PlayChannel(4, d->sound.gun1[2], 0);
				SDL_BlitSurface(d->texture.gun1[0], 0, d->sdl.surface, &d->texture.gun1_r);
				d->ui.message = TTF_RenderText_Solid(d->texture.fonts[0].text_font,
					" 0 / 0", d->texture.fonts[0].text_color);
				d->ui.fire = 0;
				d->ui.ammo_1 = -2;
			}
		}
		SDL_BlitSurface(d->ui.message, NULL, d->sdl.surface, &d->texture.ammo_r);
		free(str);
		free(str1);
		SDL_FreeSurface(d->ui.message);
	}
	else if (d->ui.gun_num == 1)
	{
		if (d->ui.start_saw  < 10)
		{
			SDL_BlitSurface(d->texture.gun2[d->ui.start_saw ], 0, d->sdl.surface, &d->texture.gun21_r);
			d->ui.start_saw = (d->ui.currTime / 100) % 11;
			if (!(Mix_Playing(2)))
				Mix_PlayChannel(2, d->sound.gun2[0], 0);
		}
		else if (d->ui.start_saw == 10 && d->ui.fire == 1)
		{
			if (d->ui.idle == 0)
			{
				SDL_BlitSurface(d->texture.gun2[14], 0, d->sdl.surface, &d->texture.gun22_r);
				d->ui.idle = 1;
			}
			else if (d->ui.idle == 1)
			{
				SDL_BlitSurface(d->texture.gun2[15], 0, d->sdl.surface, &d->texture.gun22_r);
				d->ui.idle = 0;
			}
			if (!(Mix_Playing(3)))
				Mix_PlayChannel(3, d->sound.gun2[2], 0);
		}
		else if (d->ui.start_saw == 10)
		{
			if (d->ui.idle == 0)
			{
				SDL_BlitSurface(d->texture.gun2[10], 0, d->sdl.surface, &d->texture.gun21_r);
				d->ui.idle = 1;
			}
			else if (d->ui.idle == 1)
			{
				SDL_BlitSurface(d->texture.gun2[11], 0, d->sdl.surface, &d->texture.gun21_r);
				d->ui.idle = 0;
			}
			if (!(Mix_Playing(4)))
				Mix_PlayChannel(4, d->sound.gun2[1], 0);
		}
	}
	else if (d->ui.gun_num == 2)
	{
    	if (d->ui.fire == 0)
			SDL_BlitSurface(d->texture.dude[0], 0, d->sdl.surface, &d->texture.dude_r);
		else if (d->ui.fire <= 34)
		{
			if (!(Mix_Playing(2)))
				Mix_PlayChannel(2, d->sound.win, 0);
			SDL_BlitSurface(d->texture.dude[d->ui.fire], 0, d->sdl.surface, &d->texture.dude_r);
			d->ui.fire = ((d->ui.prevTime - d->ui.start) * 150 / d->game.dt / 1000) % 34 + 1;
			if (d->ui.fire > 33)
				d->ui.fire = 0;
		}
	}
}