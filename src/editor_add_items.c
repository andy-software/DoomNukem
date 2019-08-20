/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_add_items.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 06:27:18 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/18 17:37:13 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	add_paintings(t_doom *doom, SDL_Event *event)
{
	lie_point(doom, -1, event->button.x, event->button.y);
	if (doom->editor.fline.sec2 == -1 && doom->editor.fline.sec1 != -1)
	{
		t_painting	*p = &doom->map.paint[IMG[3].exist - 1];
		t_vertex	line_param;
		const float 		width = 5;
		
		t_vertex dot_1 = doom->map.sectors[doom->editor.fline.sec1].vert[doom->editor.fline.num_line1];
		t_vertex dot_2;
		if (doom->editor.fline.num_line1 + 1 != (int)doom->map.sectors[doom->editor.fline.sec1].num_vert)
			dot_2 = doom->map.sectors[doom->editor.fline.sec1].vert[doom->editor.fline.num_line1 + 1];
		else
			dot_2 = doom->map.sectors[doom->editor.fline.sec1].vert[0];
		
		line_param = get_line_param(dot_1.x, dot_1.y, dot_2.x, dot_2.y);
		if (!comp_real(dot_1.x, dot_2.x, 0.0001))
		{
			if (dot_1.x < dot_2.x)
			{
				p->v1.x = event->button.x / SCL - width / (2 * sqrt(1 + line_param.x * line_param.x));
				p->v2.x = event->button.x / SCL + width / (2 * sqrt(1 + line_param.x * line_param.x));
				p->v1.y = p->v1.x * line_param.x + line_param.y;
				p->v2.y = p->v2.x * line_param.x + line_param.y;
			}
			else
			{
				p->v1.x = event->button.x / SCL + width / (2 * sqrt(1 + line_param.x * line_param.x));
				p->v2.x = event->button.x / SCL - width / (2 * sqrt(1 + line_param.x * line_param.x));
				p->v1.y = p->v1.x * line_param.x + line_param.y;
				p->v2.y = p->v2.x * line_param.x + line_param.y;
			}
		}
		else
		{
			p->v1.x = event->button.x / SCL;
			p->v2.x = event->button.x / SCL;
			if (dot_1.y < dot_2.y)
			{
				p->v1.y = event->button.y / SCL - width;
				p->v2.y = event->button.y / SCL + width;
			}
			else
			{
				p->v1.y = event->button.y / SCL + width;
				p->v2.y = event->button.y / SCL - width;
			}
		}
		doom->map.paint[IMG[3].exist - 1].sector_no = doom->editor.fline.sec1;
		doom->map.num_paint = IMG[3].exist;
	}
	else
	{
		if (EXIST != 0)
			EXIST--;
		doom->editor.img_press = 1;
	}
}

void	add_del_items(t_doom *doom, SDL_Event *event)
{
	if (event->button.x > (WIN_WIDTH - 400))
	{
		if ((event->button.y >= 20 && event->button.y <= 100) && event->button.button == SDL_BUTTON_LEFT)
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
				EXIST--;
		}
	}
}

void	add_items2(t_doom *doom, SDL_Event *event)
{
	if (doom->editor.ind_img == 2)
	{
		if (IMG[4].exist > -1)
		{
			doom->map.sprites[(EXIST + IMG[4].exist) - 1].coord =
			(t_vector){event->button.x / SCL, event->button.y / SCL, 10};
			doom->map.sprites[(EXIST + IMG[4].exist) - 1].pick = 0;
			doom->map.sprites[(EXIST + IMG[4].exist) - 1].mob = 1;
		}
	}
	else if (doom->editor.ind_img == 4)
	{
		if (IMG[2].exist > -1)
		{
			doom->map.sprites[(IMG[2].exist + EXIST) - 1].coord =
			(t_vector){event->button.x / SCL, event->button.y / SCL, 10};
			doom->map.sprites[(IMG[2].exist + EXIST) - 1].pick = 1;
			doom->map.sprites[(IMG[2].exist + EXIST) - 1].mob = 0;
			doom->map.sprites[(IMG[2].exist + EXIST) - 1].num_sheet = 0;
		}
	}
}

void	add_items(t_doom *doom, SDL_Event *event)
{
	if (event->button.x < (WIN_WIDTH - 400))
	{
		if (doom->editor.img_press == 1 && event->button.button == SDL_BUTTON_LEFT)
		{
			if (doom->editor.ind_img != 0)
			{
				if (doom->editor.ind_img != 3 && is_in_sector(doom, event->button.x, event->button.y) == -1)
				{
						if (EXIST != 0)
							EXIST--;
							doom->editor.img_press = 1;
				}
				else
				{
					ft_null_items(doom, doom->editor.ind_img, EXIST + 1);
					add_items2(doom, event);
					if (doom->editor.ind_img == 1)
					{
						if (IMG[1].exist == 1)
							if (doom->editor.ind_img == 1)
							{
								doom->player.coord.x = event->button.x / SCL;
								doom->player.coord.y = event->button.y / SCL;
							}
						EXIST = 1;
					}
					else if (doom->editor.ind_img == 3)
						add_paintings(doom, event);	
					doom->editor.ind_img = 0;
				}
			}
		}
			doom->editor.img_press = 0;
	}
	add_del_items(doom, event);	
}
