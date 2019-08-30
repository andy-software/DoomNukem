/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_add_items.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 06:27:18 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/30 18:57:45 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_free_items(t_doom *doom, int j)
{
	doom->map.sprites[j].spr_num = j;
	doom->map.sprites[j].coord = (t_vector){40, 40, 0};
	doom->map.sprites[j].width = 8;
	doom->map.sprites[j].end_z = 13;
	doom->map.sprites[j].mob = 0;
	doom->map.sprites[j].draw = 1;
	doom->map.sprites[j].live = 1;
	doom->map.sprites[j].angle = M_PI / 4;
	doom->map.sprites[j].anglesin = sin(doom->map.sprites[j].angle);
	doom->map.sprites[j].anglecos = cos(doom->map.sprites[j].angle);
	doom->map.sprites[j].move_speed = 0.03;
	doom->map.sprites[j].own_moves = 1;
	doom->map.sprites[j].vision_forward = 5;
	doom->map.sprites[j].vision_backward = -3;
	doom->map.sprites[j].hp = 20;
	doom->map.sprites[j].num_sheet = 0;
	doom->map.sprites[j].changes = 6;
}

void	add_del_items(t_doom *doom, SDL_Event *event)
{
	if (event->button.x > (WIN_WIDTH - 400) && (event->button.y < 100))
	{
		if ((event->button.y >= 20 && event->button.y <= 100)
		&& event->button.button == SDL_BUTTON_LEFT)
		{
			doom->editor.img_press = 1;
			doom->editor.ind_img = ((event->button.x / 100) - 7);
			EXIST++;
			if (doom->editor.ind_img == 1 && EXIST == 2)
			{
				doom->editor.img_press = 0;
				EXIST = 1;
			}
		}
		if (event->button.button == SDL_BUTTON_RIGHT)
		{
			doom->editor.ind_img = ((event->button.x / 100) - 7);
			ft_null_items(doom, doom->editor.ind_img, 0);
			ft_free_items(doom, EXIST);
			if (EXIST != 0)
				EXIST--;
		}
	}
}

// void	init_img_2(t_doom *doom, SDL_Event *event)
// {
// 	doom->map.sprites[(IMG[4].exist + EXIST) - 1].coord =
// 	(t_vector){event->button.x / SCL, event->button.y / SCL,
// 	get_z(doom->map.sectors[is_in_sector(doom, \
// 	(event->button.x), (event->button.y))].floor_plane, \
// 	event->button.x / SCL, event->button.y / SCL)};
// 	doom->map.sprites[(EXIST + IMG[4].exist) - 1].pick = 0;
// 	doom->map.sprites[(EXIST + IMG[4].exist) - 1].mob = 1;
// }

void	add_items2(t_doom *doom, SDL_Event *event)
{
	// if (doom->editor.ind_img == 2)
	// {
	// 	if (IMG[4].exist > -1)
	// 		init_img_2(doom, event);
	// }
	if (doom->editor.ind_img == 4)
	{
		doom->map.sprites[EXIST - 1].coord =
		(t_vector){event->button.x / SCL, event->button.y / SCL,
		get_z(doom->map.sectors[is_in_sector(doom, (event->button.x), \
		(event->button.y))].floor_plane, event->button.x / SCL, \
		event->button.y / SCL)};
		doom->map.sprites[EXIST - 1].pick = 1;
		doom->map.sprites[EXIST - 1].mob = 0;
		doom->map.sprites[EXIST - 1].num_sheet = 0;
	}
}

void	player_add_items(t_doom *doom, SDL_Event *event)
{
	ft_null_items(doom, doom->editor.ind_img, EXIST + 1);
	add_items2(doom, event);
	if (doom->editor.ind_img == 1)
	{
		if (IMG[1].exist == 1)
			if (doom->editor.ind_img == 1)
			{
				doom->player.coord = \
				(t_vector){event->button.x / SCL, event->button.y / SCL, \
					get_z(doom->map.sectors[is_in_sector(doom, \
					(event->button.x), (event->button.y))].floor_plane, \
					event->button.x / SCL, event->button.y / SCL) + 10};
			}
		EXIST = 1;
	}
	else if (doom->editor.ind_img == 3)
		add_paintings(doom, event);
	doom->editor.ind_img = 0;
}

void	add_items(t_doom *doom, SDL_Event *event)
{
	if (event->button.x < (WIN_WIDTH - 400))
	{
		if (doom->editor.img_press == 1
		&& event->button.button == SDL_BUTTON_LEFT)
		{
			if (doom->editor.ind_img != 0)
			{
				if (doom->editor.ind_img != 3
				&& is_in_sector(doom, event->button.x, event->button.y) == -1)
				{
					if (EXIST != 0)
						EXIST--;
					doom->editor.img_press = 1;
				}
				else
					player_add_items(doom, event);
			}
		}
		doom->editor.img_press = 0;
	}
	if (!(event->button.x > 900 && event->button.x < 999))
		add_del_items(doom, event);
}
