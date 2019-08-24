/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_render_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 20:07:35 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/23 20:07:36 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		render_sector_first_part(t_render *r, int i)
{
	r->line = r->sect->lines[i];
	r->t1.x = r->sect->vert[i].x - r->p_x;
	r->t1.y = r->sect->vert[i].y - r->p_y;
	r->t2.x = r->sect->vert[i + 1].x - r->p_x;
	r->t2.y = r->sect->vert[i + 1].y - r->p_y;
	rotate_vertex_xy(&r->t1, r->psin, r->pcos);
	rotate_vertex_xy(&r->t2, r->psin, r->pcos);
	r->v1.x = r->t1.x;
	r->v1.y = r->t1.y;
	r->v2.x = r->t2.x;
	r->v2.y = r->t2.y;
	r->t1_1_line = r->t1.y < r->t1.x * 1.455;
	r->t1_2_line = r->t1.y < -r->t1.x * 1.455;
	r->t2_1_line = r->t2.y < r->t2.x * 1.455;
	r->t2_2_line = r->t2.y < -r->t2.x * 1.455;
}

int			render_sector_cliping_lines(t_render *r)
{
	if (r->t1.y < 0 && r->t2.y < 0)
		return (1);
	if ((r->t1_1_line && r->t2_1_line) || (r->t1_2_line && r->t2_2_line))
		return (1);
	if (r->t1_1_line || r->t1_2_line || r->t2_1_line || r->t2_2_line)
	{
		r->i1 = intersect(r->t1, r->t2, (t_vertex){0, 0}, \
												(t_vertex){1, 1.455});
		r->i2 = intersect(r->t1, r->t2, (t_vertex){0, 0}, \
												(t_vertex){-1, 1.455});
		if (r->t1_1_line && r->i1.y >= 0)
			r->t1 = r->i1;
		if (r->t1_2_line && r->i2.y >= 0)
			r->t1 = r->i2;
		if (r->t2_1_line && r->i1.y >= 0)
			r->t2 = r->i1;
		if (r->t2_2_line && r->i2.y >= 0)
			r->t2 = r->i2;
	}
	r->xscale1 = HFOV / r->t1.y;
	r->xscale2 = HFOV / r->t2.y;
	r->zscale1 = VFOV / r->t1.y;
	r->zscale2 = VFOV / r->t2.y;
	return (0);
}

static void	fill_params_for_reversed_textline(int y1, \
							int y2, t_render *r, t_thread *t)
{
	if (y1 > y2)
	{
		t->d_betta = -1.0 / (t->nza - t->za);
		t->win_y = CLAMP(y2, r->ztop[t->win_x], r->zbottom[t->win_x]);
		t->wall_end = CLAMP(y1 + 1, r->ztop[t->win_x], r->zbottom[t->win_x]);
	}
	else
	{
		t->d_betta = 1.0 / (t->nza - t->za);
		t->win_y = CLAMP(y1, r->ztop[t->win_x], r->zbottom[t->win_x]);
		t->wall_end = CLAMP(y2 + 1, r->ztop[t->win_x], r->zbottom[t->win_x]);
	}
}

void		reversed_textline_draw(int y1, int y2, t_render *r, t_thread *t)
{
	SDL_Surface	*surr;

	if (y2 == y1)
		return ;
	fill_params_for_reversed_textline(y1, y2, r, t);
	surr = r->texture->wall_tex[r->line.top];
	t->betta = (t->win_y - t->za) * t->d_betta;
	t->float_y_text = (1 - t->betta) * t->u0_t + t->betta * t->u1_t;
	t->d_y_text = -t->d_betta * t->u0_t + t->d_betta * t->u1_t;
	while (t->win_y < t->wall_end)
	{
		t->color = pix_from_text(surr, (unsigned int)t->x_text_upper \
			% surr->w, (unsigned int)t->float_y_text % surr->h);
		cool_simple_function((t_int_vertex){t->win_x, t->win_y}, \
			t->r, t->color, t->y);
		t->win_y++;
		t->betta += t->d_betta;
		t->float_y_text += t->d_y_text;
	}
}

Uint32		get_fog_color(Uint32 color, Uint32 fog_color, float y)
{
	color = y < 100 ? get_color_value_int(color, fog_color, y) : fog_color;
	return (color);
}
