/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_point_lie.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 03:27:39 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/15 18:13:26 by myuliia          ###   ########.fr       */
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

int		vertical_lie(t_doom *doom, int i, int k)
{
	if (doom->editor.lp.more == 0 && comp_real(clamp(doom->editor.lp.point.y, min(doom->editor.lp.v2->y, doom->editor.lp.v1->y), max(doom->editor.lp.v2->y, doom->editor.lp.v1->y)), doom->editor.lp.point.y, 0.001))
	{
		line_sec_save(doom, 1, i, k);
		doom->editor.lp.more++;
		return (0);
	}
	else if (doom->editor.lp.more == 1 && comp_real(clamp(doom->editor.lp.point.y, min(doom->editor.lp.v2->y, doom->editor.lp.v1->y), max(doom->editor.lp.v2->y, doom->editor.lp.v1->y)), doom->editor.lp.point.y, 0.001))
	{
		if (doom->map.sectors[doom->editor.fline.sec1].neighbors[doom->editor.fline.num_line1] == -1)
			doom->editor.is_portal = 0;
		else
			doom->editor.is_portal = 1;
		doom->editor.fline.num_line2 = i;
		doom->editor.fline.sec2 = k;
	}
	else if (doom->editor.lp.more == 0)
		line_sec_save(doom, 2, i, k);
	return (1);
}

int		else_lie(t_doom *doom, int koef, int c, int i, int k)
{
	koef = (doom->editor.lp.v2->y - doom->editor.lp.v1->y) / (doom->editor.lp.v2->x - doom->editor.lp.v1->x);
	c = doom->editor.lp.v1->y - (koef * doom->editor.lp.v1->x);

	if (doom->editor.lp.more == 0 && comp_real(doom->editor.lp.point.y, (doom->editor.lp.point.x * koef + c), 1) &&
	(doom->editor.lp.point.x > min(doom->editor.lp.v1->x, doom->editor.lp.v2->x)) &&
	(doom->editor.lp.point.x < max(doom->editor.lp.v1->x, doom->editor.lp.v2->x)))
	{
		line_sec_save(doom, 1, i, k);
		doom->editor.lp.more++;
		return (0);
	}
	else if (doom->editor.lp.more == 1 && comp_real(doom->editor.lp.point.y, (doom->editor.lp.point.x * koef + c), 2) &&
	(doom->editor.lp.point.x > min(doom->editor.lp.v1->x, doom->editor.lp.v2->x)) &&
	(doom->editor.lp.point.x < max(doom->editor.lp.v1->x, doom->editor.lp.v2->x)))
	{
		if (doom->map.sectors[doom->editor.fline.sec1].neighbors[doom->editor.fline.num_line1] == -1)
			doom->editor.is_portal = 0;
		else
			doom->editor.is_portal = 1;
		doom->editor.fline.num_line2 = i;
		doom->editor.fline.sec2 = k;
	}
	else if (doom->editor.lp.more == 0)
		line_sec_save(doom, 2, i, k);
	return (1);
}

void	lie_point(t_doom *doom, int k, int x, int y)
{


    LIE_POINT(i, koef, c);
	k = -1;
	doom->editor.lp.more = 0;
	doom->editor.lp.point = (t_vertex){(x / SCL), (y / SCL)};
	while (++k < (int)doom->map.num_sect)
	{
		i = -1;
		while (++i < (int)doom->map.sectors[k].num_vert)
		{
		    doom->editor.lp.v2 = (i + 1) < (int)doom->map.sectors[k].num_vert ? doom->map.sectors[k].vert + i + 1 : doom->map.sectors[k].vert;
			doom->editor.lp.v1 = doom->map.sectors[k].vert + i;
			if (comp_real(doom->editor.lp.v2->x, doom->editor.lp.v1->x, 2) && comp_real(doom->editor.lp.point.x, doom->editor.lp.v1->x, 2))
			{
				if (!vertical_lie(doom, i, k))
					break;
			}
			else
			{
				// if (!else_lie(doom, koef, c, i, k))
				// 	break ;
				koef = (doom->editor.lp.v2->y - doom->editor.lp.v1->y) / (doom->editor.lp.v2->x - doom->editor.lp.v1->x);
				c = doom->editor.lp.v1->y - (koef * doom->editor.lp.v1->x);
			
				if (doom->editor.lp.more == 0 && comp_real(doom->editor.lp.point.y, (doom->editor.lp.point.x * koef + c), 1) &&
				(doom->editor.lp.point.x > min(doom->editor.lp.v1->x, doom->editor.lp.v2->x)) &&
				(doom->editor.lp.point.x < max(doom->editor.lp.v1->x, doom->editor.lp.v2->x)))
				{
				    line_sec_save(doom, 1, i, k);
                    doom->editor.lp.more++;
					break ;
				}
				else if (doom->editor.lp.more == 1 && comp_real(doom->editor.lp.point.y, (doom->editor.lp.point.x * koef + c), 2) &&
				(doom->editor.lp.point.x > min(doom->editor.lp.v1->x, doom->editor.lp.v2->x)) &&
				(doom->editor.lp.point.x < max(doom->editor.lp.v1->x, doom->editor.lp.v2->x)))
				{
					if (doom->map.sectors[doom->editor.fline.sec1].neighbors[doom->editor.fline.num_line1] == -1)
						doom->editor.is_portal = 0;
					else
						doom->editor.is_portal = 1;
					doom->editor.fline.num_line2 = i;
					doom->editor.fline.sec2 = k;
				}
				else if (doom->editor.lp.more == 0)
			        line_sec_save(doom, 2, i, k);
			}
		}
	}
}