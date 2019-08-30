/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:56:30 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/28 19:30:41 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		game_loop(t_doom *doom)
{
	if (!init_game_params(doom))
		return (0);
	init_moves(doom);
	doom->map.editing = 0;
	set_mouse(doom);
	SDL_Delay(1000);
	while (SDL_PollEvent(&doom->ev))
		(void)doom->ev;
	while (doom->game.quit != 1)
	{
		doom->ui.prev_time = SDL_GetTicks();
		player_events(doom);
		chose_mod(doom);
		doom->ui.curr_time = SDL_GetTicks();
		while (doom->ui.curr_time - doom->ui.prev_time < 100.0 / 6)
			doom->ui.curr_time = SDL_GetTicks();
		doom->game.dt = doom->ui.curr_time - doom->ui.prev_time;
		doom->ui.fps = doom->game.dt / 1000.0;
		if (doom->game.pause == 0 &&
			doom->game.hp_level > 0 && doom->start_quit == 1)
			draw_fps(doom, (int)(1.0 / doom->ui.fps));
		SDL_UpdateWindowSurface(doom->sdl.window);
	}
	return (1);
}

void	chose_mod(t_doom *doom)
{
	if (doom->game.story == 1)
		show_story(doom);
	else if (doom->game.pause == 0 && doom->game.hp_level > 0)
	{
		game_events(doom);
		prepare_to_rendering(&doom->render, *doom);
		draw_skybox(doom);
		draw_screen(doom);
		draw_ui(doom);
	}
	else if (doom->game.pause == 1)
	{
		SDL_BlitScaled(doom->texture.pause, 0, doom->sdl.surface, 0);
		pause_events(doom);
		draw_menu(doom);
	}
	else if (doom->game.hp_level <= 0)
	{
		set_mouse(doom);
		show_lose(doom);
		lose_events(doom);
		draw_menu(doom);
		free_menu(doom);
	}
}

void	set_mouse(t_doom *doom)
{
	if (doom->game.hp_level <= 0 ||
		doom->game.pause == 1 || doom->start_quit == 0)
	{
		fflush(stdout);
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
