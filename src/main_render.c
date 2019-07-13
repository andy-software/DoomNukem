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

void	render_sector(t_render *r, t_doom d)
{
	int i;

	++r->rendered_sectors[r->now.num];
	r->sect = d.map.sectors + r->now.num; //&d.map.sectors[r->now.num];
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
		r->win_x = r->begin_x - 1;

		r->mc1 = r->t1;
		rotate_vertex_xy(&r->mc1, r->psin, -r->pcos); //rotate and translate back
		r->mc2 = r->t2;
		rotate_vertex_xy(&r->mc2, r->psin, -r->pcos);
		r->mc1.x += r->p_x;
		r->mc2.x += r->p_x;
		r->mc1.y += r->p_y;
		r->mc2.y += r->p_y;
		if (r->neighbor >= 0)
		{
			r->ncplane = d.map.sectors[(int)r->neighbor].ceil_plane;
			r->nfplane = d.map.sectors[(int)r->neighbor].floor_plane;

			r->nzceil1 = get_z(r->ncplane, r->mc1.x, r->mc1.y) - r->p_z;
			r->nzfloor1 = get_z(r->nfplane, r->mc1.x, r->mc1.y) - r->p_z;
			r->nzceil2 = get_z(r->ncplane, r->mc2.x, r->mc2.y) - r->p_z;
			r->nzfloor2 = get_z(r->nfplane, r->mc2.x, r->mc2.y) - r->p_z;
			r->nz1a = WIN_HEIGHT / 2 - (int)((r->nzceil1 + r->t1.y * d.player.angle_z) * r->zscale1);
			r->nz1b = WIN_HEIGHT / 2 - (int)((r->nzfloor1 + r->t1.y * d.player.angle_z) * r->zscale1);
			r->nz2a = WIN_HEIGHT / 2 - (int)((r->nzceil2 + r->t2.y * d.player.angle_z) * r->zscale2);
			r->nz2b = WIN_HEIGHT / 2 - (int)((r->nzfloor2 + r->t2.y * d.player.angle_z) * r->zscale2);
		}
		
		r->zceil1  = get_z(r->cplane, r->mc1.x, r->mc1.y) - r->p_z;
		r->zfloor1 = get_z(r->fplane, r->mc1.x, r->mc1.y) - r->p_z;
		r->zceil2  = get_z(r->cplane, r->mc2.x, r->mc2.y) - r->p_z;
		r->zfloor2 = get_z(r->fplane, r->mc2.x, r->mc2.y) - r->p_z;

		r->max_b = max(r->zfloor1, r->zfloor2);
		r->min_a = min(r->zceil1, r->zceil2);

		r->z1a = WIN_HEIGHT / 2 - (int)((r->zceil1 + r->t1.y * d.player.angle_z) * r->zscale1);
		r->z1b = WIN_HEIGHT / 2 - (int)((r->zfloor1 + r->t1.y * d.player.angle_z) * r->zscale1);
		r->z2a  = WIN_HEIGHT / 2 - (int)((r->zceil2 + r->t2.y * d.player.angle_z) * r->zscale2);
		r->z2b = WIN_HEIGHT / 2 - (int)((r->zfloor2 + r->t2.y  * d.player.angle_z) * r->zscale2);
		
		float	kt = (r->t2.y - r->t1.y) / (r->x2 - r->x1);
		float	kza = (r->z2a - r->z1a) / (r->x2 - r->x1);
		float	kzb = (r->z2b - r->z1b) / (r->x2 - r->x1);
		float	nkza = (r->nz2a - r->nz1a) / (r->x2 - r->x1);
		float	nkzb = (r->nz2b - r->nz1b) / (r->x2 - r->x1);	

		r->len = line_len(r->sect->vert[i + 1], r->sect->vert[i]);

		r->dummy_var_x = (d.texture.wall_tex[r->line.wall]->w * r->line.x_w_scale - 1) / r->len;  //just a variable to calculate same things //used later
		r->w0 = line_len(r->mc1, r->sect->vert[i]) * r->dummy_var_x + r->line.x_w_shift;
		r->w1 = line_len(r->mc2, r->sect->vert[i]) * r->dummy_var_x + r->line.x_w_shift;
		
		r->dummy_var_x = (d.texture.wall_tex[r->line.bot]->w * r->line.x_b_scale - 1) / r->len;  //just a variable to calculate same things //used later
		r->w0_bot = line_len(r->mc1, r->sect->vert[i]) * r->dummy_var_x + r->line.x_b_shift;
		r->w1_bot = line_len(r->mc2, r->sect->vert[i]) * r->dummy_var_x + r->line.x_b_shift;

		r->dummy_var_x = (d.texture.wall_tex[r->line.top]->w * r->line.x_t_scale - 1) / r->len; //just a variable to calculate same things //used later
		r->w0_top = line_len(r->mc1, r->sect->vert[i]) * r->dummy_var_x + r->line.x_t_shift;
		r->w1_top = line_len(r->mc2, r->sect->vert[i]) * r->dummy_var_x + r->line.x_t_shift;

		r->alpha = (r->win_x - r->x1) / (r->x2 - r->x1);
		r->d_alpha = 1 / (r->x2 - r->x1);
		r->dummy_var_x = (1 - r->alpha) / r->t1.y;
		r->d_dummy_var_x = -r->d_alpha / r->t1.y;
		r->doomy_var_x = r->alpha / r->t2.y;
		r->d_doomy_var_x = r->d_alpha / r->t2.y;

		//floor cal
		r->floor_cal.random_vector = (t_vector){0, 0, get_z(r->fplane, r->p_x, r->p_y) - r->p_z};
		r->floor_cal.rotated.a = r->fplane.a * r->psin - r->fplane.b * r->pcos;
		r->floor_cal.rotated.b = r->fplane.a * r->pcos + r->fplane.b * r->psin;
		r->floor_cal.rotated.c = r->fplane.c;
		r->floor_cal.rotated.h = -r->floor_cal.random_vector.z;
		r->floor_cal.sect = r->sect;

		//ceil cal
		r->ceil_cal.random_vector = (t_vector){0, 0, get_z(r->cplane, r->p_x, r->p_y) - r->p_z};
		r->ceil_cal.rotated.a = r->cplane.a * r->psin - r->cplane.b * r->pcos;
		r->ceil_cal.rotated.b = r->cplane.a * r->pcos + r->cplane.b * r->psin;
		r->ceil_cal.rotated.c = r->cplane.c;
		r->ceil_cal.rotated.h = -r->ceil_cal.random_vector.z;
		r->ceil_cal.sect = r->sect;

		while (++r->win_x <= r->end_x) // in wall 
		{
			r->x_text = (r->dummy_var_x * r->w0 + r->doomy_var_x * r->w1) / (r->dummy_var_x + r->doomy_var_x);
			r->x_text %= d.texture.wall_tex[r->line.wall]->w;
			r->x_text_lower = (r->dummy_var_x * r->w0_bot + r->doomy_var_x * r->w1_bot) / (r->dummy_var_x + r->doomy_var_x);
			r->x_text_lower %= d.texture.wall_tex[r->line.bot]->w;
			r->x_text_upper = (r->dummy_var_x * r->w0_top + r->doomy_var_x * r->w1_top) / (r->dummy_var_x + r->doomy_var_x);
			r->x_text_upper %= d.texture.wall_tex[r->line.top]->w;

			r->y = (r->win_x - r->x1) * kt + r->t1.y;
			r->za = (r->win_x - r->x1) * kza + r->z1a;
			r->zb = (r->win_x - r->x1) * kzb + r->z1b;
			r->c_za = clamp(r->za, r->ztop[r->win_x], r->zbottom[r->win_x]);
			r->c_zb = clamp(r->zb, r->ztop[r->win_x], r->zbottom[r->win_x]);

			render_floor_line(r->c_zb + 1, r->zbottom[r->win_x], r);
			if (r->sect->render_ceil)
				render_ceil_line(r->c_za - 1, r->ztop[r->win_x], r);

			if(r->neighbor >= 0)
			{
				r->nza = (r->win_x - r->x1) * nkza + r->nz1a;
				r->c_nza = clamp(r->nza, r->ztop[r->win_x], r->zbottom[r->win_x]);
				r->nzb = (r->win_x - r->x1) * nkzb + r->nz1b;
				r->c_nzb = clamp(r->nzb, r->ztop[r->win_x], r->zbottom[r->win_x]);

				//vertical_line(r->win_x, r->c_za, r->nza - 1, r, 0x0F0F0F); // down to sector
				if (!r->sect->render_ceil)
					reversed_textline_draw(r->za, r->nza - 1, r);
				else
					upper_textline(r->za, r->nza - 1, r);
				r->ztop[r->win_x] = clamp(max(r->c_za, r->c_nza), r->ztop[r->win_x], WIN_HEIGHT - 1);
				//vertical_line(r->win_x, r->nzb + 1, r->c_zb, r, 0xFF0000); // up to sector
				lower_textline(r->nzb + 1, r->zb, r);
				r->zbottom[r->win_x] = clamp(min(r->c_zb, r->c_nzb), 0, r->zbottom[r->win_x]);
			}
			else
			{
				//vertical_line(r->win_x, r->c_za, r->c_zb, r, 0xAAAAAA);
				textline_draw(r->c_za, r->c_zb, r);
			}
			r->alpha += r->d_alpha;
			r->doomy_var_x += r->d_doomy_var_x;
			r->dummy_var_x += r->d_dummy_var_x;		
		}
		
		if (r->neighbor >= 0 && r->end_x >= r->begin_x && (r->head + MAX_SECTORS_RENDERED + 1 - r->tail) % MAX_SECTORS_RENDERED)
		{
			int za1 = (r->begin_x - r->x1) * kza + r->z1a;
			int zb1 = (r->begin_x - r->x1) * kzb + r->z1b;
			int nza1 = (r->begin_x - r->x1) * nkza + r->nz1a;
			int nzb1 = (r->begin_x - r->x1) * nkzb + r->nz1b;

			int za2 = (r->end_x - r->x1) * kza + r->z1a;
			int	zb2 = (r->end_x - r->x1) * kzb + r->z1b;
			int	nza2 = (r->end_x - r->x1) * nkza + r->nz1a;
			int	nzb2 =  (r->end_x - r->x1) * nkzb + r->nz1b; //pls recode this in something better

			*r->head = (t_rend_sector) {r->neighbor, r->begin_x, r->end_x, \
				max(za1, nza1), max(za2, nza2), min(zb1, nzb1), min(zb2, nzb2)};
			if(++r->head == (r->queue + MAX_SECTORS_RENDERED))
				r->head = r->queue;
		}
	}
	++r->rendered_sectors[r->now.num];
	//printf("Rendered %i now in %i\n", r->now.num, d.player.sector);
}

