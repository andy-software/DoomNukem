/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST_MUST_BE_ONE.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:39:11 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 18:05:04 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		write_to_file(t_map map, char *name, t_player mplayer)
{
	int		fd;
	int		i;

	if (open(name, O_EXCL) > 0) //if exist
		fd = open(name, O_WRONLY);
	else
		fd = open(name, O_CREAT | O_WRONLY);
	if (!fd)
		return (0);
	printf("%s %i", name, fd);

	write(fd, &map.editing, sizeof(int));

	write(fd, &map.fog, sizeof(int));
	write(fd, &map.fog_color, sizeof(Uint32));

	write(fd, &map.num_sect, sizeof(Uint32));

	i = -1;
	while (++i < map.num_sect)
	{
		write(fd, &map.sectors[i].num, sizeof(Uint32));
		write(fd, &map.sectors[i].num_vert, sizeof(Uint32));
		write(fd, map.sectors[i].vert, sizeof(t_vertex) * map.sectors[i].num_vert);
		write(fd, map.sectors[i].lines, sizeof(t_line) * map.sectors[i].num_vert);
		write(fd, map.sectors[i].neighbors, sizeof(char) * map.sectors[i].num_vert);
		write(fd, &map.sectors[i].ceil_plane, sizeof(t_plane));
		write(fd, &map.sectors[i].floor_plane, sizeof(t_plane));
		write(fd, &map.sectors[i].render_ceil, sizeof(int));
		write(fd, &map.sectors[i].ceil_tex, sizeof(int));
		write(fd, &map.sectors[i].floor_tex, sizeof(int));
		write(fd, &map.sectors[i].x_c_scale, sizeof(float));
		write(fd, &map.sectors[i].x_c_shift, sizeof(int));
		write(fd, &map.sectors[i].y_c_scale, sizeof(float));
		write(fd, &map.sectors[i].y_c_shift, sizeof(int));
		write(fd, &map.sectors[i].x_f_scale, sizeof(float));
		write(fd, &map.sectors[i].x_f_shift, sizeof(int));
		write(fd, &map.sectors[i].y_f_scale, sizeof(float));
		write(fd, &map.sectors[i].y_f_shift, sizeof(int));
		write(fd, &map.sectors[i].light_lvl, sizeof(int));
	}

	write(fd, &mplayer, sizeof(t_player));
	write(fd, &map.num_sprites, sizeof(Uint32));
	write(fd, map.sprites, sizeof(t_sprite) * MAX_SPRITES_COUNT);
	write(fd, &map.num_paint, sizeof(Uint32));
	write(fd, map.paint, sizeof(t_painting) * map.num_paint);
	close(fd);
	return (1);
}

