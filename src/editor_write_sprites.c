/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_write_sprites.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanylch <mdanylch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:13:42 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/20 22:35:33 by mdanylch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	write_sprites2(t_doom *doom, int i)
{
	if (doom->map.sprites[i].num_sheet == 0)
		create_gribok(doom, i);
	if (doom->map.sprites[i].num_sheet == 1)
		create_aptechka(doom, i);
	else if (doom->map.sprites[i].num_sheet == 2)
		create_get_ammo(doom, i);
	else if (doom->map.sprites[i].num_sheet == 3)
		create_key1(doom, i);
	else if (doom->map.sprites[i].num_sheet == 7)
		create_jetpack(doom, i);
	else if (doom->map.sprites[i].num_sheet == 9)
		create_npc(doom, i);
}

void	create_small_mob(t_doom *doom, int i)
{
	doom->map.sprites[i].text_no = 0;
	doom->map.sprites[i].move_speed = 0.30;
	doom->map.sprites[i].key = 1;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 1;
	doom->map.sprites[i].event_num = 3;
	doom->map.sprites[i].hp = 20;
	doom->map.sprites[i].death_time = 0;
}

void	create_boss_mob(t_doom *doom, int i)
{
	doom->map.sprites[i].text_no = 0;
	doom->map.sprites[i].move_speed = 0.15;
	doom->map.sprites[i].key = 1;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 0;
	doom->map.sprites[i].event_num = 1;
	doom->map.sprites[i].hp = 100;
	doom->map.sprites[i].death_time = 0;
}

void	create_gribok(t_doom *doom, int i)
{
	doom->map.sprites[i].angle = 0;
	doom->map.sprites[i].anglecos = 0;
	doom->map.sprites[i].anglesin = 0;
	doom->map.sprites[i].own_moves = 0;
	doom->map.sprites[i].move_speed = 0;
	doom->map.sprites[i].live = 0;
	doom->map.sprites[i].vision_forward = 0;
	doom->map.sprites[i].vision_backward = 0;
	doom->map.sprites[i].key = 0;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 0;
	doom->map.sprites[i].event_num = 3;
	doom->map.sprites[i].hp = 0;
	doom->map.sprites[i].pick = 1;
}

void	create_aptechka(t_doom *doom, int i)
{
	doom->map.sprites[i].angle = 0;
	doom->map.sprites[i].anglecos = 0;
	doom->map.sprites[i].anglesin = 0;
	doom->map.sprites[i].own_moves = 0;
	doom->map.sprites[i].move_speed = 0;
	doom->map.sprites[i].live = 0;
	doom->map.sprites[i].vision_forward = 0;
	doom->map.sprites[i].vision_backward = 0;
	doom->map.sprites[i].key = 0;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 0;
	doom->map.sprites[i].event_num = 0;
	doom->map.sprites[i].hp = 0;
	doom->map.sprites[i].pick = 1;
}

void	create_get_ammo(t_doom *doom, int i)
{
	doom->map.sprites[i].angle = 0;
	doom->map.sprites[i].anglecos = 0;
	doom->map.sprites[i].anglesin = 0;
	doom->map.sprites[i].own_moves = 0;
	doom->map.sprites[i].move_speed = 0;
	doom->map.sprites[i].live = 0;
	doom->map.sprites[i].vision_forward = 0;
	doom->map.sprites[i].vision_backward = 0;
	doom->map.sprites[i].key = 0;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 0;
	doom->map.sprites[i].event_num = 0;
	doom->map.sprites[i].hp = 0;
	doom->map.sprites[i].pick = 1;
}

void	create_key1(t_doom *doom, int i)
{
	doom->map.sprites[i].angle = 0;
	doom->map.sprites[i].anglecos = 0;
	doom->map.sprites[i].anglesin = 0;
	doom->map.sprites[i].own_moves = 0;
	doom->map.sprites[i].move_speed = 0;
	doom->map.sprites[i].draw = 1;
	doom->map.sprites[i].live = 0;
	doom->map.sprites[i].vision_forward = 0;
	doom->map.sprites[i].vision_backward = 0;
	doom->map.sprites[i].key = 0;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 0;
	doom->map.sprites[i].event_num = 0;
	doom->map.sprites[i].hp = 0;
	doom->map.sprites[i].pick = 1;
	doom->map.sprites[i].death_time = 0;

}

// void	create_painting(t_doom *doom, int i)
void	create_jetpack(t_doom *doom, int i)
{
	doom->map.sprites[i].angle = 0;
	doom->map.sprites[i].anglecos = 0;
	doom->map.sprites[i].anglesin = 0;
	doom->map.sprites[i].own_moves = 0;
	doom->map.sprites[i].move_speed = 0;
	doom->map.sprites[i].live = 0;
	doom->map.sprites[i].vision_forward = 0;
	doom->map.sprites[i].vision_backward = 0;
	doom->map.sprites[i].key = 0;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 0;
	doom->map.sprites[i].event_num = 0;
	doom->map.sprites[i].hp = 0;
	doom->map.sprites[i].pick = 1;
	doom->map.sprites[i].death_time = 0;
}

void	create_npc(t_doom *doom, int i)
{
	doom->map.sprites[i].angle = 0;
	doom->map.sprites[i].anglecos = 0;
	doom->map.sprites[i].anglesin = 0;
	doom->map.sprites[i].own_moves = 0;
	doom->map.sprites[i].move_speed = 0;
	doom->map.sprites[i].draw = 1;
	doom->map.sprites[i].live = 0;
	doom->map.sprites[i].vision_forward = 0;
	doom->map.sprites[i].vision_backward = 0;
	doom->map.sprites[i].key = 1;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 1;
	doom->map.sprites[i].event_num = 4;
	doom->map.sprites[i].hp = 0;
	doom->map.sprites[i].pick = 0;
}


void	write_sprites(t_doom *doom)
{
	int		i;

	// t_map &map = doom->map;
	i = -1;
	while (++i < (int)doom->map.num_sprites)
	{
		if (doom->map.sprites[i].mob == 1)
		{
			if (doom->map.sprites[i].num_sheet == 5)
				create_big_mob(doom, i);
			else if (doom->map.sprites[i].num_sheet == 6)
				create_small_mob(doom, i);
			else if (doom->map.sprites[i].num_sheet == 8)
				create_boss_mob(doom, i);
		}
		else if (doom->map.sprites[i].mob == 0)
			write_sprites2(doom, i);	
	}
}
