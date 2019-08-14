/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_point_lie.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 03:27:39 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/14 15:16:23 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	line_sec_save(t_doom *doom, int nb, int i, int k)
{
    if (nb == 1)
    {
        ft_putstr("\033[1;32m Line coincides\033[0m\n");
        doom->editor.fline.num_line1 = i;
        doom->editor.fline.num_line2 = -1;
        doom->editor.fline.sec1 = k;
        doom->editor.fline.sec2 = -1;
        doom->editor.is_portal = 2;
    }
    else
    {
        doom->editor.fline.num_line1 = -1;
        doom->editor.fline.num_line2 = -1;
        doom->editor.fline.sec1 = -1;
        doom->editor.fline.sec2 = -1;
        doom->editor.is_portal = 2;     
    }
}

void	lie_point(t_doom *doom, int k, int x, int y)
{
	t_vertex	*v1;
	t_vertex	*v2;

    LIE_POINT(point, i, koef, c);
	k = -1;
	doom->editor.more = 0;
	point = (t_vertex){(x / SCL), (y / SCL)};
	while (++k < (int)doom->map.num_sect)
	{
		i = -1;
		while (++i < (int)doom->map.sectors[k].num_vert)
		{
		    v2 = (i + 1) < (int)doom->map.sectors[k].num_vert ? doom->map.sectors[k].vert + i + 1 : doom->map.sectors[k].vert;
			v1 = doom->map.sectors[k].vert + i;

			if (comp_real(v2->x, v1->x, 2) && comp_real(point.x, v1->x, 2))
			{
				if (doom->editor.more == 0 && comp_real(clamp(point.y, min(v2->y, v1->y), max(v2->y, v1->y)), point.y, 0.001))
				{
                    line_sec_save(doom, 1, i, k);
                    doom->editor.more++;
					break ;
				}
				else if (doom->editor.more == 1 && comp_real(clamp(point.y, min(v2->y, v1->y), max(v2->y, v1->y)), point.y, 0.001))
				{
					if (doom->map.sectors[doom->editor.fline.sec1].neighbors[doom->editor.fline.num_line1] == -1)
						doom->editor.is_portal = 0;
					else
						doom->editor.is_portal = 1;
					doom->editor.fline.num_line2 = i;
					doom->editor.fline.sec2 = k;
				}
				else if (doom->editor.more == 0)
			        line_sec_save(doom, 2, i, k);
			}
			else
			{
				koef = (v2->y - v1->y) / (v2->x - v1->x);
				c = v1->y - (koef * v1->x);
			
				if (doom->editor.more == 0 && comp_real(point.y, (point.x * koef + c), 1) &&
				(point.x > min(v1->x, v2->x)) &&
				(point.x < max(v1->x, v2->x)))
				{
				    line_sec_save(doom, 1, i, k);
                    doom->editor.more++;
					break ;
				}
				else if (doom->editor.more == 1 && comp_real(point.y, (point.x * koef + c), 2) &&
				(point.x > min(v1->x, v2->x)) &&
				(point.x < max(v1->x, v2->x)))
				{
					if (doom->map.sectors[doom->editor.fline.sec1].neighbors[doom->editor.fline.num_line1] == -1)
						doom->editor.is_portal = 0;
					else
						doom->editor.is_portal = 1;
					doom->editor.fline.num_line2 = i;
					doom->editor.fline.sec2 = k;
				}
				else if (doom->editor.more == 0)
			        line_sec_save(doom, 2, i, k);
			}
		}
	}
}