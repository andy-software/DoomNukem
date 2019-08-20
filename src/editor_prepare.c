/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_prepare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanylch <mdanylch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 21:08:35 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/20 22:35:09 by mdanylch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static	void	init_map_sector_line(t_doom *doom, int j, int l)
{
	doom->map.sectors[j].lines = (t_line*)malloc(sizeof(t_line) * MAX_VERT);
	while (++l < MAX_VERT)
	{
		doom->map.sectors[j].lines[l].wall = 1;
		doom->map.sectors[j].lines[l].top = 1;
		doom->map.sectors[j].lines[l].bot = 1;
		doom->map.sectors[j].lines[l].x_w_scale = 2;
		doom->map.sectors[j].lines[l].x_b_scale = 2;
		doom->map.sectors[j].lines[l].x_t_scale = 2;
		doom->map.sectors[j].lines[l].x_w_shift = 50;
		doom->map.sectors[j].lines[l].x_b_shift = 50;
		doom->map.sectors[j].lines[l].x_t_shift = 50;
		doom->map.sectors[j].lines[l].y_w_scale = 1;
		doom->map.sectors[j].lines[l].y_b_scale = 1;
		doom->map.sectors[j].lines[l].y_t_scale = 1;
	}
}

static	void	init_map_sector(t_doom *doom, int j)
{
	doom->map.sectors = (t_sector*)malloc(sizeof(t_sector) * MAX_SECTORS);
	while (++j < MAX_SECTORS)
	{
		doom->map.sectors[j].light_lvl = 1;
		doom->map.sectors[j].num = j;
		doom->map.sectors[j].ceil_plane.c = 1;
		doom->map.sectors[j].ceil_plane.h = -80;
		doom->map.sectors[j].floor_plane.c = 1;
		doom->map.sectors[j].floor_plane.h = -10;
		doom->map.sectors[j].ceil_tex = 4;
		doom->map.sectors[j].floor_tex = 4;
		doom->map.sectors[j].x_c_scale = 1;
		doom->map.sectors[j].y_c_scale = 1;
		doom->map.sectors[j].x_f_scale = 1.0 / 10;
		doom->map.sectors[j].y_f_scale = 1.0 / 10;
		doom->map.sectors[j].render_ceil = 1;
		init_map_sector_line(doom, j, -1);
	}
}

static	void	init_map_sprites(t_doom *doom, int j)
{
	while (++j < MAX_SPRITES_COUNT)
	{
		doom->map.sprites[j].spr_num = j;
		doom->map.sprites[j].coord = (t_vector){40, 40, 0};
		doom->map.sprites[j].width = 8;
		doom->map.sprites[j].end_z = 13;
		doom->map.sprites[j].mob = 1;
		doom->map.sprites[j].draw = 1;
		doom->map.sprites[j].live = 1;
		doom->map.sprites[j].angle = M_PI / 4;
		doom->map.sprites[j].anglesin = sin(doom->map.sprites[j].angle);
		doom->map.sprites[j].anglecos = cos(doom->map.sprites[j].angle);
		doom->map.sprites[j].move_speed = 0.03;
		doom->map.sprites[j].own_moves = 1;
		doom->map.sprites[j].vision_forward = 5;
		doom->map.sprites[j].vision_backward = -3;
		doom->map.sprites[j].hp = 20;// FIX
		// doom->map.sprites[j].speed = 20;
		doom->map.sprites[j].num_sheet = 6;
		// doom->map.sprites[j].speed = 20;
	}
}

static	void	init_map_paint(t_doom *doom, int j)
{
	while (++j < MAX_PAINTINGS)
	{
		doom->map.paint[j].v1.z = 40;
		doom->map.paint[j].v2.z = 20;
		doom->map.paint[j].key = 1;
		doom->map.paint[j].draw = 1;
		doom->map.paint[j].speed = 5;
		doom->map.paint[j].high_point = -40;
		doom->map.paint[j].low_point = -10;
		doom->map.paint[j].num_sheet = 3;
	}
}

void			ft_prepare_read(t_doom *doom)
{
	ft_bzero(doom, sizeof(t_doom));
	init_map_sector(doom, -1);
	init_map_sprites(doom, -1);
	init_map_paint(doom, -1);
}
