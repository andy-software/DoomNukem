/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_add_items.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 06:27:18 by myuliia           #+#    #+#             */
/*   Updated: 2019/09/02 19:55:54 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_free_items(t_doom *doom, int j)
{
	doom->map.sprites[j].spr_num = j;
	doom->map.sprites[j].text_no = 0;
	doom->map.sprites[j].num_sheet = 2;
	doom->map.sprites[j].coord = (t_vector){40, 40, 0};
	doom->map.sprites[j].width = 2;
	doom->map.sprites[j].end_z = 5;
	doom->map.sprites[j].mob = 0;
	doom->map.sprites[j].angle = 0;
	doom->map.sprites[j].anglecos = 0;
	doom->map.sprites[j].anglesin = 0;
	doom->map.sprites[j].own_moves = 0;
	doom->map.sprites[j].move_speed = 0;
	doom->map.sprites[j].draw = 1;
	doom->map.sprites[j].live = 0;
	doom->map.sprites[j].vision_forward = 0;
	doom->map.sprites[j].vision_backward = 0;
	doom->map.sprites[j].key = 0;
	doom->map.sprites[j].changes = 0;
	doom->map.sprites[j].key_state = 0;
	doom->map.sprites[j].num_of_sound = 0;
	doom->map.sprites[j].event_num = 0;
	doom->map.sprites[j].hp = 0;
	doom->map.sprites[j].death_time = 0;
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
			if (EXIST != 0)
			{	
				if (doom->editor.ind_img == 4)
					ft_free_items(doom, EXIST - 1);
				EXIST--;
			}
		}
	}
}

void	add_items2(t_doom *doom, SDL_Event *event)
{
	if (doom->editor.ind_img == 4)
	{
		doom->map.sprites[EXIST - 1].coord =
		(t_vector){event->button.x / SCL, event->button.y / SCL,
		get_z(doom->map.sectors[is_in_sector(doom, (event->button.x), \
		(event->button.y))].floor_plane, event->button.x / SCL, \
		event->button.y / SCL)};
		doom->map.sprites[EXIST - 1].pick = 0;
		doom->map.sprites[EXIST - 1].mob = 0;
		doom->map.sprites[EXIST - 1].draw = 1;
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
