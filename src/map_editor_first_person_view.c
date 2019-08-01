/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor_first_person_view.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:01:16 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/01 14:01:17 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		check_what_line_player_are_looking(t_doom *d)
{
	int			v;
	t_sector	*sect;
	t_vertex	t1;
	t_vertex	t2;

	sect = d->map.sectors + d->player.sector;
	v = -1;
	printf("");
	while (++v < (int)sect->num_vert)
	{
		t1.x = sect->vert[v].x - d->player.coord.x;
		t1.y = sect->vert[v].y - d->player.coord.y;
		t2.x = sect->vert[v + 1].x - d->player.coord.x;
		t2.y = sect->vert[v + 1].y - d->player.coord.y;

		rotate_vertex_xy(&t1, d->player.anglesin, d->player.anglecos);
		rotate_vertex_xy(&t2, d->player.anglesin, d->player.anglecos);

		if (t1.y < 0 && t2.y < 0)
			continue;
		if (t1.x < 0 && t2.x > 0)
			return (v);
	}
	return (-1);
}
