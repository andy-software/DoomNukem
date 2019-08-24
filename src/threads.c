/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:40:34 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/23 16:46:49 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	prerender_function_1(t_thread *t, t_render *r)
{
	float	alpha2;

	t->mc = find_x_from_screen_coords(t->win_x, r->t1, r->t2, r);
	if (comp_real(r->mc2.x, r->mc1.x, 0.01))
		t->alpha = (t->mc.y - r->mc1.y) / (r->mc2.y - r->mc1.y);
	else
		t->alpha = (t->mc.x - r->mc1.x) / (r->mc2.x - r->mc1.x);
	alpha2 = (t->win_x - (int)r->x1) / (r->x2 - r->x1);
	t->dummy_var_x = (1 - alpha2) / r->t1.y;
	t->doomy_var_x = alpha2 / r->t2.y;
	t->zceil = r->zceil1 + r->p_z + t->alpha * (r->zceil2 - r->zceil1);
	t->zfloor = r->zfloor1 + r->p_z + t->alpha * (r->zfloor2 - r->zfloor1);
	if (r->neighbor >= 0)
	{
		t->nzceil = r->nzceil1 + r->p_z + t->alpha * (r->nzceil2 - r->nzceil1);
		t->nzfloor = r->nzfloor1 + r->p_z + \
			t->alpha * (r->nzfloor2 - r->nzfloor1);
	}
	t->doomy_y = (r->texture->wall_tex[r->line.wall]->h \
		* r->line.y_w_scale - 1) / 100.f;
	t->u0 = t->doomy_y * t->zceil + r->line.y_w_shift;
	t->u1 = t->doomy_y * t->zfloor + r->line.y_w_shift;
}

static void	prerender_function_2(t_thread *t, t_render *r)
{
	t->doomy_y = (r->texture->wall_tex[r->line.bot]->h \
		* r->line.y_b_scale - 1) / 100.f;
	t->u0_b = t->doomy_y * t->nzfloor + r->line.y_b_shift;
	t->u1_b = t->doomy_y * t->zfloor + r->line.y_b_shift;
	t->doomy_y = (r->texture->wall_tex[r->line.top]->h \
		* r->line.y_t_scale - 1) / 100.f;
	t->u0_t = t->doomy_y * t->zceil + r->line.y_t_shift;
	t->u1_t = t->doomy_y * t->nzceil + r->line.y_t_shift;
	t->x_text = (t->dummy_var_x * r->w0 + t->doomy_var_x \
		* r->w1) / (t->dummy_var_x + t->doomy_var_x);
	t->x_text %= r->texture->wall_tex[r->line.wall]->w;
	t->x_text_lower = (t->dummy_var_x * r->w0_bot + t->doomy_var_x \
		* r->w1_bot) / (t->dummy_var_x + t->doomy_var_x);
	t->x_text_lower %= r->texture->wall_tex[r->line.bot]->w;
	t->x_text_upper = (t->dummy_var_x * r->w0_top + t->doomy_var_x \
		* r->w1_top) / (t->dummy_var_x + t->doomy_var_x);
	t->x_text_upper %= r->texture->wall_tex[r->line.top]->w;
	t->y = (t->win_x - r->x1) * r->kt + r->t1.y;
	t->za = (t->win_x - r->x1) * r->kza + r->z1a;
	t->zb = (t->win_x - r->x1) * r->kzb + r->z1b;
	t->c_za = CLAMP(t->za, r->ztop[t->win_x], r->zbottom[t->win_x]);
	t->c_zb = CLAMP(t->zb, r->ztop[t->win_x], r->zbottom[t->win_x]);
}

static void	render_function(t_thread *t, t_render *r)
{
	render_floor_line(t->c_zb, r->zbottom[t->win_x], r, t);
	if (r->sect->render_ceil)
		render_ceil_line(t->c_za, MIN(t->c_zb, r->ztop[t->win_x]), r, t);
	if (r->neighbor >= 0)
	{
		t->nza = (t->win_x - r->x1) * r->nkza + r->nz1a;
		t->c_nza = CLAMP(t->nza, r->ztop[t->win_x], r->zbottom[t->win_x]);
		t->nzb = (t->win_x - r->x1) * r->nkzb + r->nz1b;
		t->c_nzb = CLAMP(t->nzb, r->ztop[t->win_x], r->zbottom[t->win_x]);
		t->c_nza = MIN(t->c_nza, MIN(t->c_zb, t->c_nzb));
		t->c_nzb = MAX(t->c_nzb, MAX(t->c_za, t->c_nza));
		if (!r->sect->render_ceil)
			reversed_textline_draw(t->c_za, t->c_nza, r, t);
		else
			upper_textline(t->c_za, t->c_nza + 1, r, t);
		r->ztop[t->win_x] = CLAMP(MAX(t->c_za, t->c_nza), \
								r->ztop[t->win_x], WIN_HEIGHT - 1);
		lower_textline(t->c_nzb, t->c_zb, r, t);
		r->zbottom[t->win_x] = CLAMP(MIN(t->c_zb, t->c_nzb), \
										0, r->zbottom[t->win_x]);
	}
	else
		textline_draw(t->c_za, t->c_zb, r, t);
}

void		*start_the_work(void *data)
{
	t_thread	*t;
	t_render	*r;

	t = (t_thread*)data;
	r = t->r;
	t->win_x = (int)t->begin_x;
	while (t->win_x < (int)t->end_x)
	{
		prerender_function_1(t, r);
		prerender_function_2(t, r);
		render_function(t, r);
		t->win_x++;
	}
	return (0);
}
