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
	i = -1;
	while (++i < MAX_SECTORS_RENDERED)
		r->queue[i] = (t_rend_sector){-1, 0, WIN_WIDTH - 1, 0, 0, WIN_HEIGHT - 1, WIN_HEIGHT - 1};
	r->head = r->queue;
	r->tail = r->queue;
	ft_memset(r->rendered_sectors, 0, sizeof(int) * d.map.num_sect);
	ft_memset(r->ztop, 0, WIN_WIDTH * sizeof(int));
	ft_memset(r->zbottom, WIN_HEIGHT - 1, WIN_WIDTH * sizeof(int));
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
		
		r->t1_1_line = r->t1.y < r->t1.x / 4; //is dot 1 lower then line y = x / 4
		r->t1_2_line = r->t1.y < -r->t1.x / 4; //is dot 1 lower then line y = -x / 4
		r->t2_1_line = r->t2.y < r->t2.x / 4; //is dot 2 lower then line y = x / 4
		r->t2_2_line = r->t2.y < -r->t2.x / 4; //is dot 2 lower then line y = -x / 4
		if (r->t1.y < 0 && r->t2.y < 0)
			continue ;
		if ((r->t1_1_line && r->t2_1_line) || (r->t1_2_line && r->t2_2_line))
			continue ;
		if (r->t1_1_line || r->t1_2_line || r->t2_1_line || r->t2_2_line)
		{
			r->i1 = intersect(r->t1, r->t2, (t_vertex){0, 0}, (t_vertex){4, 1});	
			r->i2 = intersect(r->t1, r->t2, (t_vertex){0, 0}, (t_vertex){-4, 1});
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

		r->z1a = WIN_HEIGHT / 2 - (int)((r->zceil1 + r->t1.y * d.player.angle_z) * r->zscale1);
		r->z1b = WIN_HEIGHT / 2 - (int)((r->zfloor1 + r->t1.y * d.player.angle_z) * r->zscale1);
		r->z2a  = WIN_HEIGHT / 2 - (int)((r->zceil2 + r->t2.y * d.player.angle_z) * r->zscale2);
		r->z2b = WIN_HEIGHT / 2 - (int)((r->zfloor2 + r->t2.y  * d.player.angle_z) * r->zscale2);
		float	kt = (r->t2.y - r->t1.y) / (r->x2 - r->x1);
		float	kza = (r->z2a - r->z1a) / (r->x2 - r->x1);
		float	kzb = (r->z2b - r->z1b) / (r->x2 - r->x1);
		float	nkza = (r->nz2a - r->nz1a) / (r->x2 - r->x1);
		float	nkzb = (r->nz2b - r->nz1b) / (r->x2 - r->x1);
		while (++r->win_x <= r->end_x) // in wall 
		{
			r->y = (r->win_x - r->x1) * kt + r->t1.y;
			r->za = (r->win_x - r->x1) * kza + r->z1a;
			r->zb = (r->win_x - r->x1) * kzb + r->z1b;
			r->c_za = clamp(r->za, r->ztop[r->win_x], r->zbottom[r->win_x]);
			r->c_zb = clamp(r->zb, r->ztop[r->win_x], r->zbottom[r->win_x]);
			vertical_line(r->win_x, r->c_zb + 1, r->zbottom[r->win_x], r, 0xFFFF00); //floor
			//floorline_draw(d.player.coord.x, d.player.coord.y, 0xFFF000, 0xFFFF00, d);
			vertical_line(r->win_x, r->ztop[r->win_x], r->c_za - 1, r, 0x222222); // cell

			if(r->neighbor >= 0)
			{
				r->nza = (r->win_x - r->x1) * nkza + r->nz1a;
				r->c_nza = clamp(r->nza, r->ztop[r->win_x], r->zbottom[r->win_x]);
				r->nzb = (r->win_x - r->x1) * nkzb + r->nz1b;
				r->c_nzb = clamp(r->nzb, r->ztop[r->win_x], r->zbottom[r->win_x]);

				//vertical_line(r->win_x, r->c_za, r->nza - 1, r, 0x0F0F0F); // down to sector
				textline_draw(r->za, r->nza - 1, r, &d.texture);
				r->ztop[r->win_x] = clamp(max(r->c_za, r->c_nza), r->ztop[r->win_x], WIN_HEIGHT - 1);
				//vertical_line(r->win_x, r->nzb + 1, r->c_zb, r, 0xFF0000); // up to sector
				textline_draw(r->nzb + 1, r->zb, r, &d.texture); // Yo u dont need doom.texture if u have doom already
				r->zbottom[r->win_x] = clamp(min(r->c_zb, r->c_nzb), 0, r->zbottom[r->win_x]);
			}
			else
			{
				//vertical_line(r->win_x, r->c_za, r->c_zb, r, 0xAAAAAA);
				textline_draw(r->c_za, r->c_zb, r, &d.texture);
			}		
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

void	textline_draw(int y1, int y2, t_render *r, t_texture *t)
{
	t->xscale1 = HFOV / r->v1.y;
	t->xscale2 = HFOV / r->v2.y;
	t->x1 = WIN_WIDTH / 2 - (r->v1.x * t->xscale1);
	t->x2 = WIN_WIDTH / 2 - (r->v2.x * t->xscale2);

	t->percent = (r->win_x - t->x1) / (t->x2 - t->x1);
	t->x_text = (t->wall_tex[3]->w * t->percent) / ((1 - t->percent) * r->v2.y / r->v1.y + t->percent); // x_tex = a * w / ((1 - a) * z2 / z1 + a)
	r->win_y = clamp(y1, 0, WIN_HEIGHT - 1);
	t->wall_end = min(y2, WIN_HEIGHT - 1);
	t->y_point = (r->zb == r->za) ? 0 : (double)(r->win_y - r->za) / (r->zb - r->za);
	t->dy_point = (r->zb == r->za) ? 0 : 1.0 / (r->zb - r->za); // derivation of y_point
	while(r->win_y < t->wall_end)
	{
		t->y_text = t->y_point * t->wall_tex[3]->h;
		t->color = pix_from_text(t->wall_tex[3], t->x_text, t->y_text);
		if (t->color != 0)
			r->pix[r->win_y * WIN_WIDTH + r->win_x] = t->color;
		r->win_y++;
		t->y_point += t->dy_point;
	}
}


// void	floorline_draw(int y1, int y2, t_render *r, t_texture *t)
// {
// 	// printf("x1:%d\n", r->x1);
// 	t->x_point = ((double)((r->win_x - r->begin_x) / (double)(r->end_x - r->begin_x)) * t->x_split);
// 	t->x_text = (int)UnFix(Fix(t->x_point - (int)t->x_point) * WALL_TEXT_W);
// 	r->win_y = clamp(y1, 0, WIN_HEIGHT - 1);
// 	t->wall_end = min(y2, WIN_HEIGHT - 1);
// 	r->fog_perc = UnFix(Fix(r->y) / r->fog_distance);
// 	while(r->win_y < t->wall_end)
// 	{
// 		t->y_point = UnFix(Fix((double)(r->win_y - r->y) / (WIN_HEIGHT - r->y)) * t->y_split);
// 		t->y_text = (int)UnFix(Fix(t->y_point - (int)t->y_point) * WALL_TEXT_H);
// 		t->color = pix_from_text(t->wall_tex[0], t->x_text, t->y_text);
// 		if (t->color != 0)
// 		{
// 			//t->color = color_mix(t->color, 0x000000, (r->fog_perc > 1 ? 1 : r->fog_perc));
// 			r->pix[r->win_y * WIN_WIDTH + r->win_x] = t->color;
// 		}
// 		r->win_y++;
// 	}
// }
void	floorline_draw(int x, int y, int new_col, int old_col, t_doom d)
{ 
    // check current pixel is old_color or not 
    if (pix_from_text(d.sdl.surface, x, y) == old_col) { 
  
        // put new pixel with new color
		d.render.pix[y * WIN_WIDTH + x] = new_col;
  
        // recursive call for bottom pixel fill 
        floorline_draw(x + 1, y, new_col, old_col, d); 
  
        // recursive call for top pixel fill
        floorline_draw(x - 1, y, new_col, old_col, d); 
  
        // recursive call for right pixel fill
       floorline_draw(x, y + 1, new_col, old_col, d); 
  
        // recursive call for left pixel fill
        floorline_draw(x, y - 1, new_col, old_col, d);
    } 
} 

void	draw_line_of_sprite(t_sprite_render *sr, SDL_Surface *sprtext, t_render *render) //copyrighted from wall texture drawing
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
