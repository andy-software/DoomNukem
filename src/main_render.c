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
		else
			r->pix[y1 * WIN_WIDTH + x] = ~r->pix[y1 * WIN_WIDTH + x];
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
	while (++i < r->sect->num_vert) // wall
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
			r->nz1a = WIN_HEIGHT / 2 - (int)((r->nzceil1 + r->t1.y * r->angle_z) * r->zscale1);
			r->nz1b = WIN_HEIGHT / 2 - (int)((r->nzfloor1 + r->t1.y * r->angle_z) * r->zscale1);
			r->nz2a = WIN_HEIGHT / 2 - (int)((r->nzceil2 + r->t2.y * r->angle_z) * r->zscale2);
			r->nz2b = WIN_HEIGHT / 2 - (int)((r->nzfloor2 + r->t2.y * r->angle_z) * r->zscale2);
		}
		
		r->zceil1  = get_z(r->cplane, r->mc1.x, r->mc1.y) - r->p_z;
		r->zfloor1 = get_z(r->fplane, r->mc1.x, r->mc1.y) - r->p_z;
		r->zceil2  = get_z(r->cplane, r->mc2.x, r->mc2.y) - r->p_z;
		r->zfloor2 = get_z(r->fplane, r->mc2.x, r->mc2.y) - r->p_z;

		r->z1a = WIN_HEIGHT / 2 - (int)((r->zceil1 + r->t1.y * r->angle_z) * r->zscale1);
		r->z1b = WIN_HEIGHT / 2 - (int)((r->zfloor1 + r->t1.y * r->angle_z) * r->zscale1);
		r->z2a  = WIN_HEIGHT / 2 - (int)((r->zceil2 + r->t2.y * r->angle_z) * r->zscale2);
		r->z2b = WIN_HEIGHT / 2 - (int)((r->zfloor2 + r->t2.y  * r->angle_z) * r->zscale2);
		
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

		r->d_alpha = 1 / (r->x2 - r->x1);
		
		r->d_dummy_var_x = -r->d_alpha / r->t1.y;
		r->d_doomy_var_x = r->d_alpha / r->t2.y;

		//floor cal//same for all threads
		r->floor_cal.random_vector = (t_vector){0, 0, get_z(r->fplane, r->p_x, r->p_y) - r->p_z};
		r->floor_cal.rotated.a = r->fplane.a * r->psin - r->fplane.b * r->pcos;
		r->floor_cal.rotated.b = r->fplane.a * r->pcos + r->fplane.b * r->psin;
		r->floor_cal.rotated.c = r->fplane.c;
		r->floor_cal.rotated.h = -r->floor_cal.random_vector.z;
		r->floor_cal.sect = r->sect;
		r->floor_cal.surr = r->texture->wall_tex[r->sect->floor_tex];

		//ceil cal//same for all threads
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

	t->win_y = clamp(y2, 0, WIN_HEIGHT - 1);//kostill
	t->wall_end = clamp(y1 + 1, 0, WIN_HEIGHT - 1);
	
	t->d_betta = -1.0 / (t->zb - t->za); 
	t->betta = (float)(t->win_y - t->za) * t->d_betta; //kostill//not like this
	
	t->float_y_text = t->betta * (surr->h - 1); //add some scaler
	t->d_y_text = surr->h * t->d_betta;  //add some scaler
	while(t->win_y < t->wall_end)
	{
		t->color = pix_from_text(surr, t->x_text_upper, (int)t->float_y_text % surr->h);
		if (t->color != 0)
			r->pix[t->win_y * WIN_WIDTH + t->win_x] = get_color_value_int(t->color, 0x0, t->r->sect->light_lvl);
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

	t->win_y = clamp(y1, 0, WIN_HEIGHT - 1);
	t->wall_end = clamp(y2, 0, WIN_HEIGHT - 1);
	
	t->d_betta = 1.0 / (t->zb - t->za);
	t->betta = (float)(t->win_y - t->za) * t->d_betta; //not like this
	
	t->float_y_text = t->betta * (surr->h - 1); //add some scaler
	t->d_y_text = surr->h * t->d_betta; //add some scaler
	while(t->win_y < t->wall_end)
	{
		t->color = pix_from_text(surr, t->x_text_upper, (unsigned)t->float_y_text % surr->h);
		if (t->color != 0)
			r->pix[t->win_y * WIN_WIDTH + t->win_x] = get_color_value_int(t->color, 0x0, t->r->sect->light_lvl);
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

	t->win_y = clamp(y1, 0, WIN_HEIGHT - 1);
	t->wall_end = clamp(y2, 0, WIN_HEIGHT - 1);
	
	t->d_betta = 1.0 / (t->zb - t->za);
	t->betta = (float)(t->win_y - t->za) * t->d_betta; //not like this
	
	t->float_y_text = t->betta * (surr->h - 1); //add some scaler
	t->d_y_text = surr->h * t->d_betta; //add some scaler
	while(t->win_y < t->wall_end)
	{
		t->color = pix_from_text(surr, t->x_text_lower, (unsigned)t->float_y_text % surr->h);
		if (t->color != 0)
			r->pix[t->win_y * WIN_WIDTH + t->win_x] = get_color_value_int(t->color, 0x0, t->r->sect->light_lvl);
		t->win_y++;
		t->betta += t->d_betta;
		t->float_y_text += t->d_y_text;
	}
}

void	textline_draw(int y1, int y2, t_render *r, t_thread *t)
{
	SDL_Surface	*surr;

	if (y2 == y1)
		return ;
	// printf("%i\n",  t->r->sect->light_lvl);
	// fflush(stdout);
	surr = r->texture->wall_tex[r->line.wall];

	t->win_y = clamp(y1, 0, WIN_HEIGHT - 1);
	t->wall_end = clamp(y2, 0, WIN_HEIGHT - 1);
	
	t->d_betta = 1.0 / (t->zb - t->za);
	t->betta = (float)(t->win_y - t->za) * t->d_betta; //not like this
	
	t->float_y_text = t->betta * (surr->h - 1); //add some scaler
	t->d_y_text = surr->h * t->d_betta; //add some scaler

	while(t->win_y < t->wall_end)
	{
		t->color = pix_from_text(surr, t->x_text, (unsigned)t->float_y_text % surr->h);
		if (t->color != 0)
			r->pix[t->win_y * WIN_WIDTH + t->win_x] = get_color_value_int(t->color, 0x0, t->r->sect->light_lvl);
		t->win_y++;
		t->betta += t->d_betta;
		t->float_y_text += t->d_y_text;
	}
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
	y_point = (double)(sr->win_y - sr->za) * dy_point;
	while(sr->win_y < wall_end)
	{
		sr->y_text = y_point * sprtext->h;
		sr->color = pix_from_text(sprtext, sr->x_text, sr->y_text);
		if (sr->color != 0)
			render->pix[sr->win_y * WIN_WIDTH + sr->win_x] = sr->color;
		sr->win_y++;
		y_point += dy_point;
	}
}

void	render_painting(t_doom *d)
{
	t_sprite_render sr;

	sr = d->sr;
	sr.paint = d->map.paint;
	sr.c_paint = d->map.num_paint;
	sr.i = -1;

	while (++sr.i < sr.c_paint)
	{
		sr.surr = d->texture.sprites->next->sprites[sr.paint[sr.i].text_no]; //omg
		sr.t1.x = sr.paint[sr.i].v1.x - d->player.coord.x; 
		sr.t1.y = sr.paint[sr.i].v1.y - d->player.coord.y;
		sr.t2.x = sr.paint[sr.i].v2.x - d->player.coord.x;
		sr.t2.y = sr.paint[sr.i].v2.y - d->player.coord.y;
		sr.z1 = sr.paint[sr.i].v1.z - d->player.coord.z;
		sr.z2 = sr.paint[sr.i].v2.z - d->player.coord.z;

		rotate_vector_xy(&sr.t1, d->player.anglesin, d->player.anglecos);
		rotate_vector_xy(&sr.t2, d->player.anglesin, d->player.anglecos);
		sr.v1 = sr.t1;
		sr.v2 = sr.t2;
		sr.t1_1_line = sr.t1.y < sr.t1.x * 1.455;
		sr.t1_2_line = sr.t1.y < -sr.t1.x * 1.455;
		sr.t2_1_line = sr.t2.y < sr.t2.x * 1.455;
		sr.t2_2_line = sr.t2.y < -sr.t2.x * 1.455;
		if ((sr.t1_1_line && sr.t2_1_line) || (sr.t1_2_line && sr.t2_2_line))
			continue ;
		if (sr.t1_1_line || sr.t1_2_line || sr.t2_1_line || sr.t2_2_line)
		{
			sr.i1 = intersect((t_vertex){sr.t1.x, sr.t1.y}, (t_vertex){sr.t2.x, sr.t2.y}, (t_vertex){0, 0}, (t_vertex){1, 1.455});	
			sr.i2 = intersect((t_vertex){sr.t1.x, sr.t1.y}, (t_vertex){sr.t2.x, sr.t2.y}, (t_vertex){0, 0}, (t_vertex){-1, 1.455});
			if (sr.t1_1_line && sr.i1.y >= 0)
				sr.t1 = (t_vector){sr.i1.x, sr.i1.y, sr.t1.z};
			if (sr.t1_2_line && sr.i2.y >= 0)
				sr.t1 = (t_vector){sr.i2.x, sr.i2.y, sr.t1.z};
			if (sr.t2_1_line && sr.i1.y >= 0)
				sr.t2 = (t_vector){sr.i1.x, sr.i1.y, sr.t2.z};
			if (sr.t2_2_line && sr.i2.y >= 0)
				sr.t2 = (t_vector){sr.i2.x, sr.i2.y, sr.t2.z};
		}
		
		sr.xscale1 = HFOV / sr.t1.y;
		sr.xscale2 = HFOV / sr.t2.y;
		sr.zscale1 = VFOV / sr.t1.y;
		sr.zscale2 = VFOV / sr.t2.y;

		sr.x1 = WIN_WIDTH / 2 - (sr.t1.x * sr.xscale1);
		sr.x2 = WIN_WIDTH / 2 - (sr.t2.x * sr.xscale2);
		//find if sprite's sector was rendered atleast once
		sr.tmp = sr.begin;
		while (sr.tmp != d->render.tail)
		{
			if (sr.tmp->num == sr.paint[sr.i].sector_no)
			{
				
				if(sr.x1 >= sr.x2 || sr.x2 < sr.tmp->sx1 || sr.x1 > sr.tmp->sx2)
				{
					if (++sr.tmp == (d->render.queue + MAX_SECTORS_RENDERED))
						sr.tmp = d->render.queue;
					continue ;
				}

				sr.xscale1_p = HFOV / sr.v1.y;
				sr.xscale2_p = HFOV / sr.v2.y;
				sr.x1_p = WIN_WIDTH / 2 - (sr.v1.x * sr.xscale1_p);
				sr.x2_p = WIN_WIDTH / 2 - (sr.v2.x * sr.xscale2_p);

				sr.begin_x = max(sr.x1, sr.tmp->sx1);
				sr.end_x = min(sr.x2, sr.tmp->sx2);
				sr.win_x = sr.begin_x - 1;
				
				sr.z1a = WIN_HEIGHT / 2 - (int)((sr.z1 + sr.t1.y * d->player.angle_z) * sr.zscale1);
				sr.z1b = WIN_HEIGHT / 2 - (int)((sr.z2 + sr.t1.y * d->player.angle_z) * sr.zscale1);
				sr.z2a = WIN_HEIGHT / 2 - (int)((sr.z1 + sr.t2.y * d->player.angle_z) * sr.zscale2);
				sr.z2b = WIN_HEIGHT / 2 - (int)((sr.z2 + sr.t2.y  * d->player.angle_z) * sr.zscale2);

				sr.d_percent = 1.0 / (sr.x2_p - sr.x1_p);
				sr.percent = (sr.win_x - sr.x1_p) * sr.d_percent;
				
				sr.d_za = (sr.z2a - sr.z1a) / (sr.x2 - sr.x1);
				sr.d_zb = (sr.z2b - sr.z1b) / (sr.x2 - sr.x1);
				sr.za = (sr.win_x - sr.x1) * sr.d_za + sr.z1a;
				sr.zb = (sr.win_x - sr.x1) * sr.d_zb + sr.z1b;
				
				sr.percent_of_wall = fpercent(sr.tmp->sx1, sr.tmp->sx2, sr.win_x);
				sr.d_percent_of_wall = 1.0 / ((float)sr.tmp->sx2 - sr.tmp->sx1); //deri

				sr.d_y = (sr.t2.y - sr.t1.y) / (sr.x2 - sr.x1);
				sr.y = (sr.win_x - sr.x1) * sr.d_y + sr.t1.y; //dunno if it need
				

				while (++sr.win_x <= sr.end_x) // in wall 
				{
					sr.x_text = (sr.surr->w * sr.percent) / ((1 - sr.percent) * sr.v2.y / sr.v1.y + sr.percent); 	// a * w / ((1 - a) * z2 / z1 + a)
					sr.clmp_bot = line_point(sr.tmp->zbot1, sr.tmp->zbot2, sr.percent_of_wall);
					sr.clmp_top = line_point(sr.tmp->ztop1, sr.tmp->ztop2, sr.percent_of_wall);
					sr.clmp_top = max(sr.clmp_top, 0);
					sr.clmp_bot = min(sr.clmp_bot, WIN_HEIGHT - 1);
					
					draw_line_of_sprite(&sr, sr.surr, &d->render);
					sr.y += sr.d_y;
					sr.za += sr.d_za;
					sr.zb += sr.d_zb;
					sr.percent += sr.d_percent;
					sr.percent_of_wall += sr.d_percent_of_wall;
				}
			}
			if (++sr.tmp == (d->render.queue + MAX_SECTORS_RENDERED))
				sr.tmp = d->render.queue;
		}
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
		cc.map_y = (cc.rotated.h) * VFOV / (cc.screen_y + cc.denomi);
		cc.map_x = cc.map_y * cc.x_multi;
		cc.dummy = cc.map_y * r->pcos + cc.map_x * r->psin;
		cc.doomy = cc.map_y * r->psin - cc.map_x * r->pcos;
		cc.map_x = cc.dummy + r->p_x;
		cc.map_y = cc.doomy + r->p_y;
		cc.x_text = (cc.map_x * cc.surr->w) * cc.sect->x_c_scale + cc.sect->x_c_shift;
		cc.y_text = (cc.map_y * cc.surr->h) * cc.sect->y_c_scale + cc.sect->y_c_shift;
		cc.color = pix_from_text(cc.surr, (unsigned)cc.x_text % cc.surr->w, (unsigned)cc.y_text % cc.surr->h);
		if (cc.color != 0)
			r->pix[cc.screen_y * WIN_WIDTH + t->win_x] = get_color_value_int(cc.color, 0x0, t->r->sect->light_lvl);
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
		fc.map_y = (fc.rotated.h) * VFOV / (fc.screen_y + fc.denomi);
		fc.map_x = fc.map_y * fc.x_multi;
		fc.dummy = fc.map_y * r->pcos + fc.map_x * r->psin;
		fc.doomy = fc.map_y * r->psin - fc.map_x * r->pcos;
		fc.map_x = fc.dummy + r->p_x;
		fc.map_y = fc.doomy + r->p_y;
		fc.x_text = (fc.map_x * fc.surr->w) * fc.sect->x_f_scale + fc.sect->x_f_shift;
		fc.y_text = (fc.map_y * fc.surr->h) * fc.sect->y_f_scale + fc.sect->x_f_shift;
		fc.color = pix_from_text(fc.surr, (unsigned)fc.x_text % fc.surr->w, (unsigned)fc.y_text % fc.surr->h);
		if (fc.color != 0)
			r->pix[fc.screen_y * WIN_WIDTH + t->win_x] = get_color_value_int(fc.color, 0x0, t->r->sect->light_lvl);
		fc.screen_y++;
	}
}

void	render_sprites(t_doom *d)
{
	t_sprite_render	sr;

	sr = d->sr;
	sr.c_sprt = d->map.num_sprites;
	
	sr.i = -1;
	while (++sr.i < sr.c_sprt)
		sr.sprites[sr.i] = d->map.sprites[sr.i];

	translate_and_rotate_sprites(sr.sprites, sr.c_sprt, d->player);
	sprite_sort(sr.sprites, sr.c_sprt); //sorted by descent

	sr.i = -1;
	while (++sr.i < sr.c_sprt && sr.sprites[sr.i].coord.y > 0)
	{
		sr.surr = d->texture.sprites->sprites[sr.i];
		sr.t1.x = sr.sprites[sr.i].coord.x + sr.sprites[sr.i].width / 2; //this 1 could be replaced with sprite width
		sr.t1.y = sr.sprites[sr.i].coord.y;
		sr.t2.x = sr.sprites[sr.i].coord.x - sr.sprites[sr.i].width / 2; //this 1 could be replaced with sprite width
		sr.t2.y = sr.sprites[sr.i].coord.y;
		sr.t1.z = sr.sprites[sr.i].coord.z + sr.sprites[sr.i].end_z; //2 - sprite height right now
		sr.t2.z = sr.sprites[sr.i].coord.z + sr.sprites[sr.i].start_z; //
		sr.z1 = sr.t1.z - d->player.coord.z; //top
		sr.z2 = sr.t2.z - d->player.coord.z; //bot

		sr.v1 = sr.t1;
		sr.v2 = sr.t2;

		sr.t1_1_line = sr.t1.y < sr.t1.x * 1.455;
		sr.t1_2_line = sr.t1.y < -sr.t1.x * 1.455;
		sr.t2_1_line = sr.t2.y < sr.t2.x * 1.455;
		sr.t2_2_line = sr.t2.y < -sr.t2.x * 1.455;
		if ((sr.t1_1_line && sr.t2_1_line) || (sr.t1_2_line && sr.t2_2_line))
			continue ;
		if (sr.t1_1_line || sr.t1_2_line || sr.t2_1_line || sr.t2_2_line)
		{
			sr.i1 = intersect((t_vertex){sr.t1.x, sr.t1.y}, (t_vertex){sr.t2.x, sr.t2.y}, (t_vertex){0, 0}, (t_vertex){1, 1.455});	
			sr.i2 = intersect((t_vertex){sr.t1.x, sr.t1.y}, (t_vertex){sr.t2.x, sr.t2.y}, (t_vertex){0, 0}, (t_vertex){-1, 1.455});
			if (sr.t1_1_line && sr.i1.y >= 0)
				sr.t1 = (t_vector){sr.i1.x, sr.i1.y, sr.t1.z};
			if (sr.t1_2_line && sr.i2.y >= 0)
				sr.t1 = (t_vector){sr.i2.x, sr.i2.y, sr.t1.z};
			if (sr.t2_1_line && sr.i1.y >= 0)
				sr.t2 = (t_vector){sr.i1.x, sr.i1.y, sr.t2.z};
			if (sr.t2_2_line && sr.i2.y >= 0)
				sr.t2 = (t_vector){sr.i2.x, sr.i2.y, sr.t2.z};
		}
		
		sr.xscale1 = HFOV / sr.t1.y;
		sr.xscale2 = HFOV / sr.t2.y; //same as previus for some sprites
		sr.zscale1 = VFOV / sr.t1.y;
		sr.zscale2 = VFOV / sr.t2.y;

		sr.x1 = WIN_WIDTH / 2 - (sr.t1.x * sr.xscale1);
		sr.x2 = WIN_WIDTH / 2 - (sr.t2.x * sr.xscale2);

		//find if sprite's sector was rendered atleast once
		sr.tmp = sr.begin;
		while (sr.tmp != d->render.tail)
		{
			if (sr.tmp->num == sr.sprites[sr.i].sector_no)
			{
				if(sr.x1 >= sr.x2 || sr.x2 < sr.tmp->sx1 || sr.x1 > sr.tmp->sx2)
				{
					if (++sr.tmp == (d->render.queue + MAX_SECTORS_RENDERED))
						sr.tmp = d->render.queue;
					continue ;
				}

				sr.xscale1_p = HFOV / sr.v1.y;
				sr.xscale2_p = HFOV / sr.v2.y;
				sr.x1_p = WIN_WIDTH / 2 - (sr.v1.x * sr.xscale1_p);
				sr.x2_p = WIN_WIDTH / 2 - (sr.v2.x * sr.xscale2_p);

				sr.begin_x = max(sr.x1, sr.tmp->sx1);
				sr.end_x = min(sr.x2, sr.tmp->sx2);		
				sr.win_x = sr.begin_x;
				
				sr.z1a = WIN_HEIGHT / 2 - (int)((sr.z1 + sr.t1.y * d->player.angle_z) * sr.zscale1);
				sr.z1b = WIN_HEIGHT / 2 - (int)((sr.z2 + sr.t1.y * d->player.angle_z) * sr.zscale1);
				sr.z2a = WIN_HEIGHT / 2 - (int)((sr.z1 + sr.t2.y * d->player.angle_z) * sr.zscale2);
				sr.z2b = WIN_HEIGHT / 2 - (int)((sr.z2 + sr.t2.y  * d->player.angle_z) * sr.zscale2);

				sr.d_percent = 1.0 / (sr.x2_p - sr.x1_p);
				sr.percent = (sr.win_x - sr.x1_p) * sr.d_percent;
				sr.y = sr.t1.y;

				sr.x_text = (sr.surr->w * sr.percent); // a * w / ((1 - a) * z2 / z1 + a) // z1 == z2
				sr.d_x_text = sr.surr->w * sr.d_percent;

				sr.d_za = (sr.z2a - sr.z1a) / (sr.x2 - sr.x1);
				sr.d_zb = (sr.z2b - sr.z1b) / (sr.x2 - sr.x1);
				sr.za = (sr.win_x - sr.x1) * sr.d_za + sr.z1a;
				sr.zb = (sr.win_x - sr.x1) * sr.d_zb + sr.z1b;
				
				sr.percent_of_wall = fpercent(sr.tmp->sx1, sr.tmp->sx2, sr.win_x);
				sr.d_percent_of_wall = 1.0 / ((float)sr.tmp->sx2 - sr.tmp->sx1); //deri

				while (sr.win_x <= sr.end_x) // in wall 
				{
					sr.clmp_top = line_point(sr.tmp->ztop1, sr.tmp->ztop2, sr.percent_of_wall);
					sr.clmp_bot = line_point(sr.tmp->zbot1, sr.tmp->zbot2, sr.percent_of_wall);
					sr.clmp_top = max(sr.clmp_top, 0);
					sr.clmp_bot = min(sr.clmp_bot, WIN_HEIGHT - 1);
					draw_line_of_sprite(&sr, sr.surr, &d->render);
					sr.za += sr.d_za;
					sr.zb += sr.d_zb;
					sr.percent += sr.d_percent;
					sr.x_text += sr.d_x_text;
					sr.percent_of_wall += sr.d_percent_of_wall;
					sr.win_x++;
				}
			}
			if (++sr.tmp == (d->render.queue + MAX_SECTORS_RENDERED))
				sr.tmp = d->render.queue;
		}
	}
}

int		draw_screen(t_doom d)
{
	*d.render.head = (t_rend_sector){d.player.sector, 0, WIN_WIDTH - 1, 0, 0, WIN_HEIGHT - 1, WIN_HEIGHT - 1};
	
	d.sr.begin = d.render.head;
	if (++d.render.head == d.render.queue + MAX_SECTORS_RENDERED)
	 	d.render.head = d.render.queue;

	while (d.render.head != d.render.tail)
	{
		d.render.now = *d.render.tail;
		if (++d.render.tail == (d.render.queue + MAX_SECTORS_RENDERED))
			d.render.tail = d.render.queue;
		if (d.render.rendered_sectors[d.render.now.num] & (MAX_SECTORS_RENDERED + 1))
			continue ;
		render_sector(&d.render, &d);
	}
	render_painting(&d);
	render_sprites(&d);
	return (0);
}