int		main(int argc, char **argv)
{
	t_map	map;
	t_player	player;

	map.num_sect = 2;
	map.sectors = (t_sector*)malloc(sizeof(t_sector) * map.num_sect);
	map.sectors[0].num_vert = 4;
	map.sectors[0].num = 0;
	
	map.sectors[0].ceil_plane.a = 0;
	map.sectors[0].ceil_plane.b = 0;
	map.sectors[0].ceil_plane.c = 1;
	map.sectors[0].ceil_plane.h = -50;

	map.sectors[0].floor_plane.a = -0.0001;
	map.sectors[0].floor_plane.b = 0.0001;
	map.sectors[0].floor_plane.c = 1;
	map.sectors[0].floor_plane.h = -20;

	map.sectors[0].ceil_tex = rand() % 6;
	map.sectors[0].floor_tex = 0;

	map.sectors[0].x_c_scale = 1;
	map.sectors[0].y_c_scale = 1;
	map.sectors[0].x_c_shift = 0;
	map.sectors[0].y_c_shift = 0;

	map.sectors[0].x_f_scale = 1.0 / 10;
	map.sectors[0].y_f_scale = 1.0 / 10;
	map.sectors[0].x_f_shift = 0;
	map.sectors[0].y_f_shift = 0;
	map.sectors[0].light_lvl = 0;
	map.sectors[0].render_ceil = 1;

	map.sectors[0].neighbors = (char*)malloc(sizeof(char) * map.sectors->num_vert);
	map.sectors[0].vert = (t_vertex*)malloc(sizeof(t_vertex) * map.sectors->num_vert);

	map.sectors[0].vert[0].x = 0;
	map.sectors[0].vert[0].y = 0;
	map.sectors[0].vert[3].x = 20;
	map.sectors[0].vert[3].y = 30;
	map.sectors[0].vert[2].x = 40;
	map.sectors[0].vert[2].y = -20;
	map.sectors[0].vert[1].x = 0;
	map.sectors[0].vert[1].y = -10;

	map.sectors[0].lines = (t_line*)malloc(sizeof(t_line) * map.sectors[0].num_vert);
	for (int i = 0; i < map.sectors->num_vert; i++)
	{
		map.sectors[0].lines[0].wall = 1;
		map.sectors[0].lines[1].wall = 2;
		map.sectors[0].lines[2].wall = 5;
		map.sectors[0].lines[3].wall = 4;
		map.sectors[0].lines[i].top = 4;
		map.sectors[0].lines[i].bot = 4;

		map.sectors[0].lines[i].x_w_scale = 5;
		map.sectors[0].lines[i].x_b_scale = 1;
		map.sectors[0].lines[i].x_t_scale = 1;

		map.sectors[0].lines[i].x_w_shift = 50;
		map.sectors[0].lines[i].x_b_shift = 50;
		map.sectors[0].lines[i].x_t_shift = 50;

		map.sectors[0].lines[i].y_w_scale = 3;
		map.sectors[0].lines[i].y_b_scale = 10;
		map.sectors[0].lines[i].y_t_scale = 10;

		map.sectors[0].lines[i].y_w_shift = 0;
		map.sectors[0].lines[i].y_b_shift = 0;
		map.sectors[0].lines[i].y_t_shift = 0;
	}

	for (int i = 0; i < map.sectors->num_vert; i++)
		map.sectors[0].neighbors[i] = -1;
	map.sectors[0].neighbors[0] = 1;

	map.sectors[1].num_vert = 4;
	map.sectors[1].num = 1;
	map.fog = 1;
	map.fog_color = 0x00AAAA;
	map.sectors[1].ceil_plane.a = 0;
	map.sectors[1].ceil_plane.b = 0;
	map.sectors[1].ceil_plane.c = 1;
	map.sectors[1].ceil_plane.h = -40;

	map.sectors[1].render_ceil = 0;

	map.sectors[1].floor_plane.a = 0;
	map.sectors[1].floor_plane.b = 0;
	map.sectors[1].floor_plane.c = 1;
	map.sectors[1].floor_plane.h = -20;
	map.sectors[1].light_lvl = 70;
	map.sectors[1].ceil_tex = 4;
	map.sectors[1].floor_tex = 0;
	map.sectors[1].x_c_scale = 1.0 / 10;
	map.sectors[1].y_c_scale = 1.0 / 10;
	map.sectors[1].x_c_shift = (rand() % 100);
	map.sectors[1].y_c_shift = (rand() % 100);

	map.sectors[1].x_f_scale = 1.0 / 10;
	map.sectors[1].y_f_scale = 1.0 / 10;
	map.sectors[1].x_f_shift = (rand() % 100);
	map.sectors[1].y_f_shift = (rand() % 100);

	map.sectors[1].neighbors = (char*)malloc(sizeof(char) * map.sectors->num_vert);
	map.sectors[1].vert = (t_vertex*)malloc(sizeof(t_vertex) * map.sectors->num_vert);

	map.sectors[1].vert[0].x = 0;
	map.sectors[1].vert[0].y = 0;
	map.sectors[1].vert[3].x = 0;
	map.sectors[1].vert[3].y = -10;
	map.sectors[1].vert[2].x = -10;
	map.sectors[1].vert[2].y = -10;
	map.sectors[1].vert[1].x = -10;
	map.sectors[1].vert[1].y = 0;

	map.sectors[1].lines = (t_line*)malloc(sizeof(t_line) * map.sectors[1].num_vert);
	for (int i = 0; i < map.sectors[1].num_vert; i++)
	{
		map.sectors[1].lines[0].wall = 1;
		map.sectors[1].lines[1].wall = 3;
		map.sectors[1].lines[2].wall = 3;
		map.sectors[1].lines[3].wall = 1;
		map.sectors[1].lines[i].top = rand() % 6;
		map.sectors[1].lines[i].bot = rand() % 6;

		map.sectors[1].lines[i].x_w_scale = 1;
		map.sectors[1].lines[i].x_b_scale = 1;
		map.sectors[1].lines[i].x_t_scale = 1;

		map.sectors[1].lines[i].x_w_shift = 0;
		map.sectors[1].lines[i].x_b_shift = 0;
		map.sectors[1].lines[i].x_t_shift = 0;

		map.sectors[1].lines[i].y_w_scale = 10;
		map.sectors[1].lines[i].y_b_scale = 10;
		map.sectors[1].lines[i].y_t_scale = 50;

		map.sectors[1].lines[i].y_w_shift = 0;
		map.sectors[1].lines[i].y_b_shift = 0;
		map.sectors[1].lines[i].y_t_shift = 0;
	}

	for (int i = 0; i < map.sectors[1].num_vert; i++)
		map.sectors[1].neighbors[i] = -1;
	map.sectors[1].neighbors[3] = 0;

	player.coord.x = -5;
	player.coord.y = -5;
	player.coord.z = 0;
	player.sector = 1;
	player.angle = 0;
	player.angle_z = 0;
	player.anglecos = cosf(player.angle);
	player.anglesin = sinf(player.angle);

	map.num_sprites = 1;
	for (int i = 0; i < 1; i++)
	{
		map.sprites[i].spr_num = i;
		map.sprites[i].text_no = 0;
		map.sprites[i].num_sheet = 8;
		map.sprites[i].coord = (t_vector){-2, -3, get_z(map.sectors[0].floor_plane, -2, -3)};
		map.sprites[i].sector_no = 1;
		map.sprites[i].width = 3;
		map.sprites[i].start_z = 6;
		map.sprites[i].end_z = 12;
		map.sprites[i].mob = 1;
		map.sprites[i].angle = M_PI / 4;
		map.sprites[i].anglecos = cos(map.sprites[i].angle);
		map.sprites[i].anglesin = sin(map.sprites[i].angle);
		map.sprites[i].own_moves = i;
		map.sprites[i].move_speed = 0.03 * (i + 1);
		map.sprites[i].draw = 1;
		map.sprites[i].live = 1;
		map.sprites[i].vision_forward = 5; //must be positive //could be same for all sprites
		map.sprites[i].vision_backward = -3; //must be negative //could be same for all sprites
		map.sprites[i].key = 1;
		map.sprites[i].changes = 0;
		map.sprites[i].key_state = 0;
		map.sprites[i].num_of_sound = 0;
		map.sprites[i].event_num = 1;
	}

	player.coord.x = -5;
	player.coord.y = -5;
	player.coord.z = 0;
	player.sector = 1;
	player.angle = 0;
	player.angle_z = 0;
	player.anglecos = cosf(player.angle);
	player.anglesin = sinf(player.angle);

	map.paint = (t_painting*)ft_memalloc(sizeof(t_painting) * 1);
	map.num_paint = 1;
	map.paint[0].sector_no = 0;
	map.paint[0].v1.x = -6;
	map.paint[0].v1.y = -10;
	map.paint[0].v1.z = 40;
	map.paint[0].v2.x = -3;
	map.paint[0].v2.y = -10;
	map.paint[0].v2.z = 30;
	map.paint[0].text_no = 0;
	map.paint[0].key = 1;
	map.paint[0].draw = 1;
	map.paint[0].key_state = 1;
	map.paint[0].changes = 0;
	map.paint[0].event_num = 1;
	map.paint[0].speed = 5;
	map.paint[0].high_point = -40;
	map.paint[0].low_point = -10;
	map.paint[0].num_of_sect_to_lift = 0;
	map.paint[0].click = 0;
	map.editing = 0;
	map.paint[0].num_sheet = 3;

	// map.paint[1].sector_no = 0;
	// map.paint[1].v1.x = 0;
	// map.paint[1].v1.y = -3.5;
	// map.paint[1].v1.z = 30;
	// map.paint[1].v2.x = 0;
	// map.paint[1].v2.y = -5;
	// map.paint[1].v2.z = 20;
	// map.paint[1].text_no = 0;
	
	write_to_file(map, argv[1], player);
	return (0);
}