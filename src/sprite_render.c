/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 16:27:02 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/06 19:44:55 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void			set_pos(t_doom *d, t_sprite_render *sr)
{
	sr->time_from_loop_start += d->game.dt;
	if (sr->time_from_loop_start / 250 > sr->prev_frame / 250)
		++sr->pos;
	sr->prev_frame = sr->time_from_loop_start;
}

SDL_Surface		*choose_texture_for_mob(t_sprite_sheet *sheet, \
									t_sprite_render *sr, int i, t_doom *d)
{
	int			pos;

	if (sr->sprites[i].mob && sr->sprites[i].live)
		pos = sr->sprites[i].text_no + sr->pos % sheet->w;
	else if (sr->sprites[i].mob && !sr->sprites[i].live)
	{
		pos = sr->sprites[i].text_no + MIN((d->ui.prevTime - \
			sr->sprites[i].death_time) / 150, (Uint32)(sheet->w - 1));
		if (pos == sr->sprites[i].text_no + sheet->w - 1)
		{
			d->map.sprites[sr->sprites[i].spr_num].draw = 0;
			if (d->map.sprites[sr->sprites[i].spr_num].num_sheet == 8) //max zaberi che z vidsi
			{
				d->map.sprites[d->sr.sprites[i].spr_num].text_no = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].num_sheet = 3;
				d->map.sprites[d->sr.sprites[i].spr_num].width = 0.5;
				d->map.sprites[d->sr.sprites[i].spr_num].start_z = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].end_z = 2.5;
				d->map.sprites[d->sr.sprites[i].spr_num].mob = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].angle = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].anglecos = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].anglesin = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].own_moves = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].move_speed = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].draw = 1;
				d->map.sprites[d->sr.sprites[i].spr_num].vision_forward = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].vision_backward = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].key = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].changes = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].key_state = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].num_of_sound = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].event_num = 0;
				d->map.sprites[d->sr.sprites[i].spr_num].pick = 1;
			}
		}
		d->map.sprites[sr->sprites[i].spr_num].end_z -= \
				d->map.sprites[sr->sprites[i].spr_num].start_z;
		d->map.sprites[sr->sprites[i].spr_num].start_z = 0;
	}
	else
		pos = sr->sprites[i].text_no;
	return (sheet->sprites[pos]);
}

void	render_sprites(t_doom *d)
{
	t_sprite_render	sr;
	t_sprite_sheet	*sheet;

	sr = d->sr;
	sr.c_sprt = d->map.num_sprites;
	set_pos(d, &d->sr);
	sr.i = -1;
	while (++sr.i < sr.c_sprt && sr.sprites[sr.i].coord.y > 0)
	{
		if (sr.sprites[sr.i].draw == 0)
			continue ;
		sheet = d->texture.sprt + sr.sprites[sr.i].num_sheet;
		sr.surr = choose_texture_for_mob(sheet, &sr, sr.i, d);
		sprite_vert_cal(&sr.t1, &sr.t2, sr.sprites + sr.i, d->player);
		if (sprite_render_cliping(&sr))
			continue ;
		sr.xscale1 = HFOV / sr.t1.y;
		sr.xscale2 = HFOV / sr.t2.y;
		sr.zscale1 = VFOV / sr.t1.y;
		sr.zscale2 = VFOV / sr.t2.y;
		sr.x1 = WIN_WIDTH / 2 - (sr.t1.x * sr.xscale1);
		sr.x2 = WIN_WIDTH / 2 - (sr.t2.x * sr.xscale2);
		sprite_render_cycle(&sr, d);
	}
}
