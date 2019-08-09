/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:58:28 by mmasyush          #+#    #+#             */
/*   Updated: 2019/08/06 20:02:14 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	draw_ui(t_doom *d)
{
	gun_anim(d);
	int i;
	int temp;

	i = -1;
	temp = d->game.hp_level;
	while(i++ < 3)
	{
		if (d->game.hp_level == 100)
			d->ui.masage[2 - i] = temp % 10 + '0';
		else
			d->ui.masage[1 - i] = temp % 10 + '0';
		temp /= 10; 
	}
	if (d->game.hp_level == 100)
		d->ui.masage[3] = 0;
	else
		d->ui.masage[2] = 0;
	d->ui.message = TTF_RenderText_Solid(d->texture.fonts[HP_F].text_font, d->ui.masage, d->texture.fonts[HP_F].text_color);
	SDL_BlitSurface(d->ui.message, NULL, d->sdl.surface, &d->texture.hp_r);
	SDL_FreeSurface(d->ui.message);
	SDL_BlitSurface(d->texture.visor, 0, d->sdl.surface, 0);
}

void    gun_anim(t_doom *d)
{
	int i;
	int temp;
	int anim_gun;

	temp = d->ui.ammo_1;
    if (d->ui.gun_num == 0)
	{
   		if (d->ui.fire == 0)
		{
			ft_strcpy(d->ui.masage, "2 / ");
			if (d->ui.ammo_1 >= 10)
			{
				i = 6;
				while(i-- > 4)
				{
						d->ui.masage[i] = temp % 10 + '0';
					temp /= 10; 
				}
				d->ui.masage[7] = 0;
			}
			else
			{
				d->ui.masage[4] = temp % 10 + '0';
				d->ui.masage[5] = 0;
			}
			SDL_BlitSurface(d->texture.gun1[0], 0, d->sdl.surface, &d->texture.gun1_r);
			if (d->ui.ammo_1 >= 0)
				d->ui.message = TTF_RenderText_Solid(d->texture.fonts[AMMO_F].text_font, d->ui.masage, d->texture.fonts[FPS_F].text_color);
			else if (d->ui.ammo_1 < 0)
				d->ui.message = TTF_RenderText_Solid(d->texture.fonts[AMMO_F].text_font,
					" 0 / 0", d->texture.fonts[FPS_F].text_color);
		}
		else if (d->ui.fire == 1)
		{
			if (d->ui.ammo_1 >= 0)
			{
				ft_strcpy(d->ui.masage, "- / ");
				if (d->ui.ammo_1 >= 10)
				{
					i = 6;
					while(i-- > 4)
					{
						d->ui.masage[i] = temp % 10 + '0';
						temp /= 10; 
					}
					d->ui.masage[7] = 0;
				}
				else
				{
					d->ui.masage[4] = temp % 10 + '0';
					d->ui.masage[5] = 0;
				}
				if (!(Mix_Playing(3)))
					Mix_PlayChannel(3, d->sound.gun1[0], 0);
				SDL_BlitSurface(d->texture.gun1[d->ui.gun_anim], 0, d->sdl.surface, &d->texture.gun1_r);
				d->ui.message = TTF_RenderText_Solid(d->texture.fonts[AMMO_F].text_font, d->ui.masage, d->texture.fonts[FPS_F].text_color);
				d->ui.gun_anim = ((d->ui.prevTime - d->ui.start) * 400 / d->game.dt / 1000) % 21 + 1;
				if (d->ui.gun_anim > 20)
				{
					d->ui.fire = 0;
					d->ui.gun_anim = 0;
				}
			}
			else if (d->ui.ammo_1 == -2)
			{
				if (!(Mix_Playing(3)))
					Mix_PlayChannel(3, d->sound.gun1[1], 0);
				SDL_BlitSurface(d->texture.gun1[d->ui.gun_anim], 0, d->sdl.surface, &d->texture.gun1_r);
				d->ui.message = TTF_RenderText_Solid(d->texture.fonts[AMMO_F].text_font,
					" 0 / 0", d->texture.fonts[FPS_F].text_color);
				d->ui.gun_anim = ((d->ui.prevTime - d->ui.start) * 400 / d->game.dt / 1000) % 3 + 1;
				if (d->ui.gun_anim > 2)
				{
					d->ui.fire = 0;
					d->ui.gun_anim = 0;
				}
			}
			else if (d->ui.ammo_1 < -2)
			{
				if (!(Mix_Playing(3)))
					Mix_PlayChannel(3, d->sound.gun1[2], 0);
				SDL_BlitSurface(d->texture.gun1[0], 0, d->sdl.surface, &d->texture.gun1_r);
				d->ui.message = TTF_RenderText_Solid(d->texture.fonts[AMMO_F].text_font,
					" 0 / 0", d->texture.fonts[FPS_F].text_color);
				d->ui.gun_anim = 0;
				d->ui.fire = 0;
				d->ui.ammo_1 = -2;
			}
		}
		SDL_BlitSurface(d->ui.message, NULL, d->sdl.surface, &d->texture.ammo_r);
		SDL_FreeSurface(d->ui.message);
	}
	else if (d->ui.gun_num == 1)
	{
		if (d->ui.start_saw < 10)
		{
			SDL_BlitSurface(d->texture.gun2[d->ui.start_saw ], 0, d->sdl.surface, &d->texture.gun21_r);
			d->ui.start_saw = (d->ui.currTime / 100) % 11;
			if (!(Mix_Playing(3)))
				Mix_PlayChannel(3, d->sound.gun2[0], 0);
		}
		else if (d->ui.start_saw == 10 && d->ui.fire == 1)
		{
			d->game.fire = 1;
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
			if (!(Mix_Playing(3)))
				Mix_PlayChannel(3, d->sound.gun2[1], 0);
		}
	}
	else if (d->ui.gun_num == 2)
	{
    	if (d->ui.fire == 0)
			SDL_BlitSurface(d->texture.dude[0], 0, d->sdl.surface, &d->texture.dude_r);
		else if (d->ui.fire > 0)
		{
			if (!(Mix_Playing(3)))
				Mix_PlayChannel(3, d->sound.win, 0);
			SDL_BlitSurface(d->texture.dude[d->ui.fire], 0, d->sdl.surface, &d->texture.dude_r);
			d->ui.fire = ((d->ui.prevTime - d->ui.start) * 200 / d->game.dt / 1000) % 34 + 1;
			if (d->ui.fire > 33)
				d->ui.fire = 0;
		}
	}
}