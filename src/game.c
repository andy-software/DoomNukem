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

static int	init_game_params(t_doom *d)
{
	d->game.quit = 0;
	d->game.pause = 0;
	d->game.ducking = 0;
	d->game.moving = 0;
	d->game.ground = 0;
	d->game.falling = 1;
	d->game.acceleration = 0.2f;
	d->texture.x_split = 4;
	d->texture.y_split = 2;
	d->render.fog_distance = 200;
	d->player.anglecos = sinf(d->player.angle);
	d->player.anglesin = cosf(d->player.angle);
	d->render.rendered_sectors = (int*)malloc(sizeof(int) * d->map.num_sect);
	d->render.max_sector_rendered = min(MAX_SECTORS_RENDERED, d->map.num_sect);
	return (1);
}

int			game_loop(t_doom doom)
{
	init_game_params(&doom);
	// SDL_DisplayMode DM;
	while (doom.game.quit != 1)
	{
		player_events(&doom);
		// SDL_GetCurrentDisplayMode(0, &DM);
		if (doom.game.pause == 0)
		{
			game_events(&doom);
			prepare_to_rendering(&doom.render, doom);
			draw_skybox(&doom.render, doom);
			draw_screen(doom);
			display_core(doom.sdl.render, doom.sdl.texture, doom.sdl.surface);
			SDL_ShowCursor(SDL_DISABLE);
			SDL_SetWindowGrab(doom.sdl.window, 1);
			SDL_SetRelativeMouseMode(1);
			//draw_sprites();
			//draw_ui();
			//set_up_the_timing();
		}
		else
		{
			SDL_ShowCursor(SDL_ENABLE);
			SDL_SetRelativeMouseMode(SDL_DISABLE);
			SDL_SetWindowGrab(doom.sdl.window, 0);
			display_core(doom.sdl.render, doom.sdl.texture, doom.texture.pause);
		}
	}
	return (1);
}

void		display_core(SDL_Renderer *render, SDL_Texture *texture, SDL_Surface *surface)
{
	SDL_RenderClear(render);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_RenderCopy(render, texture, NULL, NULL);
	SDL_RenderPresent(render);
}
