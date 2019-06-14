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
	y1 = clamp(y1, 0, WIN_HEIGHT - 1);
	y2 = clamp(y2, 0, WIN_HEIGHT - 1);
	while (y1 < y2)
		r->pix[y1++ * WIN_WIDTH + x] = color;
}


void	prepare_to_rendering(t_render *r, t_doom d)
{
	r->now.num = d.player.sector;
	r->sect = d.map.sectors + r->now.num; //&d.map.sectors[r->now.num];
	r->now.sx1 = 0;
	r->now.sx2 = WIN_WIDTH - 1;
	r->pcos = d.player.anglecos;
	r->psin = d.player.anglesin;
	r->pix = (Uint32*)d.sdl.surface->pixels;
	r->head = r->queue;
	r->tail = r->queue;
	ft_memset(r->rendered_sectors, 0, sizeof(int) * d.map.num_sect);
	ft_memset(r->ztop, 0, WIN_WIDTH * sizeof(int));
	ft_memset(r->zbottom, WIN_HEIGHT - 1, WIN_WIDTH * sizeof(int));
	ft_bzero(r->pix, WIN_HEIGHT * WIN_WIDTH * sizeof(Uint32));
}

void	render_sector(t_render *r, t_doom d)
{
	r->rendered_sectors[r->now.num]++;
	r->sect = d.map.sectors + r->now.num; //&d.map.sectors[r->now.num];
	r->cplane = r->sect->ceil_plane;
	r->fplane = r->sect->floor_plane;
	
	r->wall_num = -1;
	while (++r->wall_num < r->sect->num_vert) // wall 
	{
		r->t1.x = r->sect->vert[r->wall_num].x - d.player.coord.x;
		r->t1.y = r->sect->vert[r->wall_num].y - d.player.coord.y;
		r->t2.x = r->sect->vert[r->wall_num + 1].x - d.player.coord.x;
		r->t2.y = r->sect->vert[r->wall_num + 1].y - d.player.coord.y;
		r->v1.x = r->t1.x;
		r->v1.y = r->t1.y;
		r->v2.x = r->t2.x;
		r->v2.y = r->t2.y;
		r->tx1 = r->t1.x * r->psin - r->t1.y *r->pcos;
		r->tz1 = r->t1.x *r->pcos + r->t1.y * r->psin;
    	r->tx2 = r->t2.x * r->psin - r->t2.y *r->pcos;
		r->tz2 = r->t2.x * r->pcos + r->t2.y * r->psin;
		rotate_vertex_xy(&r->t1, r->psin, r->pcos);
		rotate_vertex_xy(&r->t2, r->psin, r->pcos);
		int bool_t1 = r->t1.y < fabs(r->t1.x) / 4; //few same calculation
		int bool_t2 = r->t2.y < fabs(r->t2.x) / 4; //few same calculation
		// if (bool_t1 && bool_t2)
		// 	continue ; 
		if (bool_t1 || bool_t2)
		{
			t_vertex i1 = intersect(r->t1, r->t2, (t_vertex){0, 0}, (t_vertex){-4, 1});
			t_vertex i2 = intersect(r->t1, r->t2, (t_vertex){0, 0}, (t_vertex){4, 1});	
			if (bool_t1)
			{
				if(i1.y > 0)
					r->t1 = i1;
				else
					r->t1 = i2;
			}
			if (bool_t2)
			{
				if (i1.y > 0)
					r->t2 = i1;
				else
					r->t2 = i2;
			}
		}
		r->xscale1 = HFOV / r->t1.y;
		r->xscale2 = HFOV / r->t2.y;
		r->zscale1 = VFOV / r->t1.y;
		r->zscale2 = VFOV / r->t2.y;

		r->x1 = WIN_WIDTH / 2 - (r->t1.x * r->xscale1);
		r->x2 = WIN_WIDTH / 2 - (r->t2.x * r->xscale2);

		if(r->x1 >= r->x2 || r->x2 < r->now.sx1 || r->x1 > r->now.sx2)
			continue ;
		r->neighbor = r->sect->neighbors[r->wall_num];
		if (r->neighbor >= 0)
		{
			r->ncplane = d.map.sectors[(int)r->neighbor].ceil_plane;
			r->nfplane = d.map.sectors[(int)r->neighbor].floor_plane;
		}

		r->begin_x = max(r->x1, r->now.sx1);
		r->end_x = min(r->x2, r->now.sx2);
		r->win_x = r->begin_x - 1;
		
		while (++r->win_x <= r->end_x) // in wall
		{
			float perc = percent(r->x1 , r->x2 , r->win_x);

			//calculate current x on the map from vision of player dont use it w/o apavlov
			// float cur_scale_x = line_point(r->xscale1, r->xscale2, perc);
			// float curr_map_x = (-r->x1 + WIN_WIDTH / 2 - perc * (r->x2 - r->x1)) / (cur_scale_x); // hehe try to understand
			// float perc_x = fpercent(r->sect->vert[r->wall_num].x, r->sect->vert[r->wall_num + 1].x, curr_map_x);

			float lp_x = line_point(r->sect->vert[r->wall_num].x, r->sect->vert[r->wall_num + 1].x, perc);
			float lp_y = line_point(r->sect->vert[r->wall_num].y, r->sect->vert[r->wall_num + 1].y, perc);
			r->zceil  = get_z(r->cplane, lp_x, lp_y) - d.player.coord.z;
			r->zfloor = get_z(r->fplane, lp_x, lp_y) - d.player.coord.z;

			r->z1a  = WIN_HEIGHT / 2 - (int)((r->zceil + r->t1.y * d.player.angle_z) * r->zscale1);
			r->z1b = WIN_HEIGHT / 2 - (int)((r->zfloor + r->t1.y * d.player.angle_z) * r->zscale1);
			r->z2a  = WIN_HEIGHT / 2 - (int)((r->zceil + r->t2.y * d.player.angle_z) * r->zscale2);
			r->z2b = WIN_HEIGHT / 2 - (int)((r->zfloor + r->t2.y  * d.player.angle_z) * r->zscale2);
			r->y = (r->win_x - r->x1) * (r->t2.y - r->t1.y) / (r->x2 - r->x1) + r->t1.y;
			r->za = (r->win_x - r->x1) * (r->z2a - r->z1a) / (r->x2 - r->x1) + r->z1a;
			r->zb = (r->win_x - r->x1) * (r->z2b - r->z1b) / (r->x2 - r->x1) + r->z1b;
			r->c_za = clamp(r->za, r->ztop[r->win_x], r->zbottom[r->win_x]);
			r->c_zb = clamp(r->zb, r->ztop[r->win_x], r->zbottom[r->win_x]);
			vertical_line(r->win_x, r->c_zb + 1, r->zbottom[r->win_x], r, 0xFFFF00); //floor
			//floorline_draw(d.player.coord.x, d.player.coord.y, 0xFFF000, 0xFFFF00, d);
			//vertical_line(r->win_x, r->ztop[r->win_x], r->c_za - 1, r, 0x222222); // cell

			if(r->neighbor >= 0)
			{
				r->nzceil = get_z(r->ncplane, lp_x, lp_y) - d.player.coord.z;
				r->nzfloor = get_z(r->nfplane, lp_x, lp_y) - d.player.coord.z;
				r->nz1a = WIN_HEIGHT / 2 - (int)((r->nzceil + r->t1.y * d.player.angle_z) * r->zscale1);
				r->nz1b = WIN_HEIGHT / 2 - (int)((r->nzfloor + r->t1.y * d.player.angle_z) * r->zscale1);
				r->nz2a = WIN_HEIGHT / 2 - (int)((r->nzceil + r->t2.y * d.player.angle_z) * r->zscale2);
				r->nz2b = WIN_HEIGHT / 2 - (int)((r->nzfloor + r->t2.y * d.player.angle_z) * r->zscale2);

				r->nza = (r->win_x - r->x1) * (r->nz2a - r->nz1a) / (r->x2 - r->x1) + r->nz1a;
				r->nza = clamp(r->nza, r->ztop[r->win_x], r->zbottom[r->win_x]);
				r->nzb = (r->win_x - r->x1) * (r->nz2b - r->nz1b) / (r->x2 - r->x1) + r->nz1b;
				r->nzb = clamp(r->nzb, r->ztop[r->win_x], r->zbottom[r->win_x]);

				// vertical_line(r->win_x, r->c_za, r->nza - 1, r, 0x0F0F0F); // down to sector
				//textline_draw(r->za, r->nza - 1, r, &d.texture, d);
				r->ztop[r->win_x] = clamp(max(r->c_za, r->nza), r->ztop[r->win_x], WIN_HEIGHT - 1);
				// vertical_line(r->win_x, r->nzb + 1, r->c_zb, r, 0xFF0000); // up to sector
				//textline_draw(r->nzb + 1, r->zb, r, &d.texture, d);
				r->zbottom[r->win_x] = clamp(min(r->c_zb, r->nzb), 0, r->zbottom[r->win_x]);
			}
			else
				//vertical_line(r->win_x, r->c_za, r->c_zb, (struct Scaler)Scaler_Init(r->za,r->c_za,r->zb, 0, WIN_HEIGHT - 1), (unsigned)txtx + 130, &d.texture, r);
				// printf("%d\n", r->sect->lines[r->wall_num].full);
				textline_draw(r->c_za, r->c_zb, r, &d.texture, d, lp_x);
		}
		if(r->neighbor >= 0 && r->x2 >= r->x1 && (r->head + MAX_SECTORS_RENDERED + 1 - r->tail) % MAX_SECTORS_RENDERED)
		{
			*r->head = (t_rend_sector) {r->neighbor, r->begin_x, r->end_x};
			if(++r->head == (r->queue + MAX_SECTORS_RENDERED))
				r->head = r->queue;
		}
	}
	//printf("Rendered %r->wall_num now in %r->wall_num\n", r->now.num, d.player.sector);
	++r->rendered_sectors[r->now.num];
}

