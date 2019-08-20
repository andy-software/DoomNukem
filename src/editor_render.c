/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 21:33:50 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/19 20:07:27 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_render_editor(t_doom *doom)
{
	ft_render_interface(doom);
	ft_render_previous(doom);
	ft_render_other(doom);
}

void	ft_render_previous2(t_doom *doom)
{
	int		it;

	it = 0;
	while (++it < NUM_VERT)
	{
		doom->editor.brezen.x1 =
		(doom->map.sectors[NUM_SECT].vert[it].x * SCL);
		doom->editor.brezen.y1 =
		doom->map.sectors[NUM_SECT].vert[it].y * SCL;
		doom->editor.brezen.x2 =
		doom->map.sectors[NUM_SECT].vert[it - 1].x * SCL;
		doom->editor.brezen.y2 =
		doom->map.sectors[NUM_SECT].vert[it - 1].y * SCL;
		doom->editor.brezen.color = 0xFFFFFF;
		ft_line(doom);
	}
	doom->editor.brezen.x1 = doom->editor.interface.tmp_x1;
	doom->editor.brezen.y1 = doom->editor.interface.tmp_y1;
	doom->editor.brezen.x2 = doom->editor.interface.tmp_x2;
	doom->editor.brezen.y2 = doom->editor.interface.tmp_y2;
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
	while (++i < (int)NUM_SECT)
	{
		it = -1;
		while (++it < (int)NUM_VERTEX)
		{
			doom->editor.brezen.x1 = doom->map.sectors[i].vert[it].x * SCL;
			doom->editor.brezen.y1 = doom->map.sectors[i].vert[it].y * SCL;
			doom->editor.brezen.x2 = doom->map.sectors[i].vert[it + 1].x * SCL;
			doom->editor.brezen.y2 = doom->map.sectors[i].vert[it + 1].y * SCL;
			doom->editor.brezen.color = 0x66ff8a;
			if (doom->map.sectors[i].neighbors[it] != -1)
				doom->editor.brezen.color = 0xFF0001;
			ft_draw_pixel(doom, doom->editor.brezen.x1, doom->editor.brezen.y1, 0xFF0000);
			ft_draw_pixel(doom, doom->editor.brezen.x1 + 1, doom->editor.brezen.y1, 0xFF0000);
			ft_draw_pixel(doom, doom->editor.brezen.x1 + 2, doom->editor.brezen.y1, 0xFF0000);
			ft_draw_pixel(doom, doom->editor.brezen.x1 + 3, doom->editor.brezen.y1, 0xFF0000);
			ft_draw_pixel(doom, doom->editor.brezen.x1 + 4, doom->editor.brezen.y1, 0xFF0000);
			ft_draw_pixel(doom, doom->editor.brezen.x1 + 5, doom->editor.brezen.y1, 0xFF0000);
			ft_line(doom);
		}
	}
	ft_render_previous2(doom);
}

void	ft_render_other2(t_doom *doom)
{
	doom->editor.brezen.x1 = doom->editor.brezen.x2;
	doom->editor.brezen.y1 = doom->editor.brezen.y2;
	doom->map.sectors[NUM_SECT].neighbors[NUM_VERT] = -1;
	doom->map.sectors[NUM_SECT].vert[NUM_VERT].x = doom->editor.brezen.x1 / SCL;
	doom->map.sectors[NUM_SECT].vert[NUM_VERT].y = doom->editor.brezen.y1 / SCL;
	NUM_VERT++;
	IS_DRW = 1;
	BUT_PRS = 0;
}

void	ft_render_other(t_doom *doom)
{
	doom->editor.brezen.color = 0xFFFFFF;
	if (IS_DRW == 0 && BUT_PRS == 1 && doom->editor.is_sector == 1)
	{
		doom->editor.brezen.x1 = doom->editor.brezen.x2;
		doom->editor.brezen.y1 = doom->editor.brezen.y2;
		if (check_on_point(doom))
		{
			ft_line(doom);
			doom->map.sectors[NUM_SECT].vert =
			(t_vertex *)malloc(sizeof(t_vertex) * MAX_VERT);
			doom->map.sectors[NUM_SECT].neighbors =
			(char *)malloc(sizeof(char) * MAX_VERT);
			doom->map.sectors[NUM_SECT].vert[0].x =
			doom->editor.brezen.x1 / SCL;
			doom->map.sectors[NUM_SECT].vert[0].y =
			doom->editor.brezen.y1 / SCL;
			doom->map.sectors[NUM_SECT].neighbors[NUM_VERT] = -1;
			NUM_VERT++;
			FT_R_OTH(doom->editor.is_sector, IS_DRW, BUT_PRS);
		}
	}
	else if (IS_DRW == 1 && BUT_PRS == 1)
		ft_render_other2(doom);
	else if (IS_DRW == 1 && BUT_PRS == 0)
		ft_line(doom);
}
