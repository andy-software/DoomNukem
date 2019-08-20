/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_write_sprites2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 19:27:18 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/18 19:38:21 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

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

// map.sprites[i].spr_num = i;
// 		map.sprites[i].text_no = 0;
// 		map.sprites[i].num_sheet = 6;
// 		map.sprites[i].coord = (t_vector){10, 10, get_z(map.sectors[0].floor_plane, 10, 10)};
// 		map.sprites[i].sector_no = 0;
// 		map.sprites[i].width = 3;
// 		map.sprites[i].start_z = 6;
// 		map.sprites[i].end_z = 12;
// 		map.sprites[i].mob = 1;
// 		map.sprites[i].angle = M_PI / 4;
// 		map.sprites[i].anglecos = cos(map.sprites[i].angle);
// 		map.sprites[i].anglesin = sin(map.sprites[i].angle);
// 		map.sprites[i].own_moves = i;
// 		map.sprites[i].move_speed = 0.30;
// 		map.sprites[i].draw = 1;
// 		map.sprites[i].live = 1;
// 		map.sprites[i].vision_forward = 5; //must be positive //could be same for all sprites
// 		map.sprites[i].vision_backward = -3; //must be negative //could be same for all sprites
// 		map.sprites[i].key = 1;
// 		map.sprites[i].changes = 0;
// 		map.sprites[i].key_state = 0;
// 		map.sprites[i].num_of_sound = 0;
// 		map.sprites[i].event_num = 3;
// 		map.sprites[i].hp = 20;
// 		map.sprites[i].death_time = 0;

void	create_small_mob(t_doom *doom, int i)
{
	doom->map.sprites[i].text_no = 0;
	doom->map.sprites[i].move_speed = 0.30;
	doom->map.sprites[i].key = 1;
	doom->map.sprites[i].changes = 0;
	doom->map.sprites[i].key_state = 0;
	doom->map.sprites[i].num_of_sound = 0;
	doom->map.sprites[i].event_num = 3;
	doom->map.sprites[i].hp = 20;
	doom->map.sprites[i].death_time = 0;
	doom->map.sprites[i].own_moves = 1;
	
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