void	reversed_textline_draw(int y1, int y2, t_render *r)
{
	SDL_Surface	*surr;

	if (y2 == y1)
		return ;

	surr = r->texture->wall_tex[r->line.top];

	r->win_y = clamp(y2, 0, WIN_HEIGHT - 1);//kostill
	r->wall_end = clamp(y1, 0, WIN_HEIGHT - 1);
	
	r->betta = (float)(r->za - r->win_y) / (r->zb - r->za); //kostill//not like this
	r->d_betta = -1.0 / (r->zb - r->za); 
	r->float_y_text = r->betta * (surr->h - 1); //add some scaler
	r->d_y_text = surr->h * r->d_betta;  //add some scaler
	while(r->win_y < r->wall_end)
	{
		r->color = pix_from_text(surr, r->x_text_upper, (int)r->float_y_text % surr->h);
		if (r->color != 0)
			r->pix[r->win_y * WIN_WIDTH + r->win_x] = r->color;
		r->win_y++;
		r->betta += r->d_betta;
		r->float_y_text += r->d_y_text;
	}
}

void	upper_textline(int y1, int y2, t_render *r)
{
	SDL_Surface	*surr;

	if (y2 == y1)
		return ;
	surr = r->texture->wall_tex[r->line.top];

	r->win_y = clamp(y1, 0, WIN_HEIGHT - 1);
	r->wall_end = clamp(y2, 0, WIN_HEIGHT - 1);
	
	r->betta = (float)(r->win_y - r->za) / (r->zb - r->za); //not like this
	r->d_betta = 1.0 / (r->zb - r->za);
	r->float_y_text = r->betta * (surr->h - 1); //add some scaler
	r->d_y_text = surr->h * r->d_betta; //add some scaler
	while(r->win_y < r->wall_end)
	{
		r->color = pix_from_text(surr, r->x_text_upper, (unsigned)r->float_y_text % surr->h);
		if (r->color != 0)
			r->pix[r->win_y * WIN_WIDTH + r->win_x] = r->color;
		r->win_y++;
		r->betta += r->d_betta;
		r->float_y_text += r->d_y_text;
	}
}

