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
//apavlov test commit
void	vertical_line(int x, int y1, int y2, t_render *r, int top, int mid, int bot)
{
	y1 = clamp(y1, 0, WIN_HEIGHT - 1);
	y2 = clamp(y2, 0, WIN_HEIGHT - 1);
	while (y1 < y2)
		r->pix[y1++ * WIN_WIDTH + x] = mid;
}

void	prepare_to_rendering(t_render *r, t_doom d)
{
	r->now.num = d.player.sector;
	r->sect = d.map.sectors + r->now.num; //&d.map.sectors[r->now.num];
	r->now.sx1 = 0;
	r->now.sx2 = WIN_WIDTH - 1;
	r->pcos = d.player.anglecos;
	r->psin = d.player.anglesin;
	ft_memset(r->ztop, 0, WIN_WIDTH);
	ft_memset(r->zbottom, WIN_HEIGHT - 1, WIN_WIDTH);
	r->pix = (Uint32*)d.sdl.surface->pixels;
}

void	render_sector(t_render r, t_doom d)
{
	int i;
	int	x;
	t_plane	cplane = r.sect->ceil_plane;
	t_plane	fplane = r.sect->floor_plane;
	t_plane ncplane;
	t_plane nfplane;
	r.now.num = d.player.sector;
	r.now.sx1 = 0;
	r.now.sx2 = WIN_WIDTH - 1;
	ft_memset(r.ztop, 0, WIN_WIDTH * sizeof(int));
	ft_memset(r.zbottom, WIN_HEIGHT - 1, WIN_WIDTH * sizeof(int));
	r.sect = d.map.sectors + r.now.num; //&d.map.sectors[r->now.num];


	i = -1;
	while (++i < r.sect->num_vert)
	{
		r.t1.x = r.sect->vert[i].x - d.player.coord.x;
		r.t1.y = r.sect->vert[i].y - d.player.coord.y;
		r.t2.x = r.sect->vert[i + 1].x - d.player.coord.x;
		r.t2.y = r.sect->vert[i + 1].y - d.player.coord.y;
		r.v1.x = r.t1.x;
		r.v1.y = r.t1.y;
		r.v2.x = r.t2.x;
		r.v2.y = r.t2.y;
		rotate_vertex_xy(&r.t1, r.psin, r.pcos);
		rotate_vertex_xy(&r.t2, r.psin, r.pcos);

		if (r.t1.y <= NEAR_Y && r.t2.y <= NEAR_Y)
			continue ;
		if (r.t1.y <= NEAR_Y || r.t2.y <= NEAR_Y)
		{
			t_vertex i1 = intersect(r.t1, r.t2, (t_vertex){-NEAR_X, NEAR_Y}, (t_vertex){-FAR_X, FAR_Y});
			t_vertex i2 = intersect(r.t1, r.t2,  (t_vertex){NEAR_X, NEAR_Y},  (t_vertex){FAR_X, FAR_Y});
			if(r.t1.y < 0)
			{ 
				if(i1.y > 0)
				{
					r.t1.x = i1.x;
					r.t1.y = i1.y;
				}
				else
				{
					r.t1.x = i2.x;
					r.t1.y = i2.y;
 				}
			}
			if(r.t2.y < 0)
			{
				if(i1.y > 0)
				{
					r.t2.x = i1.x;
					r.t2.y = i1.y;
				}
				else
				{
					r.t2.x = i2.x;
					r.t2.y = i2.y;
				} 
			}
		}
			
		r.xscale1 = HFOV / r.t1.y;
		r.xscale2 = HFOV / r.t2.y;
		r.zscale1 = VFOV / r.t1.y; //division by 0
		r.zscale2 = VFOV / r.t2.y;
		//printf("%f %f %f %f\n", r.t1.x, r.t1.y, r.t2.x, r.t2.y);
		r.x1 = WIN_WIDTH / 2 - (int)(r.t1.x * r.xscale1);
		r.x2 = WIN_WIDTH / 2 - (int)(r.t2.x * r.xscale2);

		if(r.x1 >= r.x2 || r.x2 < r.now.sx1 || r.x1 > r.now.sx2)
			continue ;
		if (r.sect->neighbors[i] >= 0)
		{
			ncplane = d.map.sectors[(int)r.sect->neighbors[i]].ceil_plane;
			nfplane = d.map.sectors[(int)r.sect->neighbors[i]].floor_plane;
		}
		r.begin_x = max(r.x1, r.now.sx1);
		r.end_x = min(r.x2, r.now.sx2);
		x = r.begin_x - 1;
		//printf("%i %i\n", r.begin_x, r.end_x);
		while (++x <= r.end_x)
		{
			float perc = percent(r.x1 , r.x2 , x);
			float lp_x = line_point(r.sect->vert[i].x, r.sect->vert[i + 1].x, perc);
			float lp_y = line_point(r.sect->vert[i].y, r.sect->vert[i + 1].y, perc);
			r.zceil  = get_z(cplane, lp_x, lp_y) - d.player.coord.z;
			r.zfloor = get_z(fplane, lp_x, lp_y) - d.player.coord.z;

			r.z1a  = WIN_HEIGHT / 2 - (int)((r.zceil + r.t1.y * d.player.angle_z) * r.zscale1);
			r.z1b = WIN_HEIGHT / 2 - (int)((r.zfloor + r.t1.y * d.player.angle_z) * r.zscale1);
			r.z2a  = WIN_HEIGHT / 2 - (int)((r.zceil + r.t2.y * d.player.angle_z) * r.zscale2);
			r.z2b = WIN_HEIGHT / 2 - (int)((r.zfloor + r.t2.y  * d.player.angle_z) * r.zscale2);

			r.y = (x - r.x1) * (r.t1.y - r.t1.y) / (r.x2 - r.x1) + r.t1.y;
			r.za = (x - r.x1) * (r.z2a - r.z1a) / (r.x2 - r.x1) + r.z1a;
			r.za = clamp(r.za, r.ztop[x], r.zbottom[x]);
			r.zb = (x - r.x1) * (r.z2b - r.z1b) / (r.x2 - r.x1) + r.z1b;
			r.zb = clamp(r.zb, r.ztop[x], r.zbottom[x]);

			vertical_line(x, r.ztop[x], r.za - 1, &r, 0x111111 ,0x222222,0x111111);
			vertical_line(x, r.zb + 1, r.zbottom[x], &r, 0x0000FF,0x0000AA,0x0000FF);
			if(r.sect->neighbors[i] >= 0)
			{
				r.nzceil = get_z(ncplane, lp_x, lp_y) - d.player.coord.z;
				r.nzfloor = get_z(nfplane, lp_x, lp_y) - d.player.coord.z;
				r.nz1a = WIN_HEIGHT / 2 - (int)((r.nzceil + r.t1.y * d.player.angle_z) * r.zscale1);
				r.nz1b = WIN_HEIGHT / 2 - (int)((r.nzfloor + r.t1.y * d.player.angle_z) * r.zscale1);
				r.nz2a = WIN_HEIGHT / 2 - (int)((r.nzceil + r.t2.y * d.player.angle_z) * r.zscale2);
				r.nz2b = WIN_HEIGHT / 2 - (int)((r.nzfloor + r.t2.y * d.player.angle_z) * r.zscale2);

				r.nza = (x - r.x1) * (r.nz2a - r.nz1a) / (r.x2 - r.x1) + r.nz1a;
				r.nza = clamp(r.nza, r.ztop[x], r.zbottom[x]);
				r.nzb = (x - r.x1) * (r.nz2b - r.nz1b) / (r.x2 - r.x1) + r.nz1b;
				r.nzb = clamp(r.nzb, r.ztop[x], r.zbottom[x]);

				vertical_line(x, r.za, r.nza - 1, &r, 0, 0x0F0F0F, 0);
				r.ztop[x] = clamp(max(r.za, r.nza), r.ztop[x], WIN_HEIGHT - 1);
				vertical_line(x, r.nzb + 1, r.zb, &r, 0, 0xAFBF0F, 0);
				r.zbottom[x] = clamp(min(r.zb, r.nzb), 0, r.zbottom[x]);
			}
			else
				vertical_line(x, r.za, r.zb, &r, 0, 0xAAAAAA, 0);
		}
	}
}

int		draw_screen(t_doom doom)
{
	t_render	r;

	prepare_to_rendering(&r, doom);
	bzero(r.pix, WIN_HEIGHT * WIN_WIDTH * sizeof(Uint32));
	render_sector(r, doom);
	SDL_UpdateWindowSurface(doom.sdl.window);
	SDL_Delay(10);
	return (0);
}

