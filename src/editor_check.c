/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 18:06:35 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/08 19:39:56 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			check_on_point(t_doom *doom)
{
	int			i;
	int			j;

	if (doom->map.num_sect > 0)
	{
		j = -1;
		while (++j < (int)doom->map.num_sect)
		{
			i = -1;
			while (++i < (int)doom->map.sectors[j].num_vert)
			{
				if ((doom->editor.brezen.x1 / 10) ==
				doom->map.sectors[j].vert[i].x &&
				(doom->editor.brezen.y1 / 10) == doom->map.sectors[j].vert[i].y)
					return (1);
			}
		}
		doom->editor.but1_press = 0;
		return (0);
	}
	return (1);
}

t_vertex	*convex2(t_doom *doom)
{
	int			i;
	t_vertex	*polig;

	i = -1;
	polig = (t_vertex *)malloc(sizeof(t_vertex) *
		(doom->map.sectors[doom->map.num_sect].num_vert * MAX_VERT));
	while (++i < NUM_VERT)
	{
		polig[i].x = doom->map.sectors[doom->map.num_sect].vert[i + 1].x
			- doom->map.sectors[doom->map.num_sect].vert[i].x;
		polig[i].y = doom->map.sectors[doom->map.num_sect].vert[i + 1].y
			- doom->map.sectors[doom->map.num_sect].vert[i].y;
		if (i == (NUM_VERT - 1))
		{
			polig[i].x = doom->map.sectors[doom->map.num_sect].vert[0].x
				- doom->map.sectors[doom->map.num_sect].vert[i].x;
			polig[i].y = doom->map.sectors[doom->map.num_sect].vert[0].y
				- doom->map.sectors[doom->map.num_sect].vert[i].y;
		}
	}
	return (polig);
}

int			convex(t_doom *doom, int j)
{
	double		product;
	t_vertex	ab;
	t_vertex	bc;
	t_vertex	*polig;

	polig = convex2(doom);
	while (++j < NUM_VERT)
	{
		ab = polig[j];
		bc = ((j + 1) == NUM_VERT) ? polig[0] : polig[j + 1];
		product = ab.x * bc.y - bc.x * ab.y;
		if (product < 0 && (doom->editor.is_sector = 2))
		{
			printf("%i %f\n", j, product);
			ft_putstr("\033[1;31m SECTOR ISN'T CONVEX\033[0m\n");
			return (0);
		}
	}
	ft_putstr("\033[1;33m SECTOR IS CONVEX\033[0m\n");
	doom->editor.is_sector = 1;
	return (1);
}

int			is_in_sector(t_doom *doom, int x, int y)
{
	int			i;
	int			sec;
	double		product;
	t_vertex	vert;
	t_vertex	vert2;
	t_vertex	point;

	if (x < WIN_WIDTH - 400 && (sec = -1))
	{
		point = (t_vertex){(x / 10), (y / 10)};
		while (++sec < (int)doom->map.num_sect)
		{		
			i = -1;
			while (++i < (int)doom->map.sectors[sec].num_vert)	
			{
				vert = (t_vertex){(doom->map.sectors[sec].vert[i].x - point.x), (doom->map.sectors[sec].vert[i].y - point.y)};
				vert2 = (i == (int)doom->map.sectors[sec].num_vert - 1) ? (t_vertex){(doom->map.sectors[sec].vert[0].x - point.x), (doom->map.sectors[sec].vert[0].y - point.y)}
					: (t_vertex){(doom->map.sectors[sec].vert[i + 1].x - point.x), (doom->map.sectors[sec].vert[i + 1].y - point.y)};
				product = vert.x * vert2.y - vert2.x * vert.y;
				if (product < 0 && (i = -1))
				{
					sec++;
					if (sec == (int)doom->map.num_sect)
					{
						ft_putstr("\033[1;31m POINT NOT IN THE SECTOR\033[0m\n");
						return (-1);
					}
				}
				if (i == (int)doom->map.sectors[sec].num_vert - 1)
				{
					ft_put_text("\033[1;32m POINT IN THE SECTOR:  ", sec, "\033[0m\n");
					return (sec);
				}
			}
		}
	}
	return (-1);
}