void	lower_textline(int y1, int y2, t_render *r)
{
	SDL_Surface	*surr;

	if (y2 == y1)
		return ;
	surr = r->texture->wall_tex[r->line.bot];

	r->win_y = clamp(y1, 0, WIN_HEIGHT - 1);
	r->wall_end = clamp(y2, 0, WIN_HEIGHT - 1);
	
	r->betta = (float)(r->win_y - r->za) / (r->zb - r->za); //not like this
	r->d_betta = 1.0 / (r->zb - r->za);
	r->float_y_text = r->betta * (surr->h - 1); //add some scaler
	r->d_y_text = surr->h * r->d_betta; //add some scaler
	while(r->win_y < r->wall_end)
	{
		r->color = pix_from_text(surr, r->x_text_lower, (unsigned)r->float_y_text % surr->h);
		if (r->color != 0)
			r->pix[r->win_y * WIN_WIDTH + r->win_x] = r->color;
		r->win_y++;
		r->betta += r->d_betta;
		r->float_y_text += r->d_y_text;
	}
}

void	textline_draw(int y1, int y2, t_render *r)
{
	SDL_Surface	*surr;

	if (y2 == y1)
		return ;
	surr = r->texture->wall_tex[r->line.wall];

	r->win_y = clamp(y1, 0, WIN_HEIGHT - 1);
	r->wall_end = clamp(y2, 0, WIN_HEIGHT - 1);
	
	r->betta = (float)(r->win_y - r->za) / (r->zb - r->za); //not like this
	r->d_betta = 1.0 / (r->zb - r->za);
	r->float_y_text = r->betta * (surr->h - 1); //add some scaler
	r->d_y_text = surr->h * r->d_betta; //add some scaler
	while(r->win_y < r->wall_end)
	{
		r->color = pix_from_text(surr, r->x_text, (unsigned)r->float_y_text % surr->h);
		if (r->color != 0)
			r->pix[r->win_y * WIN_WIDTH + r->win_x] = r->color;
		r->win_y++;
		r->betta += r->d_betta;
		r->float_y_text += r->d_y_text;
	}
}

