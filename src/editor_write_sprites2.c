/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_write_sprites2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 19:27:18 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/22 19:41:08 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	create_big_mob(t_doom *doom, int i)
{
	doom->map.sprites[i].spr_num = i;
	doom->map.sprites[i].text_no = 0;
	doom->map.sprites[i].move_speed = 0.17;
	doom->map.sprites[i].key = 1;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 1;
	doom->map.sprites[i].event_num = 1;
	doom->map.sprites[i].hp = 60;
	doom->map.sprites[i].vision_forward = 10;
	doom->map.sprites[i].vision_backward = -7;
	doom->map.sprites[i].death_time = 0;
	doom->map.sprites[i].own_moves = 0;
}

void	create_small_mob(t_doom *doom, int i)
{
	doom->map.sprites[i].spr_num = i;
	doom->map.sprites[i].text_no = 0;
	doom->map.sprites[i].move_speed = 0.25;
	doom->map.sprites[i].live = 1;
	doom->map.sprites[i].mob = 1;
	doom->map.sprites[i].key = 1;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 0;
	doom->map.sprites[i].vision_forward = 17;
	doom->map.sprites[i].vision_backward = -8;
	doom->map.sprites[i].event_num = 1;
	doom->map.sprites[i].hp = 20;
	doom->map.sprites[i].death_time = 0;
	doom->map.sprites[i].own_moves = 1;
}

void	create_boss_mob(t_doom *doom, int i)
{
	doom->map.sprites[i].spr_num = i;
	doom->map.sprites[i].text_no = 0;
	doom->map.sprites[i].move_speed = 0.25;
	doom->map.sprites[i].live = 1;
	doom->map.sprites[i].mob = 1;
	doom->map.sprites[i].key = 1;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 0;
	doom->map.sprites[i].vision_forward = 17;
	doom->map.sprites[i].vision_backward = -8;
	doom->map.sprites[i].event_num = 1;
	doom->map.sprites[i].hp = 20;
	doom->map.sprites[i].death_time = 0;
	doom->map.sprites[i].own_moves = 1;
}

void	create_gribok(t_doom *doom, int i)
{
	doom->map.sprites[i].spr_num = i;
	doom->map.sprites[i].angle = 0;
	doom->map.sprites[i].width = 1;
	doom->map.sprites[i].anglecos = 0;
	doom->map.sprites[i].anglesin = 0;
	doom->map.sprites[i].own_moves = 0;
	doom->map.sprites[i].move_speed = 0;
	doom->map.sprites[i].live = 0;
	doom->map.sprites[i].vision_forward = 0;
	doom->map.sprites[i].vision_backward = 0;
	doom->map.sprites[i].key = 1;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 0;
	doom->map.sprites[i].event_num = 2;
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