void	textline_draw(int y1, int y2, t_render *r, t_texture *t, t_doom d, float lp_x)
{
	// t->x_point = UnFix(Fix((double)((r->win_x - r->x1)) / (r->x2 - r->x1)) * t->x_split);
	// t->x_text = (int)UnFix(Fix(t->x_point - (int)t->x_point) * WALL_TEXT_W);
	t->x_text = (0 * ((r->x2 - r->win_x) * r->t2.y) + ((WALL_TEXT_W * t->x_split - 1) *
		((r->win_x - r->x1) * r->t1.y))) / ((r->x2 - r->win_x) * r->t2.y + (r->win_x - r->x1) * r->t1.y);
	r->win_y = clamp(y1, 0, WIN_HEIGHT - 1);
	t->wall_end = min(y2, WIN_HEIGHT - 1);
	r->fog_perc = UnFix(Fix(r->y) / r->fog_distance);
	while(r->win_y <= t->wall_end)
	{
		t->y_point = UnFix(Fix((double)(r->win_y - r->za) / (r->zb - r->za)) * t->y_split / 2);
		t->y_text = (int)UnFix(Fix(t->y_point - (int)t->y_point) * WALL_TEXT_H);
		// t->y_text = (0 * ((r->zb - r->win_y)) + ((WALL_TEXT_H) *
		// ((r->win_y - r->za)))) / ((r->zb - r->win_y) + (r->win_y - r->za));
		t->color = pix_from_text(t->wall_tex[r->sect->lines[r->wall_num].full], t->x_text, t->y_text);
		if (t->color != 0)
			r->pix[r->win_y * WIN_WIDTH + r->win_x] = color_mix(t->color, \
				0x000000, (r->fog_perc > 1 ? 1 : r->fog_perc));
		r->win_y++;
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


int		draw_screen(t_doom doom)
{
	*doom.render.head = (t_rend_sector) {doom.player.sector, 0, WIN_WIDTH - 1};
	if (++doom.render.head == doom.render.queue + MAX_SECTORS_RENDERED)
	 	doom.render.head = doom.render.queue;
	while (doom.render.head != doom.render.tail)
	{
		doom.render.now = *doom.render.tail;
		if (++doom.render.tail == (doom.render.queue + MAX_SECTORS_RENDERED))
			doom.render.tail = doom.render.queue;
		if (doom.render.rendered_sectors[doom.render.now.num] & (MAX_SECTORS_RENDERED + 1))
			continue ;
		render_sector(&doom.render, doom);
	}
	// SDL_UpdateWindowSurface(doom.sdl.window);
	// SDL_Delay(10);
	return (0);
}
