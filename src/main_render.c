/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_render->c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:06:14 by apavlov           #+#    #+#             */
/*   Updated: 2019/04/06 13:06:15 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	vertical_line(int x, int y1, int y2, t_render *r, int color)
{
	y1 = clamp(y1, 0, WIN_HEIGHT - 1) - 1;
	y2 = clamp(y2, 0, WIN_HEIGHT - 1);
	while (++y1 <= y2)
		if (color != 0)
			r->pix[y1 * WIN_WIDTH + x] = color;
}

void	prepare_to_render_next_sector(t_render *r)
{
	int	max1;
	int	max2;
	int	min1;
	int	min2;

	max1 = max((r->begin_x - r->x1) * r->kza + r->z1a, (r->begin_x - r->x1) * r->nkza + r->nz1a);
	max2 = max((r->end_x - r->x1) * r->kza + r->z1a, (r->end_x - r->x1) * r->nkza + r->nz1a);
	min1 = min((r->begin_x - r->x1) * r->kzb + r->z1b, (r->begin_x - r->x1) * r->nkzb + r->nz1b);
	min2 = min((r->end_x - r->x1) * r->kzb + r->z1b, (r->end_x - r->x1) * r->nkzb + r->nz1b);

	*r->head = (t_rend_sector) {r->neighbor, r->begin_x, r->end_x, \
		max1, max2, min1, min2};
	if(++r->head == (r->queue + MAX_SECTORS_RENDERED))
		r->head = r->queue;
}

void	prepare_to_rendering(t_render *r, t_doom d)
{
	int i;

	r->now.num = d.player.sector;
	r->sect = d.map.sectors + r->now.num; //&d.map.sectors[r->now.num];
	r->now.sx1 = 0;
	r->now.sx2 = WIN_WIDTH - 1;
	r->pcos = d.player.anglecos;
	r->psin = d.player.anglesin;
	r->pix = (Uint32*)d.sdl.surface->pixels;
	r->p_x = d.player.coord.x;
	r->p_y = d.player.coord.y;
	r->p_z = d.player.coord.z;
	r->angle_z = d.player.angle_z;
	i = -1;
	while (++i < MAX_SECTORS_RENDERED)
		r->queue[i] = (t_rend_sector){-1, 0, WIN_WIDTH - 1, 0, 0, WIN_HEIGHT - 1, WIN_HEIGHT - 1};
	r->head = r->queue;
	r->tail = r->queue;
	ft_memset(r->rendered_sectors, 0, sizeof(int) * d.map.num_sect);
	intset(r->ztop, 0, WIN_WIDTH);
	intset(r->zbottom, WIN_HEIGHT - 1, WIN_WIDTH);
	ft_bzero(r->pix, WIN_HEIGHT * WIN_WIDTH * sizeof(Uint32));
}

void	render_sector(t_render *r, t_doom *d)
{
	int	i;
	int	t;

	++r->rendered_sectors[r->now.num];
	r->sect = d->map.sectors + r->now.num; //&d.map.sectors[r->now.num];
	r->cplane = r->sect->ceil_plane;
	r->fplane = r->sect->floor_plane;
	
	i = -1;
	while (++i < (int)r->sect->num_vert) // wall
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
		
		r->t1_1_line = r->t1.y < r->t1.x * 1.455; //is dot 1 lower then line y = x * tg(55.5)
		r->t1_2_line = r->t1.y < -r->t1.x * 1.455; //is dot 1 lower then line y = -x * tg(55.5)
		r->t2_1_line = r->t2.y < r->t2.x * 1.455; //is dot 2 lower then line y = x * tg(55.5)
		r->t2_2_line = r->t2.y < -r->t2.x * 1.455; //is dot 2 lower then line y = -x * tg(55.5)
		if (r->t1.y < 0 && r->t2.y < 0)
			continue ;
		if ((r->t1_1_line && r->t2_1_line) || (r->t1_2_line && r->t2_2_line))
			continue ;
		if (r->t1_1_line || r->t1_2_line || r->t2_1_line || r->t2_2_line)
		{
			r->i1 = intersect(r->t1, r->t2, (t_vertex){0, 0}, (t_vertex){1, 1.455});	
			r->i2 = intersect(r->t1, r->t2, (t_vertex){0, 0}, (t_vertex){-1, 1.455});
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

		r->x1 = WIN_WIDTH / 2 - (r->t1.x * r->xscale1);
		r->x2 = WIN_WIDTH / 2 - (r->t2.x * r->xscale2);
		if(r->x1 >= r->x2 || r->x2 < r->now.sx1 || r->x1 > r->now.sx2)
			continue ;

		r->neighbor = r->sect->neighbors[i];
		r->begin_x = max(r->x1, r->now.sx1);
		r->end_x = min(r->x2, r->now.sx2);

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
			r->nz1a = WIN_HEIGHT / 2 - ((r->nzceil1 + r->t1.y * r->angle_z) * r->zscale1);
			r->nz1b = WIN_HEIGHT / 2 - ((r->nzfloor1 + r->t1.y * r->angle_z) * r->zscale1);
			r->nz2a = WIN_HEIGHT / 2 - ((r->nzceil2 + r->t2.y * r->angle_z) * r->zscale2);
			r->nz2b = WIN_HEIGHT / 2 - ((r->nzfloor2 + r->t2.y * r->angle_z) * r->zscale2);
		}
		
		r->zceil1  = get_z(r->cplane, r->mc1.x, r->mc1.y) - r->p_z;
		r->zfloor1 = get_z(r->fplane, r->mc1.x, r->mc1.y) - r->p_z;
		r->zceil2  = get_z(r->cplane, r->mc2.x, r->mc2.y) - r->p_z;
		r->zfloor2 = get_z(r->fplane, r->mc2.x, r->mc2.y) - r->p_z;

		r->z1a = WIN_HEIGHT / 2 - ((r->zceil1 + r->t1.y * r->angle_z) * r->zscale1);
		r->z1b = WIN_HEIGHT / 2 - ((r->zfloor1 + r->t1.y * r->angle_z) * r->zscale1);
		r->z2a = WIN_HEIGHT / 2 - ((r->zceil2 + r->t2.y * r->angle_z) * r->zscale2);
		r->z2b = WIN_HEIGHT / 2 - ((r->zfloor2 + r->t2.y  * r->angle_z) * r->zscale2);
		
		r->kt = (r->t2.y - r->t1.y) / (r->x2 - r->x1);
		r->kza = (r->z2a - r->z1a) / (r->x2 - r->x1);
		r->kzb = (r->z2b - r->z1b) / (r->x2 - r->x1);
		r->nkza = (r->nz2a - r->nz1a) / (r->x2 - r->x1);
		r->nkzb = (r->nz2b - r->nz1b) / (r->x2 - r->x1);

		r->len = line_len(r->sect->vert[i + 1], r->sect->vert[i]);

		r->dummy_var = (d->texture.wall_tex[r->line.wall]->w * r->line.x_w_scale - 1) / r->len;  //just a variable to calculate same things //used later//same for all threads
		r->w0 = line_len(r->mc1, r->sect->vert[i]) * r->dummy_var + r->line.x_w_shift;
		r->w1 = line_len(r->mc2, r->sect->vert[i]) * r->dummy_var + r->line.x_w_shift;
		
		r->dummy_var = (d->texture.wall_tex[r->line.bot]->w * r->line.x_b_scale - 1) / r->len;  //just a variable to calculate same things //used later//same for all threads
		r->w0_bot = line_len(r->mc1, r->sect->vert[i]) * r->dummy_var + r->line.x_b_shift;
		r->w1_bot = line_len(r->mc2, r->sect->vert[i]) * r->dummy_var + r->line.x_b_shift;

		r->dummy_var = (d->texture.wall_tex[r->line.top]->w * r->line.x_t_scale - 1) / r->len; //just a variable to calculate same things //used later//same for all threads
		r->w0_top = line_len(r->mc1, r->sect->vert[i]) * r->dummy_var + r->line.x_t_shift;
		r->w1_top = line_len(r->mc2, r->sect->vert[i]) * r->dummy_var + r->line.x_t_shift;

		//r->d_alpha = 1 / (r->x2 - r->x1);
		
		// r->d_dummy_var_x = -r->d_alpha / r->t1.y;
		// r->d_doomy_var_x = r->d_alpha / r->t2.y;

		//floor cal
		r->floor_cal.random_vector = (t_vector){0, 0, get_z(r->fplane, r->p_x, r->p_y) - r->p_z};
		r->floor_cal.rotated.a = r->fplane.a * r->psin - r->fplane.b * r->pcos;
		r->floor_cal.rotated.b = r->fplane.a * r->pcos + r->fplane.b * r->psin;
		r->floor_cal.rotated.c = r->fplane.c;
		r->floor_cal.rotated.h = -r->floor_cal.random_vector.z;
		r->floor_cal.sect = r->sect;
		r->floor_cal.surr = r->texture->wall_tex[r->sect->floor_tex];

		//ceil cal
		r->ceil_cal.random_vector = (t_vector){0, 0, get_z(r->cplane, r->p_x, r->p_y) - r->p_z};
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
			pthread_create(&d->threads[t].thrd, NULL, start_the_work, d->threads + t);
		if (r->neighbor >= 0 && r->end_x >= r->begin_x && (r->head + MAX_SECTORS_RENDERED + 1 - r->tail) % MAX_SECTORS_RENDERED)
			prepare_to_render_next_sector(r);
		t = -1;
		while (++t < r->count_slice)
			pthread_join(d->threads[t].thrd, NULL);
	}	
	++r->rendered_sectors[r->now.num];
}

void	reversed_textline_draw(int y1, int y2, t_render *r, t_thread *t)
{
	SDL_Surface	*surr;

	if (y2 == y1)
		return ;
	surr = r->texture->wall_tex[r->line.top];
	if (y1 > y2)
	{
		t->d_betta = -1.0 / (t->nza - t->za); 
		t->win_y = clamp(y2, r->ztop[t->win_x], r->zbottom[t->win_x]);
		t->wall_end = clamp(y1 + 1, r->ztop[t->win_x], r->zbottom[t->win_x]);
	}
	else
	{
		t->d_betta = 1.0 / (t->nza - t->za);
		t->win_y = clamp(y1, r->ztop[t->win_x], r->zbottom[t->win_x]);
		t->wall_end = clamp(y2 + 1, r->ztop[t->win_x], r->zbottom[t->win_x]);
	}
	t->betta = (t->win_y - t->za) * t->d_betta;
	t->float_y_text = (1 - t->betta) * t->u0_t + t->betta * t->u1_t;
	t->d_y_text = -t->d_betta * t->u0_t+ t->d_betta * t->u1_t;
	while (t->win_y < t->wall_end)
	{
		t->color = pix_from_text(surr, (unsigned int)t->x_text_upper % surr->w, (unsigned int)t->float_y_text % surr->h);
		cool_simple_function((t_int_vertex){t->win_x, t->win_y}, t->r, t->color, t->y);
		t->win_y++;
		t->betta += t->d_betta;
		t->float_y_text += t->d_y_text;
	}
}

void	upper_textline(int y1, int y2, t_render *r, t_thread *t)
{
	SDL_Surface	*surr;

	if (y2 == y1)
		return ;
	surr = r->texture->wall_tex[r->line.top];
	t->win_y = clamp(y1, r->ztop[t->win_x], r->zbottom[t->win_x]);
	t->wall_end = clamp(y2, r->ztop[t->win_x], r->zbottom[t->win_x]);
	t->d_betta = 1.0 / (t->nza - t->za);
	t->betta = (t->win_y - t->za) * t->d_betta;
	t->float_y_text = (1 - t->betta) * t->u0_t + t->betta * t->u1_t;
	t->d_y_text = -t->d_betta * t->u0_t+ t->d_betta * t->u1_t;
	while (t->win_y < t->wall_end)
	{
		t->color = pix_from_text(surr, (unsigned int)t->x_text_upper % surr->w, (unsigned int)t->float_y_text % surr->h);
		cool_simple_function((t_int_vertex){t->win_x, t->win_y}, t->r, t->color, t->y);
		t->win_y++;
		t->betta += t->d_betta;
		t->float_y_text += t->d_y_text;
	}
}

void	lower_textline(int y1, int y2, t_render *r, t_thread *t)
{
	SDL_Surface	*surr;

	if (y2 == y1)
		return ;
	surr = r->texture->wall_tex[r->line.bot];
	t->win_y = clamp(y1, r->ztop[t->win_x], r->zbottom[t->win_x]);
	t->wall_end = clamp(y2, r->ztop[t->win_x], r->zbottom[t->win_x]);
	t->d_betta = 1.0 / (t->zb - t->nzb);
	t->betta = (t->win_y - t->nzb) * t->d_betta;
	t->float_y_text = (1 - t->betta) * t->u0_b + t->betta * t->u1_b;
	t->d_y_text = -t->d_betta * t->u0_b + t->d_betta * t->u1_b;
	while (t->win_y < t->wall_end)
	{
		t->color = pix_from_text(surr, (unsigned int)t->x_text_lower % surr->w, (unsigned int)t->float_y_text % surr->h);
		cool_simple_function((t_int_vertex){t->win_x, t->win_y}, t->r, t->color, t->y);
		t->win_y++;
		t->betta += t->d_betta;
		t->float_y_text += t->d_y_text;
	}
}

Uint32	get_fog_color(Uint32 color, Uint32 fog_color, float y)
{
	color = y < 100 ? get_color_value_int(color, fog_color, y) : fog_color;
	return (color);
}

void	textline_draw(int y1, int y2, t_render *r, t_thread *t)
{
	SDL_Surface	*surr;

	if (y2 == y1)
		return ;
	surr = r->texture->wall_tex[r->line.wall];
	t->win_y = clamp(y1, r->ztop[t->win_x], r->zbottom[t->win_x]);
	t->wall_end = clamp(y2, r->ztop[t->win_x], r->zbottom[t->win_x]);
	t->d_betta = 1.0 / (t->zb - t->za);
	t->betta = (t->win_y - t->za) * t->d_betta;
	t->float_y_text = ((1 - t->betta) * t->u0 + t->betta * t->u1);
	
	t->d_y_text = -t->d_betta * t->u0 + t->d_betta * t->u1;
	
	while (t->win_y <= t->wall_end)
	{
		t->color = pix_from_text(surr, (unsigned int)t->x_text % surr->w, (unsigned int)t->float_y_text % surr->h);
		cool_simple_function((t_int_vertex){t->win_x, t->win_y}, t->r, t->color, t->y);
		t->win_y++;
		t->betta += t->d_betta;
		t->float_y_text += t->d_y_text;
	}
}

void	cool_simple_function(t_int_vertex v, t_render *r, Uint32 color, float y)
{
	Uint32	*pixels;

	pixels = r->pix + v.y * WIN_WIDTH + v.x;
	if (color != 0)
			color = get_color_value_int(color, 0x0, r->sect->light_lvl);
		else
			color = (r->map->inverse_colors) ? ~*pixels : *pixels;
		if (r->map->fog)
			color = get_fog_color(color, r->map->fog_color, y);
	*pixels = (r->map->inverse_colors) ? ~color : color;
}

void	draw_line_of_sprite(t_sprite_render *sr, SDL_Surface *sprtext, t_render *render)
{
	int		wall_end;
	float	y_point;
	float	dy_point;

	if (sr->zb == sr->za)
		return ;

	sr->win_y = clamp(sr->za, sr->clmp_top, sr->clmp_bot);
	wall_end = clamp(sr->zb, sr->clmp_top, sr->clmp_bot);
	dy_point = 1.0 / (sr->zb - sr->za); // derivation of y_point
	y_point = (float)(sr->win_y - (int)sr->za) * dy_point; //seg fault coz of int y
	while(sr->win_y < wall_end)
	{
		sr->y_text = y_point * (sprtext->h - 1);
		sr->color = pix_from_text(sprtext, sr->x_text, sr->y_text);
		if (sr->color != 0)
		{
			sr->color = get_color_value_int(sr->color, 0x0, sr->curr_sect->light_lvl);
			if (sr->map->fog && (int)sr->y > 20)
				sr->color = get_color_value_int(sr->color, sr->map->fog_color, (int)sr->y);
			render->pix[sr->win_y * WIN_WIDTH + (int)sr->win_x] = sr->color;
		}
		sr->win_y++;
		y_point += dy_point;
	}
}

void	render_ceil_line(int start, int end, t_render *r, t_thread *t)
{
	t_ceil_cal	cc;

	if (end > start)
		return ;
	cc = t->cc;
	cc.screen_y = clamp(start, end, WIN_HEIGHT);
	cc.x_multi = (WIN_WIDTH / 2 - t->win_x) / (HFOV);
	cc.denomi = - WIN_HEIGHT / 2 + (cc.rotated.a * (-cc.x_multi) - cc.rotated.b + r->angle_z) * VFOV;
	while (cc.screen_y > end)
	{
		cc.y = (cc.rotated.h) * VFOV / (cc.screen_y + cc.denomi);
		cc.map_x = cc.y * cc.x_multi;
		cc.dummy = cc.y * r->pcos + cc.map_x * r->psin;
		cc.doomy = cc.y * r->psin - cc.map_x * r->pcos;
		cc.map_x = cc.dummy + r->p_x;
		cc.map_y = cc.doomy + r->p_y;
		cc.x_text = (cc.map_x * cc.surr->w) * cc.sect->x_c_scale + cc.sect->x_c_shift;
		cc.y_text = (cc.map_y * cc.surr->h) * cc.sect->y_c_scale + cc.sect->y_c_shift;
		cc.color = pix_from_text(cc.surr, (unsigned)cc.x_text % cc.surr->w, (unsigned)cc.y_text % cc.surr->h);
		if (cc.color != 0)
			cc.color = get_color_value_int(cc.color, 0x0, t->r->sect->light_lvl);
		else
			cc.color = r->pix[cc.screen_y * WIN_WIDTH + t->win_x];
		if (r->map->fog)
			cc.color =  get_fog_color(cc.color, r->map->fog_color, cc.y);
		r->pix[cc.screen_y * WIN_WIDTH + t->win_x] = (r->map->inverse_colors) ? ~cc.color : cc.color;
		cc.screen_y--;
	}
}

void	render_floor_line(int start, int end, t_render *r, t_thread *t)
{
	t_floor_cal	fc;
	
	if (end < start)
		return ;
	fc = r->floor_cal;
	fc.screen_y = clamp(start, 0, end);
	fc.x_multi = (WIN_WIDTH / 2 - t->win_x) / (HFOV);
	fc.denomi = -WIN_HEIGHT / 2 + (fc.rotated.a * (-fc.x_multi) - fc.rotated.b + r->angle_z) * VFOV;
	while (fc.screen_y < end)
	{
		fc.y = (fc.rotated.h) * VFOV / (fc.screen_y + fc.denomi);
		fc.map_x = fc.y * fc.x_multi;
		fc.dummy = fc.y * r->pcos + fc.map_x * r->psin;
		fc.doomy = fc.y * r->psin - fc.map_x * r->pcos;
		fc.map_x = fc.dummy + r->p_x;
		fc.map_y = fc.doomy + r->p_y;
		fc.x_text = (fc.map_x * fc.surr->w) * fc.sect->x_f_scale + fc.sect->x_f_shift;
		fc.y_text = (fc.map_y * fc.surr->h) * fc.sect->y_f_scale + fc.sect->x_f_shift;
		fc.color = pix_from_text(fc.surr, (unsigned)fc.x_text % fc.surr->w, (unsigned)fc.y_text % fc.surr->h);
		if (fc.color != 0)
			fc.color = get_color_value_int(fc.color, 0x0, t->r->sect->light_lvl);
		else
			fc.color = r->pix[fc.screen_y * WIN_WIDTH + t->win_x];
		if (r->map->fog)
			fc.color = get_fog_color(fc.color, r->map->fog_color, fc.y);
		r->pix[fc.screen_y * WIN_WIDTH + t->win_x] = (r->map->inverse_colors) ? ~fc.color : fc.color;	
		fc.screen_y++;
	}
}

int		draw_screen(t_doom *d)
{
	*d->render.head = (t_rend_sector){d->player.sector, 0, WIN_WIDTH - 1, 0, 0, WIN_HEIGHT - 1, WIN_HEIGHT - 1};
	
	d->sr.begin = d->render.head;
	if (++d->render.head == d->render.queue + MAX_SECTORS_RENDERED)
	 	d->render.head = d->render.queue;

	while (d->render.head != d->render.tail)
	{
		d->render.now = *d->render.tail;
		if (++d->render.tail == (d->render.queue + MAX_SECTORS_RENDERED))
			d->render.tail = d->render.queue;
		if (d->render.rendered_sectors[d->render.now.num] & (MAX_SECTORS_RENDERED + 1))
			continue ;
		render_sector(&d->render, d);
	}
	render_painting(d);
	render_sprites(d);
	return (0);
}