void	draw_line_of_sprite(t_sprite_render *sr, SDL_Surface *sprtext, t_render *render)
{
	int		x_text;
	int		wall_end;
	float	y_point;
	int		y_text;
	Uint32	color;
	float	x1;
	float	x2;
	float	percent;
	float	xscale1;
	float	xscale2;
	float	dy_point;

	xscale1 = HFOV / sr->v1.y;
	xscale2 = HFOV / sr->v2.y;
	x1 = WIN_WIDTH / 2 - (sr->v1.x * xscale1);
	x2 = WIN_WIDTH / 2 - (sr->v2.x * xscale2);

	percent = (sr->win_x - x1) / (x2 - x1);
	x_text = (sprtext->w * percent) / ((1 - percent) * sr->v2.y / sr->v1.y + percent); // a * w / ((1 - a) * z2 / z1 + a)
	sr->win_y = clamp(sr->za, sr->clmp_top, sr->clmp_bot);
	wall_end = clamp(sr->zb, sr->clmp_top, sr->clmp_bot);
	y_point = (sr->zb == sr->za) ? 0 : (double)(sr->win_y - sr->za) / (sr->zb - sr->za);
	dy_point = (sr->zb == sr->za) ? (0) : (1.0 / (sr->zb - sr->za)); // derivation of y_point
	while(sr->win_y < wall_end)
	{
		y_text = y_point * sprtext->h;
		color = pix_from_text(sprtext, x_text, y_text);
		if (color != 0)
			render->pix[sr->win_y * WIN_WIDTH + sr->win_x] = color;
		sr->win_y++;
		y_point += dy_point;
	}
}

