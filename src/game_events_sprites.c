/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events_sprites.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanylch <mdanylch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 20:13:02 by mdanylch          #+#    #+#             */
/*   Updated: 2019/08/27 20:13:16 by mdanylch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static	void	sprites_event_1(t_doom *d, int i)
{
	if (d->ui.gun_num == 0)
		d->map.sprites[d->sr.sprites[i].spr_num].hp -= d->game.damage;
	else
	{
		d->map.sprites[d->sr.sprites[i].spr_num].hp -= d->game.damage / 10;
		d->game.blood = 1;
	}
}

static	void	sprites_event_2(t_doom *d, int i)
{
	if (d->map.sprites[d->sr.sprites[i].spr_num].hp <= 0)
	{
		d->map.sprites[d->sr.sprites[i].spr_num].live = 0;
		if (d->sr.sprites[i].num_sheet == 5)
			Mix_PlayChannel(4, d->sound.mobdeath[1], 0);
		else if (d->sr.sprites[i].num_sheet == 6)
			Mix_PlayChannel(4, d->sound.mobdeath[0], 0);
		else if (d->sr.sprites[i].num_sheet == 8)
			Mix_PlayChannel(4, d->sound.mobdeath[2], 0);
	}
	else
	{
		if (d->sr.sprites[i].num_sheet == 5)
			Mix_PlayChannel(4, d->sound.mobhurt[1], 0);
		else if (d->sr.sprites[i].num_sheet == 6)
			Mix_PlayChannel(4, d->sound.mobhurt[0], 0);
		else if (d->sr.sprites[i].num_sheet == 8)
			Mix_PlayChannel(4, d->sound.mobhurt[2], 0);
	}
}

void			check_sprite_intersection(t_doom *d)
{
	SPRITES_VAR(t1, t2, attack_range, i);
	while (++i < (int)d->map.num_sprites)
		if (d->sr.sprites[i].coord.y < 0)
			break ;
	if (d->ui.gun_num == 0)
		attack_range = 100;
	else if (d->ui.gun_num == 1)
		attack_range = 2;
	else
		return ;
	while (--i >= 0)
	{
		if (!d->sr.sprites[i].live)
			continue ;
		sprite_vert_cal(&t1, &t2, d->sr.sprites + i, d->player);
		if (t1.x > 0 && t2.x < 0 && d->ui.ammo_1 >= -2)
			if (t1.y < attack_range)
				if (t1.z + t1.y * d->player.angle_z > 0 && \
					t2.z + t1.y * d->player.angle_z < 0)
				{
					sprites_event_1(d, i);
					sprites_event_2(d, i);
					break ;
				}
	}
}
