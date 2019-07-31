/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 16:27:02 by apavlov           #+#    #+#             */
/*   Updated: 2019/07/29 16:27:03 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void set_pos(t_doom *d, t_sprite_render *sr)
{
	sr->time_from_loop_start += d->game.dt;
	if (sr->time_from_loop_start / 250 > sr->prev_frame / 250)
		if (++sr->pos > 2)
		{
			sr->pos = 0;
			sr->time_from_loop_start -= sr->prev_frame;
		}
	sr->prev_frame = sr->time_from_loop_start;
}

void	render_sprites(t_doom *d)
{
	t_sprite_render	sr;

	sr = d->sr;
	sr.c_sprt = d->map.num_sprites;

	set_pos(d, &d->sr);
	sr.i = -1;
	while (++sr.i < sr.c_sprt && sr.sprites[sr.i].coord.y > 0 && sr.sprites[sr.i].draw)
	{
		sr.surr = d->texture.sprites->sprites[sr.sprites[sr.i].text_no + sr.pos];
		sprite_vert_cal(&sr.t1, &sr.t2, sr.sprites + sr.i, d->player);

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

		sr.tmp = sr.begin;
		while (sr.tmp != d->render.tail)
		{
			if ((int)sr.tmp->num == sr.sprites[sr.i].sector_no)
			{
				if(sr.x1 >= sr.x2 || sr.x2 < sr.tmp->sx1 || sr.x1 > sr.tmp->sx2)
				{
					if (++sr.tmp == (d->render.queue + MAX_SECTORS_RENDERED))
						sr.tmp = d->render.queue;
					continue ;
				}
				sr.curr_sect = d->map.sectors + sr.sprites[sr.i].sector_no;
				sr.xscale1_p = HFOV / sr.v1.y;
				sr.xscale2_p = HFOV / sr.v2.y;
				sr.x1_p = WIN_WIDTH / 2 - (sr.v1.x * sr.xscale1_p);
				sr.x2_p = WIN_WIDTH / 2 - (sr.v2.x * sr.xscale2_p);

				sr.begin_x = max(sr.x1, sr.tmp->sx1);
				sr.end_x = min(sr.x2, sr.tmp->sx2);		
				sr.win_x = sr.begin_x;
				
				sr.z1a = WIN_HEIGHT / 2 - (int)((sr.t1.z + sr.t1.y * d->player.angle_z) * sr.zscale1);
				sr.z1b = WIN_HEIGHT / 2 - (int)((sr.t2.z + sr.t1.y * d->player.angle_z) * sr.zscale1);
				sr.z2a = WIN_HEIGHT / 2 - (int)((sr.t1.z + sr.t2.y * d->player.angle_z) * sr.zscale2);
				sr.z2b = WIN_HEIGHT / 2 - (int)((sr.t2.z + sr.t2.y  * d->player.angle_z) * sr.zscale2);

				sr.d_percent = 1.0 / (sr.x2_p - sr.x1_p);
				sr.percent = (sr.win_x - sr.x1_p) * sr.d_percent;
				sr.y = sr.t1.y;

				sr.x_text = (sr.surr->w * sr.percent);
				sr.d_x_text = sr.surr->w * sr.d_percent;

				sr.d_za = (sr.z2a - sr.z1a) / (sr.x2 - sr.x1);
				sr.d_zb = (sr.z2b - sr.z1b) / (sr.x2 - sr.x1);
				sr.za = (sr.win_x - sr.x1) * sr.d_za + sr.z1a;
				sr.zb = (sr.win_x - sr.x1) * sr.d_zb + sr.z1b;
				
				sr.percent_of_wall = fpercent(sr.tmp->sx1, sr.tmp->sx2, sr.win_x);
				sr.d_percent_of_wall = 1.0 / ((float)sr.tmp->sx2 - sr.tmp->sx1);

				while (sr.win_x <= sr.end_x)
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