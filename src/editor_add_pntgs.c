/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_add_pntgs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:41:25 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/22 18:05:49 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	add_paintings3(t_painting *p, SDL_Event *event, t_vertex dot_1, t_vertex dot_2)
{
	float 		width;

    width = 5;
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

void	add_paintings2(SDL_Event *event, t_vertex line_param, t_painting *p, int nb)
{
	float 		width;

    width = 5;
	if (nb == 1)
	{
		p->v1.x = event->button.x / SCL - width / (2 *
        sqrt(1 + line_param.x * line_param.x));
		p->v2.x = event->button.x / SCL + width / (2 *
        sqrt(1 + line_param.x * line_param.x));
		p->v1.y = p->v1.x * line_param.x + line_param.y;
		p->v2.y = p->v2.x * line_param.x + line_param.y;
	}
	else if (nb == 2)
	{
		p->v1.x = event->button.x / SCL + width / (2 * sqrt(1 + line_param.x * line_param.x));
		p->v2.x = event->button.x / SCL - width / (2 * sqrt(1 + line_param.x * line_param.x));
		p->v1.y = p->v1.x * line_param.x + line_param.y;
		p->v2.y = p->v2.x * line_param.x + line_param.y;
	}
}

void	add_paintings(t_doom *doom, SDL_Event *event)
{
	t_painting	*p = &doom->map.paint[IMG[3].exist - 1];
	t_vertex	line_param;
	
	t_vertex dot_1;
	t_vertex dot_2;
		
	lie_point(doom, event->button.x, event->button.y);
	if (doom->editor.fline.sec2 == -1 && doom->editor.fline.sec1 != -1)
	{
		dot_1 = doom->map.sectors[doom->editor.fline.sec1].vert[doom->editor.fline.num_line1];
		if (doom->editor.fline.num_line1 + 1 != (int)doom->map.sectors[doom->editor.fline.sec1].num_vert)
			dot_2 = doom->map.sectors[doom->editor.fline.sec1].vert[doom->editor.fline.num_line1 + 1];
		else
			dot_2 = doom->map.sectors[doom->editor.fline.sec1].vert[0];
		
		line_param = get_line_param(dot_1.x, dot_1.y, dot_2.x, dot_2.y);
		if (!comp_real(dot_1.x, dot_2.x, 0.0001))
		{
			if (dot_1.x < dot_2.x)
				add_paintings2(event, line_param, p, 1);
			else
				add_paintings2(event, line_param, p, 2);
		}
		else
			add_paintings3(p, event, dot_1, dot_2);
		doom->map.paint[IMG[3].exist - 1].sector_no = doom->editor.fline.sec1;
		doom->map.paint[IMG[3].exist - 1].num_sheet = 10;
		doom->map.num_paint = IMG[3].exist;
	}
	else
	{
		if (EXIST != 0)
			EXIST--;
		doom->editor.img_press = 1;
	}
}