void	render_painting(t_sprite_render sr, t_doom d)
{
	d.sr.paint = d.map.paint; // i think this shouldnt be sorted
	d.sr.c_paint = d.map.num_paint;
	d.sr.i = -1;

	while (++d.sr.i < d.sr.c_paint)
	{
		d.sr.t1.x = d.sr.paint[d.sr.i].v1.x - d.player.coord.x; 
		d.sr.t1.y = d.sr.paint[d.sr.i].v1.y - d.player.coord.y;
		d.sr.t2.x = d.sr.paint[d.sr.i].v2.x - d.player.coord.x;
		d.sr.t2.y = d.sr.paint[d.sr.i].v2.y - d.player.coord.y;
		d.sr.z1 = d.sr.paint[d.sr.i].v1.z - d.player.coord.z; //top
		d.sr.z2 = d.sr.paint[d.sr.i].v2.z - d.player.coord.z; //bot

		rotate_vector_xy(&d.sr.t1, d.player.anglesin, d.player.anglecos);
		rotate_vector_xy(&d.sr.t2, d.player.anglesin, d.player.anglecos);
		d.sr.v1 = d.sr.t1;
		d.sr.v2 = d.sr.t2;

		d.sr.t1_1_line = d.sr.t1.y < d.sr.t1.x / 4;
		d.sr.t1_2_line = d.sr.t1.y < -d.sr.t1.x / 4;
		d.sr.t2_1_line = d.sr.t2.y < d.sr.t2.x / 4;
		d.sr.t2_2_line = d.sr.t2.y < -d.sr.t2.x / 4;
		if ((d.sr.t1_1_line && d.sr.t2_1_line) || (d.sr.t1_2_line && d.sr.t2_2_line))
			continue ;
		if (d.sr.t1_1_line || d.sr.t1_2_line || d.sr.t2_1_line || d.sr.t2_2_line)
		{
			d.sr.i1 = intersect((t_vertex){d.sr.t1.x, d.sr.t1.y}, (t_vertex){d.sr.t2.x, d.sr.t2.y}, (t_vertex){0, 0}, (t_vertex){4, 1});	
			d.sr.i2 = intersect((t_vertex){d.sr.t1.x, d.sr.t1.y}, (t_vertex){d.sr.t2.x, d.sr.t2.y}, (t_vertex){0, 0}, (t_vertex){-4, 1});
			if (d.sr.t1_1_line && d.sr.i1.y >= 0)
				d.sr.t1 = (t_vector){d.sr.i1.x, d.sr.i1.y, d.sr.t1.z};
			if (d.sr.t1_2_line && d.sr.i2.y >= 0)
				d.sr.t1 = (t_vector){d.sr.i2.x, d.sr.i2.y, d.sr.t1.z};
			if (d.sr.t2_1_line && d.sr.i1.y >= 0)
				d.sr.t2 = (t_vector){d.sr.i1.x, d.sr.i1.y, d.sr.t2.z};
			if (d.sr.t2_2_line && d.sr.i2.y >= 0)
				d.sr.t2 = (t_vector){d.sr.i2.x, d.sr.i2.y, d.sr.t2.z};
		}
		
		d.sr.xscale1 = HFOV / d.sr.t1.y;
		d.sr.xscale2 = HFOV / d.sr.t2.y;
		d.sr.zscale1 = VFOV / d.sr.t1.y;
		d.sr.zscale2 = VFOV / d.sr.t2.y;

		d.sr.x1 = WIN_WIDTH / 2 - (d.sr.t1.x * d.sr.xscale1);
		d.sr.x2 = WIN_WIDTH / 2 - (d.sr.t2.x * d.sr.xscale2);
		//find if sprite's sector was rendered atleast once
		d.sr.tmp = d.sr.begin;
		while (d.sr.tmp != d.render.tail)
		{
			if (d.sr.tmp->num == d.sr.paint[d.sr.i].sector_no)
			{
				
				if(d.sr.x1 >= d.sr.x2 || d.sr.x2 < d.sr.tmp->sx1 || d.sr.x1 > d.sr.tmp->sx2)
				{
					if (++d.sr.tmp == (d.render.queue + MAX_SECTORS_RENDERED))
						d.sr.tmp = d.render.queue;
					continue ;
				}
				
				d.sr.begin_x = max(d.sr.x1, d.sr.tmp->sx1);
				d.sr.end_x = min(d.sr.x2, d.sr.tmp->sx2);
				d.sr.win_x = d.sr.begin_x - 1;
				
				d.sr.z1a = WIN_HEIGHT / 2 - (int)((d.sr.z1 + d.sr.t1.y * d.player.angle_z) * d.sr.zscale1);
				d.sr.z1b = WIN_HEIGHT / 2 - (int)((d.sr.z2 + d.sr.t1.y * d.player.angle_z) * d.sr.zscale1);
				d.sr.z2a = WIN_HEIGHT / 2 - (int)((d.sr.z1 + d.sr.t2.y * d.player.angle_z) * d.sr.zscale2);
				d.sr.z2b = WIN_HEIGHT / 2 - (int)((d.sr.z2 + d.sr.t2.y  * d.player.angle_z) * d.sr.zscale2);

				while (++d.sr.win_x <= d.sr.end_x) // in wall 
				{
					d.sr.clmp_top = line_point(d.sr.tmp->ztop1, d.sr.tmp->ztop2, fpercent(d.sr.tmp->sx1, d.sr.tmp->sx2, d.sr.win_x));
					d.sr.clmp_top = max(d.sr.clmp_top, 0);
					d.sr.clmp_bot = line_point(d.sr.tmp->zbot1, d.sr.tmp->zbot2, fpercent(d.sr.tmp->sx1, d.sr.tmp->sx2, d.sr.win_x));
					d.sr.clmp_bot = min(d.sr.clmp_bot, WIN_HEIGHT - 1);

					d.sr.y = (d.sr.win_x - d.sr.x1) * (d.sr.t2.y - d.sr.t1.y) / (d.sr.x2 - d.sr.x1) + d.sr.t1.y; //dunno if it need
					d.sr.za = (d.sr.win_x - d.sr.x1) * (d.sr.z2a - d.sr.z1a) / (d.sr.x2 - d.sr.x1) + d.sr.z1a;
					d.sr.zb = (d.sr.win_x - d.sr.x1) * (d.sr.z2b - d.sr.z1b) / (d.sr.x2 - d.sr.x1) + d.sr.z1b;
					// d.sr.c_za = max(d.sr.za, d.sr.clmp_top); // i bet i never use this
					// d.sr.c_zb = min(d.sr.zb, d.sr.clmp_bot);
					draw_line_of_sprite(&d.sr, d.texture.sprites->next->sprites[0], &d.render);
				}
			}
			if (++d.sr.tmp == (d.render.queue + MAX_SECTORS_RENDERED))
				d.sr.tmp = d.render.queue;
		}
	}
}


