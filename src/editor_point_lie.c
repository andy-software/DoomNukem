/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_point_lie.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 03:27:39 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/24 18:40:32 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static	void	line_sec_save(t_doom *doom, int nb)
{
	if (nb == 1)
	{
		ft_putstr("\033[1;32m Line coincides\033[0m\n");
		DEDI.fline.num_line1 = DEDI.i;
		DEDI.fline.num_line2 = -1;
		DEDI.fline.sec1 = DEDI.k;
		DEDI.fline.sec2 = -1;
		DEDI.is_portal = 2;
	}
	else
	{
		DEDI.fline.num_line1 = -1;
		DEDI.fline.num_line2 = -1;
		DEDI.fline.sec1 = -1;
		DEDI.fline.sec2 = -1;
		DEDI.is_portal = 2;
	}
}

static	int		point_on_y(t_doom *doom)
{
	if (DEDI.more == 0 && \
		comp_real(CLAMP(DEDI.point.y, MIN(DEDI.v2->y, DEDI.v1->y), \
		MAX(DEDI.v2->y, DEDI.v1->y)), DEDI.point.y, 0.001))
	{
		line_sec_save(doom, 1);
		DEDI.more++;
		return (0);
	}
	else if (DEDI.more == 1 && \
		comp_real(CLAMP(DEDI.point.y, MIN(DEDI.v2->y, DEDI.v1->y), \
		MAX(DEDI.v2->y, DEDI.v1->y)), DEDI.point.y, 0.001))
	{
		if (MAPSEC[DEDI.fline.sec1].neighbors[DEDI.fline.num_line1] == -1)
			DEDI.is_portal = 0;
		else
			DEDI.is_portal = 1;
		DEDI.fline.num_line2 = DEDI.i;
		DEDI.fline.sec2 = DEDI.k;
	}
	else if (DEDI.more == 0)
		line_sec_save(doom, 2);
	return (1);
}

static	int		point_true(t_doom *doom, int point_true)
{
	if (point_true == 1)
	{
		return (DEDI.more == 0 && \
	comp_real(DEDI.point.y, (DEDI.point.x * DEDI.koef + DEDI.c), 1) && \
	(DEDI.point.x > MIN(DEDI.v1->x, DEDI.v2->x)) && \
	(DEDI.point.x < MAX(DEDI.v1->x, DEDI.v2->x)));
	}
	else
	{
		return (DEDI.more == 1 && \
	comp_real(DEDI.point.y, (DEDI.point.x * DEDI.koef + DEDI.c), 2) &&
	(DEDI.point.x > MIN(DEDI.v1->x, DEDI.v2->x)) &&
	(DEDI.point.x < MAX(DEDI.v1->x, DEDI.v2->x)));
	}
}

static	int		point_on_line(t_doom *doom)
{
	DEDI.koef = (DEDI.v2->y - DEDI.v1->y) / (DEDI.v2->x - DEDI.v1->x);
	DEDI.c = DEDI.v1->y - (DEDI.koef * DEDI.v1->x);
	if (point_true(doom, 1))
	{
		line_sec_save(doom, 1);
		DEDI.more++;
		return (0);
	}
	else if (point_true(doom, 0))
	{
		if (MAPSEC[DEDI.fline.sec1].neighbors[DEDI.fline.num_line1] == -1)
			DEDI.is_portal = 0;
		else
			DEDI.is_portal = 1;
		DEDI.fline.num_line2 = DEDI.i;
		DEDI.fline.sec2 = DEDI.k;
	}
	else if (DEDI.more == 0)
		line_sec_save(doom, 2);
	return (1);
}

void			lie_point(t_doom *doom, int x, int y)
{
	DEDI.k = -1;
	DEDI.more = 0;
	DEDI.point = (t_vertex){(x / SCL), (y / SCL)};
	while (++DEDI.k < (int)doom->map.num_sect)
	{
		DEDI.i = -1;
		while (++DEDI.i < (int)MAPSEC[DEDI.k].num_vert)
		{
			DEDI.v2 = (DEDI.i + 1) < (int)MAPSEC[DEDI.k].num_vert ? \
			MAPSEC[DEDI.k].vert + DEDI.i + 1 : MAPSEC[DEDI.k].vert;
			DEDI.v1 = MAPSEC[DEDI.k].vert + DEDI.i;
			if (comp_real(DEDI.v2->x, DEDI.v1->x, 2) && \
				comp_real(DEDI.point.x, DEDI.v1->x, 2))
			{
				if (point_on_y(doom) == 0)
					break ;
			}
			else
			{
				if (point_on_line(doom) == 0)
					break ;
			}
		}
	}
}
