/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_write_sprites.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:13:42 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/14 16:43:17 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

/**
		doom->map.sprites[j].spr_num = j;       
		doom->map.sprites[j].coord = (t_vector){40, 40, 0};
		doom->map.sprites[j].width = 8;
		doom->map.sprites[j].end_z = 13;
		doom->map.sprites[j].mob = 1;
		doom->map.sprites[j].draw = 1;
		doom->map.sprites[j].live = 1;
		doom->map.sprites[j].angle = M_PI / 4;
		doom->map.sprites[j].anglesin = sin(doom->map.sprites[j].angle);
		doom->map.sprites[j].anglecos = cos(doom->map.sprites[j].angle);
		doom->map.sprites[j].move_speed = 0.03;
		doom->map.sprites[j].own_moves = 1;
		doom->map.sprites[j].vision_forward = 5;
		doom->map.sprites[j].vision_backward = -3;
		doom->map.sprites[j].hp = 20;  // FIX
		// doom->map.sprites[j].speed = 20;
		doom->map.sprites[j].num_sheet = 6;
**/
void	create_big_mob(t_doom *doom, int i)
{
	doom->map.sprites[i].text_no = 0;
	doom->map.sprites[i].move_speed = 0.15;
	doom->map.sprites[i].key = 1;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 1;
	doom->map.sprites[i].event_num = 1;
	doom->map.sprites[i].hp = 60;
	doom->map.sprites[i].death_time = 0;
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
		{
			if (doom->map.sprites[i].num_sheet == 0)
				create_gribok(doom, i);
			if (doom->map.sprites[i].num_sheet == 1)
				create_aptechka(doom, i);
			else if (doom->map.sprites[i].num_sheet == 2)
				create_get_ammo(doom, i);
			else if (doom->map.sprites[i].num_sheet == 3)
				create_key1(doom, i);
			// else if (doom->map.sprites[i].num_sheet == 4)
				// create_painting(doom, i);
			else if (doom->map.sprites[i].num_sheet == 7)
				create_jetpack(doom, i);
			else if (doom->map.sprites[i].num_sheet == 9)
				create_npc(doom, i);
		}
	}
}
