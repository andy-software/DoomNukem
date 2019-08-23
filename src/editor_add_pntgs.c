/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_add_pntgs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:41:25 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/22 20:59:10 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		add_paintings3(t_doom *d, SDL_Event *ev, t_vertex d_1, t_vertex d_2)
{
	float		width;
	t_painting	*p;

	p = &d->map.paint[IMGS[3].exist - 1];
	width = 5;
	p->v1.x = ev->button.x / SCL;
	p->v2.x = ev->button.x / SCL;
	if (d_1.y < d_2.y)
	{
		p->v1.y = ev->button.y / SCL - width;
		p->v2.y = ev->button.y / SCL + width;
	}
	else
	{
		p->v1.y = ev->button.y / SCL + width;
		p->v2.y = ev->button.y / SCL - width;
	}
}

void		add_paintings2(SDL_Event *ev, t_vertex l_par, t_doom *d, int nb)
{
	float		width;
	t_painting	*p;

	p = &d->map.paint[IMGS[3].exist - 1];
	width = 5;
	if (nb == 1)
	{
		p->v1.x = ev->button.x / SCL - width / (2 *
		sqrt(1 + l_par.x * l_par.x));
		p->v2.x = ev->button.x / SCL + width / (2 *
		sqrt(1 + l_par.x * l_par.x));
		p->v1.y = p->v1.x * l_par.x + l_par.y;
		p->v2.y = p->v2.x * l_par.x + l_par.y;
	}
	else if (nb == 2)
	{
		p->v1.x = ev->button.x / SCL + width / (2 *
		sqrt(1 + l_par.x * l_par.x));
		p->v2.x = ev->button.x / SCL - width / (2 *
		sqrt(1 + l_par.x * l_par.x));
		p->v1.y = p->v1.x * l_par.x + l_par.y;
		p->v2.y = p->v2.x * l_par.x + l_par.y;
	}
}

t_vertex	find_dot_2(t_doom *doom)
{
	if (DEFLN.num_line1 + 1
	!= (int)MAPSEC[DEFLN.sec1].num_vert)
		return (MAPSEC[DEFLN.sec1].vert[DEFLN.num_line1
		+ 1]);
	else
		return (MAPSEC[DEFLN.sec1].vert[0]);
}

void		del_paint(t_doom *doom)
{
	if (EXIST != 0)
		EXIST--;
	doom->editor.img_press = 1;
}

void		add_paintings(t_doom *d, SDL_Event *ev)
{
	t_vertex	line_param;
	t_vertex	dot_1;
	t_vertex	dot_2;

	lie_point(d, ev->button.x, ev->button.y);
	if (DEFL.sec2 == -1 && DEFL.sec1 != -1)
	{
		dot_1 = d->map.sectors[DEFL.sec1].vert[DEFL.num_line1];
		dot_2 = find_dot_2(d);
		line_param = get_line_param(dot_1.x, dot_1.y, dot_2.x, dot_2.y);
		if (!comp_real(dot_1.x, dot_2.x, 0.0001))
		{
			if (dot_1.x < dot_2.x)
				add_paintings2(ev, line_param, d, 1);
			else
				add_paintings2(ev, line_param, d, 2);
		}
		else
			add_paintings3(d, ev, dot_1, dot_2);
		d->map.paint[IMGS[3].exist - 1].sector_no = DEFL.sec1;
		d->map.paint[IMGS[3].exist - 1].num_sheet = 10;
		d->map.num_paint = IMGS[3].exist;
	}
	else
		del_paint(d);
}
