/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 21:33:50 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/22 20:13:11 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_render_previous2(t_doom *doom)
{
	int		it;

	it = 0;
	while (++it < NUM_VERT)
	{
		DBRZ.x1 =
		(doom->map.sectors[NUM_SECT].vert[it].x * SCL);
		DBRZ.y1 =
		doom->map.sectors[NUM_SECT].vert[it].y * SCL;
		DBRZ.x2 =
		doom->map.sectors[NUM_SECT].vert[it - 1].x * SCL;
		DBRZ.y2 =
		doom->map.sectors[NUM_SECT].vert[it - 1].y * SCL;
		DBRZ.color = 0xFFFFFF;
		ft_line(doom);
	}
	DBRZ.x1 = doom->editor.interface.tmp_x1;
	DBRZ.y1 = doom->editor.interface.tmp_y1;
	DBRZ.x2 = doom->editor.interface.tmp_x2;
	DBRZ.y2 = doom->editor.interface.tmp_y2;
}

void	ft_render_pr_lines(t_doom *doom, int it, int i)
{
	while (++it < (int)NUM_VERTEX)
	{
		DBRZ.x1 = doom->map.sectors[i].vert[it].x * SCL;
		DBRZ.y1 = doom->map.sectors[i].vert[it].y * SCL;
		DBRZ.x2 = doom->map.sectors[i].vert[it + 1].x * SCL;
		DBRZ.y2 = doom->map.sectors[i].vert[it + 1].y * SCL;
		DBRZ.color = 0x66ff8a;
		if (doom->map.sectors[i].neighbors[it] != -1)
			DBRZ.color = 0xFF0001;
		ft_draw_pixel(doom, DBRZ.x1, DBRZ.y1, 0xFF0000);
		ft_draw_pixel(doom, DBRZ.x1 + 1, DBRZ.y1, 0xFF0000);
		ft_draw_pixel(doom, DBRZ.x1 + 2, DBRZ.y1, 0xFF0000);
		ft_draw_pixel(doom, DBRZ.x1 + 3, DBRZ.y1, 0xFF0000);
		ft_draw_pixel(doom, DBRZ.x1 + 4, DBRZ.y1, 0xFF0000);
		ft_draw_pixel(doom, DBRZ.x1 + 5, DBRZ.y1, 0xFF0000);
		ft_line(doom);
	}
}

void	ft_render_previous(t_doom *doom)
{
	int		i;

	i = -1;
	doom->editor.interface.tmp_x1 = DBRZ.x1;
	doom->editor.interface.tmp_y1 = DBRZ.y1;
	doom->editor.interface.tmp_x2 = DBRZ.x2;
	doom->editor.interface.tmp_y2 = DBRZ.y2;
	while (++i < (int)NUM_SECT)
		ft_render_pr_lines(doom, -1, i);
	ft_render_previous2(doom);
}

void	ft_render_other2(t_doom *doom)
{
	DBRZ.x1 = DBRZ.x2;
	DBRZ.y1 = DBRZ.y2;
	doom->map.sectors[NUM_SECT].neighbors[NUM_VERT] = -1;
	doom->map.sectors[NUM_SECT].vert[NUM_VERT].x = DBRZ.x1 / SCL;
	doom->map.sectors[NUM_SECT].vert[NUM_VERT].y = DBRZ.y1 / SCL;
	NUM_VERT++;
	IS_DRW = 1;
	BUT_PRS = 0;
}

void	ft_render_other(t_doom *doom)
{
	DBRZ.color = 0xFFFFFF;
	if (IS_DRW == 0 && BUT_PRS == 1 && doom->editor.is_sector == 1)
	{
		DBRZ.x1 = DBRZ.x2;
		DBRZ.y1 = DBRZ.y2;
		if (check_on_point(doom))
		{
			ft_line(doom);
			doom->map.sectors[NUM_SECT].vert =
			(t_vertex *)malloc(sizeof(t_vertex) * MAX_VERT);
			doom->map.sectors[NUM_SECT].neighbors =
			(char *)malloc(sizeof(char) * MAX_VERT);
			doom->map.sectors[NUM_SECT].vert[0].x =
			DBRZ.x1 / SCL;
			doom->map.sectors[NUM_SECT].vert[0].y =
			DBRZ.y1 / SCL;
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