void	render_ceil_line(int start, int end, t_render *r)
{
	t_ceil_cal	cc;
	SDL_Surface	*surr;

	cc = r->ceil_cal;
	surr = r->texture->wall_tex[cc.sect->ceil_tex];
	cc.screen_y = clamp(start, end, WIN_HEIGHT);
	cc.x_multi = (WIN_WIDTH / 2 - r->win_x) / (HFOV);
	cc.denomi = - WIN_HEIGHT / 2 + (cc.rotated.a * (-cc.x_multi) - cc.rotated.b + r->angle_z) * VFOV;
	
	while (cc.screen_y > end)
	{
		cc.map_y = (cc.rotated.h) * VFOV / (cc.screen_y + cc.denomi);
		cc.map_x = cc.map_y * cc.x_multi;
		cc.dummy = cc.map_y * r->pcos + cc.map_x * r->psin;
		cc.doomy = cc.map_y * r->psin - cc.map_x * r->pcos;
		cc.map_x = cc.dummy + r->p_x;
		cc.map_y = cc.doomy + r->p_y;
		cc.x_text = (cc.map_x * surr->w) * cc.sect->x_c_scale + cc.sect->x_c_shift;
		cc.y_text = (cc.map_y * surr->h) * cc.sect->y_c_scale + cc.sect->y_c_shift;
		cc.color = pix_from_text(surr, (unsigned)cc.x_text % surr->w, (unsigned)cc.y_text % surr->h);
		if (cc.color != 0)
			r->pix[cc.screen_y * WIN_WIDTH + r->win_x] = cc.color;
		cc.screen_y--;
	}
}

