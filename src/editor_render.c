/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 21:33:50 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/05 21:35:12 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	 ft_render_editor(t_doom *doom)
{
	ft_render_interface(doom);
	ft_render_previous(doom);
	ft_render_other(doom);
}

void	ft_render_previous(t_doom *doom)
{
	int		i;
	int		it;


	i = -1;
	doom->editor.interface.tmp_x1 = doom->editor.brezen.x1;
	doom->editor.interface.tmp_y1 = doom->editor.brezen.y1;
	doom->editor.interface.tmp_x2 = doom->editor.brezen.x2;
	doom->editor.interface.tmp_y2 = doom->editor.brezen.y2;
	while (++i < (int)doom->map.num_sect)
	{
		it = -1;
		while (++it < (int)NUM_VERTEX)
		{
			doom->editor.brezen.x1 = doom->map.sectors[i].vert[it].x * 10;
			doom->editor.brezen.y1 = doom->map.sectors[i].vert[it].y * 10;
			doom->editor.brezen.x2 = doom->map.sectors[i].vert[it + 1].x * 10;
			doom->editor.brezen.y2 = doom->map.sectors[i].vert[it + 1].y * 10;
			doom->editor.brezen.color = 0x66ff8a;
			if (doom->map.sectors[i].neighbors[it] != -1)
				doom->editor.brezen.color = 0xFF0001;
			ft_line(doom);
		}
	}
	it = 0;
	if (doom->editor.is_drawing == 0)
		doom->map.sectors[doom->map.num_sect].num_vert = 0;
	while (++it < NUM_VERT)
	{
		doom->editor.brezen.x1 = (doom->map.sectors[doom->map.num_sect].vert[it].x * 10);
		doom->editor.brezen.y1 = doom->map.sectors[doom->map.num_sect].vert[it].y * 10;
		doom->editor.brezen.x2 = doom->map.sectors[doom->map.num_sect].vert[it - 1].x * 10;
		doom->editor.brezen.y2 = doom->map.sectors[doom->map.num_sect].vert[it - 1].y * 10;
		doom->editor.brezen.color = 0xFFFFFF;
		ft_line(doom);
	}	
	doom->editor.brezen.x1 = doom->editor.interface.tmp_x1;
	doom->editor.brezen.y1 = doom->editor.interface.tmp_y1;
	doom->editor.brezen.x2 = doom->editor.interface.tmp_x2;
	doom->editor.brezen.y2 = doom->editor.interface.tmp_y2;	
}

void	ft_render_other(t_doom *doom) 
{
	doom->editor.brezen.color = 0xFFFFFF;
	if (doom->editor.is_drawing == 0 && doom->editor.but1_press == 1 && doom->editor.is_sector == 1)
	{
		doom->editor.brezen.x1 = doom->editor.brezen.x2;
		doom->editor.brezen.y1 = doom->editor.brezen.y2;
		if(check_on_point(doom))
		{
			ft_line(doom);
			doom->map.sectors[doom->map.num_sect].vert = (t_vertex *)malloc(sizeof(t_vertex) * MAX_VERT);
			doom->map.sectors[doom->map.num_sect].neighbors = (char *)malloc(sizeof(char) * MAX_VERT);
			doom->map.sectors[doom->map.num_sect].vert[0].x = doom->editor.brezen.x1 / 10;
			doom->map.sectors[doom->map.num_sect].vert[0].y = doom->editor.brezen.y1 / 10;
			doom->map.sectors[doom->map.num_sect].neighbors[doom->map.sectors[doom->map.num_sect].num_vert] = -1; // init neighbours

			doom->map.sectors[doom->map.num_sect].num_vert++;
			doom->editor.is_sector = 0;
			doom->editor.is_drawing = 1;
			doom->editor.but1_press = 0;
		}
	}
	else if (doom->editor.is_drawing == 1 && doom->editor.but1_press == 1)
	{
		doom->editor.brezen.x1 = doom->editor.brezen.x2;
		doom->editor.brezen.y1 = doom->editor.brezen.y2;
		doom->map.sectors[doom->map.num_sect].neighbors[doom->map.sectors[doom->map.num_sect].num_vert] = -1;  // init neighbours
		doom->map.sectors[doom->map.num_sect].vert[doom->map.sectors[doom->map.num_sect].num_vert].x = doom->editor.brezen.x1 / 10;
		doom->map.sectors[doom->map.num_sect].vert[doom->map.sectors[doom->map.num_sect].num_vert].y = doom->editor.brezen.y1 / 10;
		doom->map.sectors[doom->map.num_sect].num_vert++;

		doom->editor.is_drawing = 1;
		doom->editor.but1_press = 0;
	}
	else if (doom->editor.is_drawing == 1 && doom->editor.but1_press == 0)
		ft_line(doom);
}