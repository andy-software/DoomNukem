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
	d->game.ducking = 0;
	d->game.moving = 0;
	d->game.ground = 0;
	d->game.falling = 1;
	d->game.acceleration = 0.2f;
	d->player.anglecos = sinf(d->player.angle);
	d->player.anglesin = cosf(d->player.angle);
	d->render.rendered_sectors = (int*)malloc(sizeof(int) * d->map.num_sect);
	d->render.max_sector_rendered = min(MAX_SECTORS_RENDERED, d->map.num_sect);
	return (1);
}

int			game_loop(t_doom doom)
{
	init_game_params(&doom);

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