void	render_floor_line(int start, int end, t_render *r)
{
	t_floor_cal	fc;
	SDL_Surface	*surr;
	
	fc = r->floor_cal;
	surr = r->texture->wall_tex[fc.sect->floor_tex];
	fc.screen_y = clamp(start, 0, end);
	fc.x_multi = (WIN_WIDTH / 2 - r->win_x) / (HFOV);
	fc.denomi = -WIN_HEIGHT / 2 + (fc.rotated.a * (-fc.x_multi) - fc.rotated.b + r->angle_z) * VFOV;
	
	while (fc.screen_y < end)
	{
		fc.map_y = (fc.rotated.h) * VFOV / (fc.screen_y + fc.denomi);
		fc.map_x = fc.map_y * fc.x_multi;
		fc.dummy = fc.map_y * r->pcos + fc.map_x * r->psin;
		fc.doomy = fc.map_y * r->psin - fc.map_x * r->pcos;
		fc.map_x = fc.dummy + r->p_x;
		fc.map_y = fc.doomy + r->p_y;
		fc.x_text = (fc.map_x * surr->w) * fc.sect->x_f_scale + fc.sect->x_f_shift;
		fc.y_text = (fc.map_y * surr->h) * fc.sect->y_f_scale + fc.sect->x_f_shift;
		fc.color = pix_from_text(surr, (unsigned)fc.x_text % surr->w, (unsigned)fc.y_text % surr->h);
		if (fc.color != 0)
			r->pix[fc.screen_y * WIN_WIDTH + r->win_x] = fc.color;
		fc.screen_y++;
	}
}

