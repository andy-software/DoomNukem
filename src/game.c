/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:56:30 by apavlov           #+#    #+#             */
/*   Updated: 2019/03/23 17:56:31 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void     init_hud(t_doom *d)
{
	d->texture.gun1_r.x = WIN_WIDTH / 2;
	d->texture.gun1_r.y = WIN_HEIGHT - d->texture.gun1[0]->h;

    d->texture.gun21_r.x = WIN_WIDTH - d->texture.gun2[0]->w * 1.5;
	d->texture.gun21_r.y = WIN_HEIGHT - d->texture.gun2[0]->h;

    d->texture.gun22_r.x =  WIN_WIDTH - d->texture.gun2[14]->w * 2;
	d->texture.gun22_r.y = WIN_HEIGHT - d->texture.gun2[0]->h;
    
    d->texture.dude_r.x =  WIN_WIDTH / 3;
	d->texture.dude_r.y = WIN_HEIGHT - d->texture.dude[0]->h;

    d->texture.ammo_r.x = WIN_WIDTH - WIN_WIDTH / 3.5;
	d->texture.ammo_r.y = WIN_HEIGHT - WIN_HEIGHT / 6;

	d->texture.hp_r.x = WIN_WIDTH / 4.5;
	d->texture.hp_r.y = WIN_HEIGHT / 1.2;
}

static int	init_game_params(t_doom *d)
{
	d->game.quit = 0;
	d->game.pause = 0;
	d->game.ducking = 0;
	d->game.moving = 0;
	d->game.ground = 0;
	d->game.falling = 1;
	d->game.flying = 0;
	d->game.acceleration = 0.2f;
	d->game.hp_level = 100;
	d->game.dt = 0;
    d->ui.ammo_1 = 10;
	d->player.anglecos = sinf(d->player.angle);
	d->player.anglesin = cosf(d->player.angle);
	d->render.rendered_sectors = (int*)malloc(sizeof(int) * d->map.num_sect);
	d->render.max_sector_rendered = min(MAX_SECTORS_RENDERED, d->map.num_sect);
	d->sr.sprites = (t_sprite*)ft_memalloc(sizeof(t_sprite) * d->map.num_sprites);
	d->render.ztop = (int*)ft_memalloc(sizeof(int) * WIN_WIDTH);
	d->render.zbottom = (int*)ft_memalloc(sizeof(int) * WIN_WIDTH);
	d->render.queue = (t_rend_sector*)ft_memalloc(sizeof(t_rend_sector) * MAX_SECTORS_RENDERED);
	d->game.dt = 0;
	d->render.texture = &d->texture;
	init_hud(d);
	int	i;

	i = 0;
	while (i < d->map.num_sect)
	{
		if (d->map.sectors[i].ceil_plane.c == 0)
			return (error_message("What the hell did you bring to this cursed lands.."));
		d->map.sectors[i].ceil_plane.a /= d->map.sectors[i].ceil_plane.c;
		d->map.sectors[i].ceil_plane.b /= d->map.sectors[i].ceil_plane.c;
		d->map.sectors[i].ceil_plane.h /= d->map.sectors[i].ceil_plane.c;
		d->map.sectors[i].ceil_plane.c = 1.0f;
		i++;
	}
	return (1);
}

void	*fun(void*a)
{
	return (0);
}

int			game_loop(t_doom doom)
{
	// changes(&doom);
	if (!init_game_params(&doom))
		return (0);
	init_moves(&doom);
	while (doom.game.quit != 1)
	{
		doom.ui.prevTime = SDL_GetTicks();
		player_events(&doom);
		if (doom.game.pause == 0 && doom.game.hp_level > 0)
		{
			game_events(&doom);
			prepare_to_rendering(&doom.render, doom);
			draw_skybox(doom);
			draw_screen(doom);
			draw_ui(&doom);
		}
		else if (doom.game.pause == 1)
		{
			SDL_BlitScaled(doom.texture.pause, 0, doom.sdl.surface, 0);
		}
		else
		{
			doom.ui.message = TTF_RenderText_Solid(doom.texture.fonts[HP_FONT].text_font, "U LOOOOSe BOiiiiii", doom.texture.fonts[HP_FONT].text_color);
			SDL_BlitSurface(doom.ui.message, NULL, doom.sdl.surface, NULL);
			SDL_FreeSurface(doom.ui.message);
		}
		while (SDL_GetTicks() - doom.ui.prevTime < 100.0 / 6); // lock fps to 100
		doom.ui.currTime = SDL_GetTicks();
		doom.game.dt = doom.ui.currTime - doom.ui.prevTime;
		doom.ui.fps = doom.game.dt / 1000.0;
		
		draw_fps(&doom, (int)(1.0 / doom.ui.fps));
		SDL_UpdateWindowSurface(doom.sdl.window);
	}
	return (1);
}
