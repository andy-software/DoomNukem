/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:40:34 by apavlov           #+#    #+#             */
/*   Updated: 2019/07/16 14:40:35 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		find_count_and_width_of_slice(t_render *r)
{
	int		count_slice;
	int		len;

	len = r->end_x - r->begin_x;
	count_slice = 0;
	while (len >= count_slice * MIN_SLICE_WIDTH && \
								count_slice < MAX_THREADS_IN_RENDER)
		count_slice++;	
	r->width_slice = (float)len / count_slice;
	r->count_slice = count_slice;
	return (1);
}

int		fill_the_params(t_render *r, t_thread *t)
{
	int		i;

	i = 0;
	while (i < r->count_slice)
	{
		t[i].id = i;
		t[i].begin_x = i * r->width_slice + r->begin_x;
		t[i].end_x = (i + 1) * r->width_slice + r->begin_x; 
		t[i].alpha = (t[i].begin_x - r->x1) * r->d_alpha;
		t[i].dummy_var_x = (1 - t[i].alpha) / r->t1.y;
		t[i].doomy_var_x = t[i].alpha / r->t2.y;
		// if (r->neighbor >= 0)
		// {
		// 	t[i].nzceil = r->nzceil1 + t[i].alpha * (r->nzceil2 - r->nzceil1);
		// 	t[i].nzfloor = r->nzfloor1 + t[i].alpha * (r->nzfloor2 - r->nzfloor1);
		// }
		// t[i].zceil = r->zceil1 + t[i].alpha * (r->zceil2 - r->zceil1);
		// t[i].zfloor = r->zfloor1 + t[i].alpha * (r->zfloor2 - r->zfloor1);
		t[i].cc = r->ceil_cal;
		t[i].fc = r->floor_cal;
		t[i].r = r;
		i++;
	}
	t[r->count_slice - 1].end_x = r->end_x;//some shit 
	return (1);
}

void	*start_the_work(void *data)
{
	t_thread	*t;
	t_render	*r;

	t = (t_thread*)data;
	r = t->r;
	t->win_x = (int)t->begin_x;
	
	//printf("t->i %i ---- t->win_x %i\n", t->id, t->win_x);

	while (t->win_x < (int)t->end_x) // in wall 
	{
		t->zceil = r->zceil1 + r->p_z + t->alpha * (r->zceil2 - r->zceil1);
		t->zfloor = r->zfloor1 + r->p_z + t->alpha * (r->zfloor2 - r->zfloor1);
		if (r->neighbor >= 0)
		{
			t->nzceil = r->nzceil1 + t->alpha * (r->nzceil2 - r->nzceil1);
			t->nzfloor = r->nzfloor1 + t->alpha * (r->nzfloor2 - r->nzfloor1);
		}

		t->doomy_y = (r->texture->wall_tex[r->line.wall]->h * r->line.y_w_scale - 1) / 20.f;

		t->u0 = t->doomy_y * t->zceil + r->line.y_w_shift;
		t->u1 = t->doomy_y * t->zfloor + r->line.y_w_shift;

		t->x_text = (t->dummy_var_x * r->w0 + t->doomy_var_x * r->w1) / (t->dummy_var_x + t->doomy_var_x);
		t->x_text %= r->texture->wall_tex[r->line.wall]->w;
		
		t->x_text_lower = (t->dummy_var_x * r->w0_bot + t->doomy_var_x * r->w1_bot) / (t->dummy_var_x + t->doomy_var_x);
		t->x_text_lower %= r->texture->wall_tex[r->line.bot]->w;
		t->x_text_upper = (t->dummy_var_x * r->w0_top + t->doomy_var_x * r->w1_top) / (t->dummy_var_x + t->doomy_var_x);
		t->x_text_upper %= r->texture->wall_tex[r->line.top]->w;

		t->y = (t->win_x - r->x1) * r->kt + r->t1.y;
		t->za = (t->win_x - r->x1) * r->kza + r->z1a;
		t->zb = (t->win_x - r->x1) * r->kzb + r->z1b;

		t->c_za = clamp(t->za, r->ztop[t->win_x], r->zbottom[t->win_x]);
		t->c_zb = clamp(t->zb, r->ztop[t->win_x], r->zbottom[t->win_x]);

		render_floor_line(t->c_zb, r->zbottom[t->win_x], r, t);

		if (r->sect->render_ceil)
		{
			if (r->ztop[t->win_x] > t->c_zb)
				render_ceil_line(t->c_za, t->c_zb, r, t);
			else
				render_ceil_line(t->c_za, r->ztop[t->win_x], r, t);
		}

		if(r->neighbor >= 0)
		{
			t->nza = (t->win_x - r->x1) * r->nkza + r->nz1a;
			t->c_nza = clamp(t->nza, r->ztop[t->win_x], r->zbottom[t->win_x]);
			t->nzb = (t->win_x - r->x1) * r->nkzb + r->nz1b;
			t->c_nzb = clamp(t->nzb, r->ztop[t->win_x], r->zbottom[t->win_x]);

			t->c_nza = min(t->c_nza, min(t->c_zb, t->c_nzb));
			t->c_nzb = max(t->c_nzb, max(t->c_za, t->c_nza));
			if (!r->sect->render_ceil)
				reversed_textline_draw(t->c_za, t->c_nza, r, t);
			else
			{
				//printf("neight %i %i %i %i\n", t->nzb, t->nza, r->zbottom[t->win_x], r->ztop[t->win_x]);
				//printf("curr %i %i %i %i\n", t->zb, t->za, r->zbottom[t->win_x], r->ztop[t->win_x]);
				upper_textline(t->c_za, t->c_nza, r, t);
			}
			r->ztop[t->win_x] = clamp(max(t->c_za, t->c_nza), r->ztop[t->win_x], WIN_HEIGHT - 1);
			lower_textline(t->nzb, t->zb, r, t);
			r->zbottom[t->win_x] = clamp(min(t->c_zb, t->c_nzb), 0, r->zbottom[t->win_x]);
		}
		else
			textline_draw(t->c_za, t->c_zb, r, t);
		t->alpha += r->d_alpha;
		t->doomy_var_x += r->d_doomy_var_x;
		t->dummy_var_x += r->d_dummy_var_x;
		t->win_x++;
	}
	return (0);
}
