/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:56:30 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/14 19:01:15 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	init_hud(t_doom *d)
{
	d->texture.gun1_r.x = WIN_WIDTH / 20;
	d->texture.gun1_r.y = WIN_HEIGHT - d->texture.gun1[0]->h;

	d->texture.gun21_r.x = WIN_WIDTH - d->texture.gun2[0]->w * 1.5;
	d->texture.gun21_r.y = WIN_HEIGHT - d->texture.gun2[0]->h;

	d->texture.gun22_r.x = WIN_WIDTH - d->texture.gun2[14]->w * 2;
	d->texture.gun22_r.y = WIN_HEIGHT - d->texture.gun2[0]->h;

	d->texture.dude_r.x = WIN_WIDTH / 3;
	d->texture.dude_r.y = WIN_HEIGHT - d->texture.dude[0]->h;

	d->texture.ammo_r.x = WIN_WIDTH - WIN_WIDTH / 3.5;
	d->texture.ammo_r.y = WIN_HEIGHT - WIN_HEIGHT / 6;

	d->texture.hp_r.x = WIN_WIDTH / 4.5;
	d->texture.hp_r.y = WIN_HEIGHT / 1.2;

	d->texture.keys_r.x = WIN_WIDTH - d->texture.keys->w;
	d->texture.keys_r.y = WIN_HEIGHT / 3;
}

int		init_game_params(t_doom *d)
{
	int	i;

	d->game.quit = 0;
	d->game.dead = 0;
	d->game.pause = 0;
	d->game.story = 0;
	d->game.ducking = 0;
	d->game.moving = 0;
	d->game.ground = 0;
	d->game.falling = 1;
	d->game.flying = 0;
	d->game.blood = 0;
	d->game.rect_i = 0;
	d->game.acceleration = 0.5f;
	d->difficulty = 1;
	d->game.hp_level = 100;
	d->game.dt = 0;
	d->ui.idle = 0;
	if (!d->map.editing)
	{
		d->game.damage = 60 / d->difficulty;
		d->ui.ammo_1 = 10 * d->difficulty;
	}
	d->game.fuel = 100;
	d->game.picked_key[0] = 0;
	d->game.picked_key[1] = 0;
	d->game.picked_key[2] = 0;
	d->ui.fire = 0;
	d->ui.gun_num = 0;
	d->ui.gun_anim = 0;
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
	d->sr.time_from_loop_start = 0;
	d->sr.pos = 0;
	d->sr.prev_frame = 0;
	d->sr.map = &d->map;
	d->render.map = &d->map;
	init_hud(d);
	i = 0;
	while (i < (int)d->map.num_sect)
	{
		if (d->map.sectors[i].ceil_plane.c == 0)
			return (error_message("What the hell did you bring to this cursed lands.."));
		d->map.sectors[i].ceil_plane.a /= d->map.sectors[i].ceil_plane.c;
		d->map.sectors[i].ceil_plane.b /= d->map.sectors[i].ceil_plane.c;
		d->map.sectors[i].ceil_plane.h /= d->map.sectors[i].ceil_plane.c;
		d->map.sectors[i].ceil_plane.c = 1.0f;
		i++;
	}
	show_pause(d);
	return (1);
}

int		game_loop(t_doom doom)
{
	if (!init_game_params(&doom))
		return (0);
	init_moves(&doom);
	doom.map.editing = 0;
	set_mouse(&doom);
	while (doom.game.quit != 1)
	{
		doom.ui.prevTime = SDL_GetTicks();
		player_events(&doom);
		if (doom.game.story == 1)
			show_story(&doom);
		else if (doom.game.pause == 0 && doom.game.hp_level > 0)
		{
			game_events(&doom);
			prepare_to_rendering(&doom.render, doom);
			draw_skybox(&doom);
			draw_screen(&doom);
			draw_ui(&doom);
		}
		else if (doom.game.pause == 1)
		{
			SDL_BlitScaled(doom.texture.pause, 0, doom.sdl.surface, 0);
			pause_events(&doom);
			draw_menu(&doom);
		}
		else if (doom.game.hp_level <= 0)
		{
			set_mouse(&doom);
			show_lose(&doom);
			lose_events(&doom);
			draw_menu(&doom);
		}
		while (SDL_GetTicks() - doom.ui.prevTime < 100.0 / 6);
			doom.ui.currTime = SDL_GetTicks();
			doom.game.dt = doom.ui.currTime - doom.ui.prevTime;
			doom.ui.fps = doom.game.dt / 1000.0;
			if (doom.game.pause == 0 &&
				doom.game.hp_level > 0 && doom.start_quit == 1)
				draw_fps(&doom, (int)(1.0 / doom.ui.fps));
		SDL_UpdateWindowSurface(doom.sdl.window);
	}
	return (1);
}

void	set_mouse(t_doom *doom)
{
	if (doom->game.hp_level <= 0 ||
		doom->game.pause == 1 || doom->start_quit == 0)
	{
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_DISABLE);
		SDL_SetWindowGrab(doom->sdl.window, 0);
	}
	else if (doom->game.pause == 0 && doom->game.hp_level > 0)
	{
		SDL_SetWindowGrab(doom->sdl.window, 1);
		SDL_SetRelativeMouseMode(SDL_ENABLE);
		SDL_GetRelativeMouseState(NULL, NULL);
	}
}