void	render_sprites(t_sprite_render sr, t_doom d)
{
	d.sr.c_sprt = d.map.num_sprites;
	d.sr.i = -1;
	while (++d.sr.i < d.sr.c_sprt)
		d.sr.sprites[d.sr.i] = d.map.sprites[d.sr.i];

	translate_and_rotate_sprites(d.sr.sprites, d.sr.c_sprt, d.player);
	sprite_sort(d.sr.sprites, d.sr.c_sprt); //sorted by descent

	d.sr.i = -1;
	while (++d.sr.i < d.sr.c_sprt && d.sr.sprites[d.sr.i].coord.y > 0)
	{
		d.sr.t1.x = d.sr.sprites[d.sr.i].coord.x + 1; //this 1 could be replaced with sprite width
		d.sr.t1.y = d.sr.sprites[d.sr.i].coord.y;
		d.sr.t2.x = d.sr.sprites[d.sr.i].coord.x - 1; //this 1 could be replaced with sprite width
		d.sr.t2.y = d.sr.sprites[d.sr.i].coord.y;
		d.sr.t1.z = d.sr.sprites[d.sr.i].coord.z + 2; //2 - sprite height right now
		d.sr.t2.z = d.sr.sprites[d.sr.i].coord.z;
		d.sr.z1 = d.sr.t1.z - d.player.coord.z; //top
		d.sr.z2 = d.sr.t2.z - d.player.coord.z; //bot

		d.sr.v1 = d.sr.t1;
		d.sr.v2 = d.sr.t2;

		d.sr.t1_1_line = d.sr.t1.y < d.sr.t1.x / 4;
		d.sr.t1_2_line = d.sr.t1.y < -d.sr.t1.x / 4;
		d.sr.t2_1_line = d.sr.t2.y < d.sr.t2.x / 4;
		d.sr.t2_2_line = d.sr.t2.y < -d.sr.t2.x / 4;
		if ((d.sr.t1_1_line && d.sr.t2_1_line) || (d.sr.t1_2_line && d.sr.t2_2_line))
			continue ;
		if (d.sr.t1_1_line || d.sr.t1_2_line || d.sr.t2_1_line || d.sr.t2_2_line)
		{
			d.sr.i1 = intersect((t_vertex){d.sr.t1.x, d.sr.t1.y}, (t_vertex){d.sr.t2.x, d.sr.t2.y}, (t_vertex){0, 0}, (t_vertex){4, 1});	
			d.sr.i2 = intersect((t_vertex){d.sr.t1.x, d.sr.t1.y}, (t_vertex){d.sr.t2.x, d.sr.t2.y}, (t_vertex){0, 0}, (t_vertex){-4, 1});
			if (d.sr.t1_1_line && d.sr.i1.y >= 0)
				d.sr.t1 = (t_vector){d.sr.i1.x, d.sr.i1.y, d.sr.t1.z};
			if (d.sr.t1_2_line && d.sr.i2.y >= 0)
				d.sr.t1 = (t_vector){d.sr.i2.x, d.sr.i2.y, d.sr.t1.z};
			if (d.sr.t2_1_line && d.sr.i1.y >= 0)
				d.sr.t2 = (t_vector){d.sr.i1.x, d.sr.i1.y, d.sr.t2.z};
			if (d.sr.t2_2_line && d.sr.i2.y >= 0)
				d.sr.t2 = (t_vector){d.sr.i2.x, d.sr.i2.y, d.sr.t2.z};
		}
		
		d.sr.xscale1 = HFOV / d.sr.t1.y;
		d.sr.xscale2 = HFOV / d.sr.t2.y; //same as previus for some sprites
		d.sr.zscale1 = VFOV / d.sr.t1.y;
		d.sr.zscale2 = VFOV / d.sr.t2.y;

		d.sr.x1 = WIN_WIDTH / 2 - (d.sr.t1.x * d.sr.xscale1);
		d.sr.x2 = WIN_WIDTH / 2 - (d.sr.t2.x * d.sr.xscale2);

		//find if sprite's sector was rendered atleast once
		d.sr.tmp = d.sr.begin;
		while (d.sr.tmp != d.render.tail)
		{
			if (d.sr.tmp->num == d.sr.sprites[d.sr.i].sector_no)
			{
				if(d.sr.x1 >= d.sr.x2 || d.sr.x2 < d.sr.tmp->sx1 || d.sr.x1 > d.sr.tmp->sx2)
				{
					if (++d.sr.tmp == (d.render.queue + MAX_SECTORS_RENDERED))
						d.sr.tmp = d.render.queue;
					continue ;
				}
				d.sr.begin_x = max(d.sr.x1, d.sr.tmp->sx1);
				d.sr.end_x = min(d.sr.x2, d.sr.tmp->sx2);		
				d.sr.win_x = d.sr.begin_x - 1;
				
				d.sr.z1a = WIN_HEIGHT / 2 - (int)((d.sr.z1 + d.sr.t1.y * d.player.angle_z) * d.sr.zscale1);
				d.sr.z1b = WIN_HEIGHT / 2 - (int)((d.sr.z2 + d.sr.t1.y * d.player.angle_z) * d.sr.zscale1);
				d.sr.z2a = WIN_HEIGHT / 2 - (int)((d.sr.z1 + d.sr.t2.y * d.player.angle_z) * d.sr.zscale2);
				d.sr.z2b = WIN_HEIGHT / 2 - (int)((d.sr.z2 + d.sr.t2.y  * d.player.angle_z) * d.sr.zscale2);

				while (++d.sr.win_x <= d.sr.end_x) // in wall 
				{
					d.sr.clmp_top = line_point(d.sr.tmp->ztop1, d.sr.tmp->ztop2, fpercent(d.sr.tmp->sx1, d.sr.tmp->sx2, d.sr.win_x));
					d.sr.clmp_top = max(d.sr.clmp_top, 0);
					d.sr.clmp_bot = line_point(d.sr.tmp->zbot1, d.sr.tmp->zbot2, fpercent(d.sr.tmp->sx1, d.sr.tmp->sx2, d.sr.win_x));
					d.sr.clmp_bot = min(d.sr.clmp_bot, WIN_HEIGHT - 1);

					d.sr.y = d.sr.t1.y;
					d.sr.za = (d.sr.win_x - d.sr.x1) * (d.sr.z2a - d.sr.z1a) / (d.sr.x2 - d.sr.x1) + d.sr.z1a;
					d.sr.zb = (d.sr.win_x - d.sr.x1) * (d.sr.z2b - d.sr.z1b) / (d.sr.x2 - d.sr.x1) + d.sr.z1b;
					// d.sr.c_za = max(d.sr.za, d.sr.clmp_top); // i bet i never use this
					// d.sr.c_zb = min(d.sr.zb, d.sr.clmp_bot);
					draw_line_of_sprite(&d.sr, d.texture.sprites->sprites[1], &d.render);
				}
			}
			if (++d.sr.tmp == (d.render.queue + MAX_SECTORS_RENDERED))
				d.sr.tmp = d.render.queue;
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
		render_sector(&d.render, d);
	}
	render_painting(d.sr, d);
	render_sprites(d.sr, d);
	return (0);
}
