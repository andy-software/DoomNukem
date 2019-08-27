/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:58:28 by mmasyush          #+#    #+#             */
/*   Updated: 2019/08/12 16:40:44 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	draw_ui(t_doom *d)
{
	gun_anim(d);
	if (d->game.flying == 1)
		fule_show(d);
	int i;
	int temp;

	i = -1;
	temp = d->game.hp_level;
	while(i++ < 3)
	{
		if (d->game.hp_level == 100)
			d->ui.str[2 - i] = temp % 10 + '0';
		else
			d->ui.str[1 - i] = temp % 10 + '0';
		temp /= 10; 
	}
	(d->game.hp_level == 100) ? (d->ui.str[3] = 0) : (d->ui.str[2] = 0);
	d->ui.message = TTF_RenderText_Solid(d->texture.fonts[HP_F].text_font, d->ui.str, d->texture.fonts[HP_F].text_color);
	SDL_BlitSurface(d->ui.message, 0, d->sdl.surface, &d->texture.hp_r);
	SDL_FreeSurface(d->ui.message);
	show_keys(d);
	SDL_BlitSurface(d->texture.visor, 0, d->sdl.surface, 0);
}

void    gun_anim(t_doom *d)
{
	int i;
	int temp;
	

	temp = d->ui.ammo_1;
    if (d->ui.gun_num == 0)
	{
   		if (d->ui.fire == 0)
		{
			ft_strcpy(d->ui.str, "2 / ");
			if (d->ui.ammo_1 >= 10)
			{
				i = 6;
				while(--i > 3)
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
				d->ui.message = TTF_RenderText_Solid(d->texture.fonts[AMMO_F].text_font, d->ui.str, d->texture.fonts[FPS_F].text_color);
			else if (d->ui.ammo_1 < 0)
				d->ui.message = TTF_RenderText_Solid(d->texture.fonts[AMMO_F].text_font,
					" 0 / 0", d->texture.fonts[FPS_F].text_color);
		}
		else if (d->ui.fire == 1)
		{
			if (d->ui.ammo_1 >= 0)
			{
				ft_strcpy(d->ui.str, "- / ");
				if (d->ui.ammo_1 >= 10)
				{
					i = 6;
					while(--i > 3)
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
				SDL_BlitSurface(d->texture.gun1[d->ui.gun_anim], 0, d->sdl.surface, &d->texture.gun1_r);
				d->ui.message = TTF_RenderText_Solid(d->texture.fonts[AMMO_F].text_font, d->ui.str, d->texture.fonts[FPS_F].text_color);
				d->ui.gun_anim = ((d->ui.prevTime - d->ui.clickTime) / 50);
				if (d->ui.gun_anim > 17)
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
				d->ui.gun_anim = ((d->ui.prevTime - d->ui.clickTime) / 50);
				if (d->ui.gun_anim > 1)
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
			SDL_BlitSurface(d->texture.gun2[d->ui.start_saw], 0, d->sdl.surface, &d->texture.gun21_r);
			d->ui.start_saw = ((d->ui.prevTime - d->ui.clickTime) / 50);
			if (!(Mix_Playing(3)))
				Mix_PlayChannel(3, d->sound.gun2[0], 0);
		}
		else if (d->ui.start_saw == 10 && d->ui.fire == 1)
		{
			d->game.fire = 1;
			if (d->ui.idle == 0)
			{
				SDL_BlitSurface(d->texture.gun2[14 + d->game.blood * 2], 0, d->sdl.surface, &d->texture.gun22_r);
				d->ui.idle = 1;
			}
			else if (d->ui.idle == 1)
			{
				SDL_BlitSurface(d->texture.gun2[15 + d->game.blood * 2], 0, d->sdl.surface, &d->texture.gun22_r);
				d->ui.idle = 0;
			}
			if (!(Mix_Playing(3)))
				Mix_PlayChannel(3, d->sound.gun2[2], 0);
		}
		else if (d->ui.start_saw == 10)
		{
			if (d->ui.idle == 0)
			{
				SDL_BlitSurface(d->texture.gun2[10 + d->game.blood * 2], 0, d->sdl.surface, &d->texture.gun21_r);
				d->ui.idle = 1;
			}
			else if (d->ui.idle == 1)
			{
				SDL_BlitSurface(d->texture.gun2[11 + d->game.blood * 2], 0, d->sdl.surface, &d->texture.gun21_r);
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
			SDL_BlitSurface(d->texture.dude[d->ui.gun_anim], 0, d->sdl.surface, &d->texture.dude_r);
			d->ui.gun_anim = ((d->ui.prevTime - d->ui.clickTime) / 80);
			if (d->ui.gun_anim > 33)
			{
				d->ui.fire = 0;
				d->ui.gun_anim = 0;
			}
		}
	}
}

void	fule_show(t_doom *d)
{
	SDL_Rect		fuel_r;
	int i;
	int temp;
	fuel_r.x = WIN_WIDTH / 1.6;
	fuel_r.y = WIN_HEIGHT / 7;
	ft_strcpy(d->ui.str, "Fuel: ");
	temp = d->game.fuel;
	i = (d->game.fuel == 100) ? 9 : 8;
	while(--i > 5)
	{
		d->ui.str[i] = temp % 10 + '0';
		temp /= 10;
	}
	(d->game.fuel == 100) ? (d->ui.str[9] = 0) : (d->ui.str[8] = 0);
	d->ui.message = TTF_RenderText_Solid(d->texture.fonts[HP_F].text_font,
		d->ui.str, d->texture.fonts[HP_F].text_color);
	SDL_BlitSurface(d->ui.message, NULL, d->sdl.surface, &fuel_r);
	SDL_FreeSurface(d->ui.message);
}

void show_keys(t_doom *d)
{
	SDL_Rect 	pos[3];
	pos[0].x = WIN_WIDTH - d->texture.keys->w;
	pos[0].y = WIN_HEIGHT / 3;
	pos[1].x = WIN_WIDTH - d->texture.keys->w;
	pos[1].y = WIN_HEIGHT / 3 + d->texture.keys->h / 3;
	pos[2].x = WIN_WIDTH - d->texture.keys->w;
	pos[2].y = WIN_HEIGHT / 3 + d->texture.keys->h / 3 + d->texture.keys->h /3;
	if (d->game.picked_key[0] == 0 || d->game.picked_key[1] == 0 || d->game.picked_key[2] == 0)
		SDL_BlitSurface(d->texture.keys, 0, d->sdl.surface, &d->texture.keys_r);
	else
		d->game.access = 1; 

	if (d->game.picked_key[0] == 1)
		SDL_BlitSurface(d->texture.sprt[3].sprites[0], 0, d->sdl.surface, &pos[0]);
	if (d->game.picked_key[1] == 1)
		SDL_BlitSurface(d->texture.sprt[3].sprites[1], 0, d->sdl.surface, &pos[1]);
	if (d->game.picked_key[2] == 1)
		SDL_BlitSurface(d->texture.sprt[3].sprites[2], 0, d->sdl.surface, &pos[2]);
}