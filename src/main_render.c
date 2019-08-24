/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:06:14 by apavlov           #+#    #+#             */
/*   Updated: 2019/04/06 13:06:15 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void		render_sector_second_part(t_render *r, t_doom *d, int i)
{
	r->mc1 = r->t1;
	rotate_vertex_xy(&r->mc1, r->psin, -r->pcos);
	r->mc2 = r->t2;
	rotate_vertex_xy(&r->mc2, r->psin, -r->pcos);
	r->mc1.x += r->p_x;
	r->mc2.x += r->p_x;
	r->mc1.y += r->p_y;
	r->mc2.y += r->p_y;
	if (r->neighbor >= 0)
	{
		r->ncplane = d->map.sectors[(int)r->neighbor].ceil_plane;
		r->nfplane = d->map.sectors[(int)r->neighbor].floor_plane;
		r->nzceil1 = get_z(r->ncplane, r->mc1.x, r->mc1.y) - r->p_z;
		r->nzfloor1 = get_z(r->nfplane, r->mc1.x, r->mc1.y) - r->p_z;
		r->nzceil2 = get_z(r->ncplane, r->mc2.x, r->mc2.y) - r->p_z;
		r->nzfloor2 = get_z(r->nfplane, r->mc2.x, r->mc2.y) - r->p_z;
		r->nz1a = WIN_HEIGHT / 2 - ((r->nzceil1 + \
								r->t1.y * r->angle_z) * r->zscale1);
		r->nz1b = WIN_HEIGHT / 2 - ((r->nzfloor1 + \
								r->t1.y * r->angle_z) * r->zscale1);
		r->nz2a = WIN_HEIGHT / 2 - ((r->nzceil2 + \
								r->t2.y * r->angle_z) * r->zscale2);
		r->nz2b = WIN_HEIGHT / 2 - ((r->nzfloor2 + \
								r->t2.y * r->angle_z) * r->zscale2);
	}
}

static void		render_sector_third_part(t_render *r, t_doom *d, int i)
{
	r->zceil1 = get_z(r->cplane, r->mc1.x, r->mc1.y) - r->p_z;
	r->zfloor1 = get_z(r->fplane, r->mc1.x, r->mc1.y) - r->p_z;
	r->zceil2 = get_z(r->cplane, r->mc2.x, r->mc2.y) - r->p_z;
	r->zfloor2 = get_z(r->fplane, r->mc2.x, r->mc2.y) - r->p_z;
	r->z1a = WIN_HEIGHT / 2 - ((r->zceil1 + \
							r->t1.y * r->angle_z) * r->zscale1);
	r->z1b = WIN_HEIGHT / 2 - ((r->zfloor1 + \
							r->t1.y * r->angle_z) * r->zscale1);
	r->z2a = WIN_HEIGHT / 2 - ((r->zceil2 + \
							r->t2.y * r->angle_z) * r->zscale2);
	r->z2b = WIN_HEIGHT / 2 - ((r->zfloor2 + \
							r->t2.y * r->angle_z) * r->zscale2);
	r->kt = (r->t2.y - r->t1.y) / (r->x2 - r->x1);
	r->kza = (r->z2a - r->z1a) / (r->x2 - r->x1);
	r->kzb = (r->z2b - r->z1b) / (r->x2 - r->x1);
	r->nkza = (r->nz2a - r->nz1a) / (r->x2 - r->x1);
	r->nkzb = (r->nz2b - r->nz1b) / (r->x2 - r->x1);
	r->len = line_len(r->sect->vert[i + 1], r->sect->vert[i]);
	r->dummy_var = (d->texture.wall_tex[r->line.wall]->w * \
									r->line.x_w_scale - 1) / r->len;
	r->w0 = line_len(r->mc1, r->sect->vert[i]) * \
									r->dummy_var + r->line.x_w_shift;
}

static void		render_sector_start_threads(t_render *r, t_doom *d)
{
	int	t;

	r->ceil_cal.random_vector = (t_vector){0, 0, \
			get_z(r->cplane, r->p_x, r->p_y) - r->p_z};
	r->ceil_cal.rotated.a = r->cplane.a * r->psin - r->cplane.b * r->pcos;
	r->ceil_cal.rotated.b = r->cplane.a * r->pcos + r->cplane.b * r->psin;
	r->ceil_cal.rotated.c = r->cplane.c;
	r->ceil_cal.rotated.h = -r->ceil_cal.random_vector.z;
	r->ceil_cal.sect = r->sect;
	r->ceil_cal.surr = r->texture->wall_tex[r->sect->ceil_tex];
	find_count_and_width_of_slice(r);
	fill_the_params(r, d->threads);
	t = -1;
	while (++t < r->count_slice)
		pthread_create(&d->threads[t].thrd, \
					NULL, start_the_work, d->threads + t);
	if (r->neighbor >= 0 && r->end_x >= r->begin_x && \
		(r->head + MAX_SECTORS_RENDERED + 1 - r->tail) % MAX_SECTORS_RENDERED)
		prepare_to_render_next_sector(r);
	t = -1;
	while (++t < r->count_slice)
		pthread_join(d->threads[t].thrd, NULL);
}

static void		render_sector_fourth_part(t_render *r, t_doom *d, int i)
{
	r->w1 = line_len(r->mc2, r->sect->vert[i]) * \
									r->dummy_var + r->line.x_w_shift;
	r->dummy_var = (d->texture.wall_tex[r->line.bot]->w * \
									r->line.x_b_scale - 1) / r->len;
	r->w0_bot = line_len(r->mc1, r->sect->vert[i]) * \
							r->dummy_var + r->line.x_b_shift;
	r->w1_bot = line_len(r->mc2, r->sect->vert[i]) * \
							r->dummy_var + r->line.x_b_shift;
	r->dummy_var = (d->texture.wall_tex[r->line.top]->w * \
							r->line.x_t_scale - 1) / r->len;
	r->w0_top = line_len(r->mc1, r->sect->vert[i]) * \
							r->dummy_var + r->line.x_t_shift;
	r->w1_top = line_len(r->mc2, r->sect->vert[i]) * \
						r->dummy_var + r->line.x_t_shift;
	r->floor_cal.random_vector = (t_vector){0, 0, \
						get_z(r->fplane, r->p_x, r->p_y) - r->p_z};
	r->floor_cal.rotated.a = r->fplane.a * r->psin - r->fplane.b * r->pcos;
	r->floor_cal.rotated.b = r->fplane.a * r->pcos + r->fplane.b * r->psin;
	r->floor_cal.rotated.c = r->fplane.c;
	r->floor_cal.rotated.h = -r->floor_cal.random_vector.z;
	r->floor_cal.sect = r->sect;
	r->floor_cal.surr = r->texture->wall_tex[r->sect->floor_tex];
}

void			render_sector(t_render *r, t_doom *d)
{
	int	i;

	++r->rendered_sectors[r->now.num];
	r->sect = d->map.sectors + r->now.num;
	r->cplane = r->sect->ceil_plane;
	r->fplane = r->sect->floor_plane;
	i = -1;
	while (++i < (int)r->sect->num_vert)
	{
		render_sector_first_part(r, i);
		if (render_sector_cliping_lines(r))
			continue ;
		r->x1 = WIN_WIDTH / 2 - (r->t1.x * r->xscale1);
		r->x2 = WIN_WIDTH / 2 - (r->t2.x * r->xscale2);
		if (r->x1 >= r->x2 || r->x2 < r->now.sx1 || r->x1 > r->now.sx2)
			continue ;
		r->neighbor = r->sect->neighbors[i];
		r->begin_x = MAX(r->x1, r->now.sx1);
		r->end_x = MIN(r->x2, r->now.sx2);
		render_sector_second_part(r, d, i);
		render_sector_third_part(r, d, i);
		render_sector_fourth_part(r, d, i);
		render_sector_start_threads(r, d);
	}
	++r->rendered_sectors[r->now.num];
}
