/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_inits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:06:06 by mmasyush          #+#    #+#             */
/*   Updated: 2019/08/28 18:06:07 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	init_hud(t_doom *d)
{
	d->game.picked_key[0] = 0;
	d->game.picked_key[1] = 0;
	d->game.picked_key[2] = 0;
	d->ui.gun_num = 0;
	d->ui.gun_anim = 0;
	d->ui.fire = 0;
	d->texture.gun1_r.x = WIN_WIDTH - d->texture.gun1[0]->w;
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

int		init_sect(t_doom *d)
{
	int	i;

	i = 0;
	while (i < (int)d->map.num_sect)
	{
		if (d->map.sectors[i].ceil_plane.c == 0)
			return (error_message("What did you bring to this cursed lands.."));
		d->map.sectors[i].ceil_plane.a /= d->map.sectors[i].ceil_plane.c;
		d->map.sectors[i].ceil_plane.b /= d->map.sectors[i].ceil_plane.c;
		d->map.sectors[i].ceil_plane.h /= d->map.sectors[i].ceil_plane.c;
		d->map.sectors[i].ceil_plane.c = 1.0f;
		i++;
	}
	return (1);
}

void	init_else_params(t_doom *d)
{
	d->player.anglecos = sinf(d->player.angle);
	d->player.anglesin = cosf(d->player.angle);
	d->render.rendered_sectors = (int*)malloc(sizeof(int) * d->map.num_sect);
	d->render.max_sector_rendered = MIN(MAX_SECTORS_RENDERED, d->map.num_sect);
	d->sr.sprites = (t_sprite*)ft_memalloc(sizeof(t_sprite) *
		d->map.num_sprites);
	d->render.ztop = (int*)ft_memalloc(sizeof(int) * WIN_WIDTH);
	d->render.zbottom = (int*)ft_memalloc(sizeof(int) * WIN_WIDTH);
	d->render.queue = (t_rend_sector*)ft_memalloc(sizeof(t_rend_sector) *
		MAX_SECTORS_RENDERED);
	d->render.texture = &d->texture;
	d->sr.time_from_loop_start = 0;
	d->sr.pos = 0;
	d->sr.prev_frame = 0;
	d->sr.map = &d->map;
	d->render.map = &d->map;
	d->ui.idle = 0;
	d->game.speed = MOVE_SPEED;
	if (!d->map.editing)
	{
		d->game.damage = 60 / d->difficulty;
		d->ui.ammo_1 = 10 * d->difficulty;
	}
}

int		init_game_params(t_doom *d)
{
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
	d->game.dt = 0;
	d->game.rect_i = 0;
	d->game.ugroza = 0;
	d->game.acceleration = 0.5f;
	d->game.hp_level = 100;
	d->game.win = 0;
	d->game.fuel = 0;
	d->game.access = 0;
	init_hud(d);
	init_else_params(d);
	init_sect(d);
	show_pause(d);
	return (1);
}
