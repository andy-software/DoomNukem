/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_write_sprites2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 19:27:18 by myuliia           #+#    #+#             */
/*   Updated: 2019/09/01 12:44:43 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	create_big_mob(t_doom *doom, int i)
{	
	doom->map.sprites[i].spr_num = i;
	doom->map.sprites[i].text_no = 0;
	doom->map.sprites[i].mob = 1;
	doom->map.sprites[i].angle = M_PI / 4;
	doom->map.sprites[i].anglecos = cos(doom->map.sprites[i].angle);
	doom->map.sprites[i].anglesin = sin(doom->map.sprites[i].angle);
	doom->map.sprites[i].own_moves = 1;
	doom->map.sprites[i].move_speed = 0.15;
	doom->map.sprites[i].draw = 1;
	doom->map.sprites[i].live = 1;
	doom->map.sprites[i].vision_forward = 7;
	doom->map.sprites[i].vision_backward = -5;
	doom->map.sprites[i].key = 1;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 0;
	doom->map.sprites[i].event_num = 1;
	doom->map.sprites[i].hp = 60;
	doom->map.sprites[i].death_time = 0;
}

void	create_small_mob(t_doom *doom, int i)
{
	doom->map.sprites[i].spr_num = i;
	doom->map.sprites[i].text_no = 0;
	doom->map.sprites[i].mob = 1;
	doom->map.sprites[i].angle = M_PI / 4;
	doom->map.sprites[i].anglecos = cos(doom->map.sprites[i].angle);
	doom->map.sprites[i].anglesin = sin(doom->map.sprites[i].angle);
	doom->map.sprites[i].own_moves = 0;
	doom->map.sprites[i].move_speed = 0.25;
	doom->map.sprites[i].draw = 1;
	doom->map.sprites[i].live = 1;
	doom->map.sprites[i].vision_forward = 5;
	doom->map.sprites[i].vision_backward = -3;
	doom->map.sprites[i].key = 1;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 1;
	doom->map.sprites[i].event_num = 1;
	doom->map.sprites[i].hp = 60;
	doom->map.sprites[i].death_time = 0;
}

void	create_boss_mob(t_doom *doom, int i)
{
	doom->map.sprites[i].spr_num = i;
	doom->map.sprites[i].text_no = 0;
	doom->map.sprites[i].mob = 1;
	doom->map.sprites[i].angle = M_PI / 4;
	doom->map.sprites[i].anglecos = cos(doom->map.sprites[i].angle);
	doom->map.sprites[i].anglesin = sin(doom->map.sprites[i].angle);
	doom->map.sprites[i].own_moves = 1;
	doom->map.sprites[i].move_speed = 0.10;
	doom->map.sprites[i].draw = 1;
	doom->map.sprites[i].live = 1;
	doom->map.sprites[i].vision_forward = 10;
	doom->map.sprites[i].vision_backward = -7;
	doom->map.sprites[i].key = 1;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 2;
	doom->map.sprites[i].event_num = 1;
	doom->map.sprites[i].hp = 300;
	doom->map.sprites[i].death_time = 0;
}

void	create_gribok(t_doom *doom, int i)
{
	doom->map.sprites[i].spr_num = i;
	doom->map.sprites[i].text_no = 0;
	doom->map.sprites[i].mob = 0;
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
	doom->map.sprites[i].event_num = 2;
	doom->map.sprites[i].hp = 0;
	doom->map.sprites[i].pick = 0;
}

void	create_pickup(t_doom *doom, int i)
{
	doom->map.sprites[i].spr_num = i;
	doom->map.sprites[i].text_no = 0;
	doom->map.sprites[i].mob = 0;
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
}
