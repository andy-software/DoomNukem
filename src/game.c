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

static int	init_game_params(t_game *game, t_player	*player)
{
	game->quit = 0;
	game->ducking = 0;
	game->moving = 0;
	game->ground = 0;
	game->falling = 1;
	game->acceleration = 0.2f;
	player->anglecos = sinf(player->angle);
	player->anglesin = cosf(player->angle);
	return (1);
}

int			game_loop(t_doom doom)
{
	init_game_params(&doom.game, &doom.player);
	while (doom.game.quit != 1)
	{
		game_events(&doom);
		draw_screen(doom);
		//draw_sprites();
		//draw_ui();
		//set_up_the_timing();
		player_events(&doom);
	}
	return (1);
}
