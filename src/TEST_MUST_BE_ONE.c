/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST_MUST_BE_ONE.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:39:11 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/14 16:28:15 by myuliia          ###   ########.fr       */
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
	write(fd, &map.inverse_colors, sizeof(int));

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
	write(fd, map.sprites, sizeof(t_sprite) * map.num_sprites);
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

	map.sectors[0].ceil_tex = 3;
	map.sectors[0].floor_tex = 4;

	map.sectors[0].x_c_scale = 1 / 10.0;
	map.sectors[0].y_c_scale = 1 / 10.0;
	map.sectors[0].x_c_shift = 0;
	map.sectors[0].y_c_shift = 0;

	map.sectors[0].x_f_scale = 1.0 / 10;
	map.sectors[0].y_f_scale = 1.0 / 10;
	map.sectors[0].x_f_shift = 0;
	map.sectors[0].y_f_shift = 0;
	map.sectors[0].light_lvl = 0;
	map.sectors[0].render_ceil = 0;

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
		map.sectors[0].lines[0].wall = 4;
		map.sectors[0].lines[1].wall = 4;
		map.sectors[0].lines[2].wall = 4;
		map.sectors[0].lines[3].wall = 4;
		map.sectors[0].lines[i].top = 3;
		map.sectors[0].lines[i].bot = 3; 

		map.sectors[0].lines[i].x_w_scale = 5;
		map.sectors[0].lines[i].x_b_scale = 1;
		map.sectors[0].lines[i].x_t_scale = 1;

		map.sectors[0].lines[i].x_w_shift = 50;
		map.sectors[0].lines[i].x_b_shift = 50;
		map.sectors[0].lines[i].x_t_shift = 50;

		map.sectors[0].lines[i].y_w_scale = 3;
		map.sectors[0].lines[i].y_b_scale = 10;
		map.sectors[0].lines[i].y_t_scale = 10;

		map.sectors[0].lines[i].y_w_shift = 450;
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
	map.sectors[1].ceil_tex = 12;
	map.sectors[1].floor_tex = 13;
	map.sectors[1].x_c_scale = 1;
	map.sectors[1].y_c_scale = 1;
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
		map.sectors[1].lines[0].wall = 4;
		map.sectors[1].lines[1].wall = 4;
		map.sectors[1].lines[2].wall = 4;
		map.sectors[1].lines[3].wall = 4;
		map.sectors[1].lines[i].top = 4;
		map.sectors[1].lines[i].bot = 4;

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

	map.num_sprites = 9;
	for (int i = 0; i < 1; i++) // mob small
	{
		map.sprites[i].spr_num = i;
		map.sprites[i].text_no = 0;
		map.sprites[i].num_sheet = 6;
		map.sprites[i].coord = (t_vector){10, 10, get_z(map.sectors[0].floor_plane, 10, 10)};
		map.sprites[i].sector_no = 0;
		map.sprites[i].width = 3;
		map.sprites[i].start_z = 6;
		map.sprites[i].end_z = 12;
		map.sprites[i].mob = 1;
		map.sprites[i].angle = M_PI / 4;
		map.sprites[i].anglecos = cos(map.sprites[i].angle);
		map.sprites[i].anglesin = sin(map.sprites[i].angle);
		map.sprites[i].own_moves = i;
		map.sprites[i].move_speed = 0.25;
		map.sprites[i].draw = 1;
		map.sprites[i].live = 1;
		map.sprites[i].vision_forward = 5; //must be positive //could be same for all sprites
		map.sprites[i].vision_backward = -3; //must be negative //could be same for all sprites
		map.sprites[i].key = 1;
		map.sprites[i].changes = 0;
		map.sprites[i].key_state = 0;
		map.sprites[i].num_of_sound = 0;
		map.sprites[i].event_num = 1;
		map.sprites[i].hp = 20;
		map.sprites[i].death_time = 0;
	}
	for (int i = 1; i < 2; i++) //mob big
	{
		map.sprites[i].spr_num = i;
		map.sprites[i].text_no = 0;
		map.sprites[i].num_sheet = 5;
		map.sprites[i].coord = (t_vector){19, 10, get_z(map.sectors[0].floor_plane, 19, 10)};
		map.sprites[i].sector_no = 0;
		map.sprites[i].width = 4;
		map.sprites[i].start_z = 0;
		map.sprites[i].end_z = 14;
		map.sprites[i].mob = 1;
		map.sprites[i].angle = M_PI / 4;
		map.sprites[i].anglecos = cos(map.sprites[i].angle);
		map.sprites[i].anglesin = sin(map.sprites[i].angle);
		map.sprites[i].own_moves = i;
		map.sprites[i].move_speed = 0.15;
		map.sprites[i].draw = 1;
		map.sprites[i].live = 1;
		map.sprites[i].vision_forward = 5; //must be positive //could be same for all sprites
		map.sprites[i].vision_backward = -3; //must be negative //could be same for all sprites
		map.sprites[i].key = 1;
		map.sprites[i].changes = 0;
		map.sprites[i].key_state = 0;
		map.sprites[i].num_of_sound = 1;
		map.sprites[i].event_num = 1;
		map.sprites[i].hp = 60;
		map.sprites[i].death_time = 0;
	}
	for (int i = 2; i < 3; i++) //med
	{
		map.sprites[i].spr_num = i;
		map.sprites[i].text_no = 0;
		map.sprites[i].num_sheet = 1;
		map.sprites[i].coord = (t_vector){-3, -3, get_z(map.sectors[0].floor_plane, -3, -3)};
		map.sprites[i].sector_no = 1;
		map.sprites[i].width = 1;
		map.sprites[i].start_z = 0;
		map.sprites[i].end_z = 4;
		map.sprites[i].mob = 0;
		map.sprites[i].angle = 0;
		map.sprites[i].anglecos = 0;
		map.sprites[i].anglesin = 0;
		map.sprites[i].own_moves = 0;
		map.sprites[i].move_speed = 0;
		map.sprites[i].draw = 1;
		map.sprites[i].live = 0;
		map.sprites[i].vision_forward = 0; //must be positive //could be same for all sprites
		map.sprites[i].vision_backward = 0; //must be negative //could be same for all sprites
		map.sprites[i].key = 0;
		map.sprites[i].changes = 0;
		map.sprites[i].key_state = 0;
		map.sprites[i].num_of_sound = 0;
		map.sprites[i].event_num = 0;
		map.sprites[i].hp = 0;
		map.sprites[i].pick = 1;
	}
	for (int i = 3; i < 4; i++) //ammo
	{
		map.sprites[i].spr_num = i;
		map.sprites[i].text_no = 0;
		map.sprites[i].num_sheet = 2;
		map.sprites[i].coord = (t_vector){-6, -6, get_z(map.sectors[0].floor_plane, -6, -6)};
		map.sprites[i].sector_no = 1;
		map.sprites[i].width = 1;
		map.sprites[i].start_z = 0;
		map.sprites[i].end_z = 2;
		map.sprites[i].mob = 0;
		map.sprites[i].angle = 0;
		map.sprites[i].anglecos = 0;
		map.sprites[i].anglesin = 0;
		map.sprites[i].own_moves = 0;
		map.sprites[i].move_speed = 0;
		map.sprites[i].draw = 1;
		map.sprites[i].live = 0;
		map.sprites[i].vision_forward = 0; //must be positive //could be same for all sprites
		map.sprites[i].vision_backward = 0; //must be negative //could be same for all sprites
		map.sprites[i].key = 0;
		map.sprites[i].changes = 0;
		map.sprites[i].key_state = 0;
		map.sprites[i].num_of_sound = 0;
		map.sprites[i].event_num = 0;
		map.sprites[i].hp = 0;
		map.sprites[i].pick = 1;
	}
	for (int i = 4; i < 5; i++) // key
	{
		map.sprites[i].spr_num = i;
		map.sprites[i].text_no = 1;
		map.sprites[i].num_sheet = 3;
		map.sprites[i].coord = (t_vector){-4, -4, get_z(map.sectors[0].floor_plane, -4, -4)};
		map.sprites[i].sector_no = 1;
		map.sprites[i].width = 0.5;
		map.sprites[i].start_z = 0;
		map.sprites[i].end_z = 2;
		map.sprites[i].mob = 0;
		map.sprites[i].angle = 0;
		map.sprites[i].anglecos = 0;
		map.sprites[i].anglesin = 0;
		map.sprites[i].own_moves = 0;
		map.sprites[i].move_speed = 0;
		map.sprites[i].draw = 1;
		map.sprites[i].live = 0;
		map.sprites[i].vision_forward = 0; //must be positive //could be same for all sprites
		map.sprites[i].vision_backward = 0; //must be negative //could be same for all sprites
		map.sprites[i].key = 0;
		map.sprites[i].changes = 0;
		map.sprites[i].key_state = 0;
		map.sprites[i].num_of_sound = 0;
		map.sprites[i].event_num = 0;
		map.sprites[i].hp = 0;
		map.sprites[i].pick = 1;
		map.sprites[i].death_time = 0;
	}
	for (int i = 5; i < 6; i++)  // jetpack
	{
		map.sprites[i].spr_num = i;
		map.sprites[i].text_no = 0;
		map.sprites[i].num_sheet = 7;
		map.sprites[i].coord = (t_vector){20, -5, get_z(map.sectors[0].floor_plane, 20, -5)};
		map.sprites[i].sector_no = 0;
		map.sprites[i].width = 1;
		map.sprites[i].start_z = 0;
		map.sprites[i].end_z = 5;
		map.sprites[i].mob = 0;
		map.sprites[i].angle = 0;
		map.sprites[i].anglecos = 0;
		map.sprites[i].anglesin = 0;
		map.sprites[i].own_moves = 0;
		map.sprites[i].move_speed = 0;
		map.sprites[i].draw = 1;
		map.sprites[i].live = 0;
		map.sprites[i].vision_forward = 0; //must be positive //could be same for all sprites
		map.sprites[i].vision_backward = 0; //must be negative //could be same for all sprites
		map.sprites[i].key = 0;
		map.sprites[i].changes = 0;
		map.sprites[i].key_state = 0;
		map.sprites[i].num_of_sound = 0;
		map.sprites[i].event_num = 0;
		map.sprites[i].hp = 0;
		map.sprites[i].pick = 1;
		map.sprites[i].death_time = 0;
	}
	for (int i = 6; i < 7; i++) //npc
	{
		map.sprites[i].spr_num = i;
		map.sprites[i].text_no = 0;
		map.sprites[i].num_sheet = 9;
		map.sprites[i].coord = (t_vector){8, 8, get_z(map.sectors[0].floor_plane, 8, 8)};
		map.sprites[i].sector_no = 0;
		map.sprites[i].width = 2;
		map.sprites[i].start_z = 0;
		map.sprites[i].end_z = 11;
		map.sprites[i].mob = 0;
		map.sprites[i].angle = 0;
		map.sprites[i].anglecos = 0;
		map.sprites[i].anglesin = 0;
		map.sprites[i].own_moves = 0;
		map.sprites[i].move_speed = 0;
		map.sprites[i].draw = 1;
		map.sprites[i].live = 0;
		map.sprites[i].vision_forward = 0; //must be positive //could be same for all sprites
		map.sprites[i].vision_backward = 0; //must be negative //could be same for all sprites
		map.sprites[i].key = 1;
		map.sprites[i].changes = 0;
		map.sprites[i].key_state = 0;
		map.sprites[i].num_of_sound = 1;
		map.sprites[i].event_num = 3;
		map.sprites[i].hp = 0;
		map.sprites[i].pick = 0;
	}
	for (int i = 7; i < 8; i++) // boss small
	{
		map.sprites[i].spr_num = i;
		map.sprites[i].text_no = 0;
		map.sprites[i].num_sheet = 8;
		map.sprites[i].coord = (t_vector){11, 11, get_z(map.sectors[0].floor_plane, 11, 11)};
		map.sprites[i].sector_no = 0;
		map.sprites[i].width = 10;
		map.sprites[i].start_z = 3;
		map.sprites[i].end_z = 27;
		map.sprites[i].mob = 1;
		map.sprites[i].angle = M_PI / 4;
		map.sprites[i].anglecos = cos(map.sprites[i].angle);
		map.sprites[i].anglesin = sin(map.sprites[i].angle);
		map.sprites[i].own_moves = 1;
		map.sprites[i].move_speed = 0.10;
		map.sprites[i].draw = 1;
		map.sprites[i].live = 1;
		map.sprites[i].vision_forward = 10; //must be positive //could be same for all sprites
		map.sprites[i].vision_backward = -7; //must be negative //could be same for all sprites
		map.sprites[i].key = 1;
		map.sprites[i].changes = 0;
		map.sprites[i].key_state = 0;
		map.sprites[i].num_of_sound = 0;
		map.sprites[i].event_num = 1;
		map.sprites[i].hp = 300;
		map.sprites[i].death_time = 0;
	}
	for (int i = 8; i < 9; i++)  // tree
	{
		map.sprites[i].spr_num = i;
		map.sprites[i].text_no = 0;
		map.sprites[i].num_sheet = 11;
		map.sprites[i].coord = (t_vector){15, -5, get_z(map.sectors[0].floor_plane, 15, -5)};
		map.sprites[i].sector_no = 0;
		map.sprites[i].width = 5;
		map.sprites[i].start_z = 0;
		map.sprites[i].end_z = 30;
		map.sprites[i].mob = 0;
		map.sprites[i].angle = 0;
		map.sprites[i].anglecos = 0;
		map.sprites[i].anglesin = 0;
		map.sprites[i].own_moves = 0;
		map.sprites[i].move_speed = 0;
		map.sprites[i].draw = 1;
		map.sprites[i].live = 0;
		map.sprites[i].vision_forward = 0; //must be positive //could be same for all sprites
		map.sprites[i].vision_backward = 0; //must be negative //could be same for all sprites
		map.sprites[i].key = 0;
		map.sprites[i].changes = 0;
		map.sprites[i].key_state = 0;
		map.sprites[i].num_of_sound = 0;
		map.sprites[i].event_num = 0;
		map.sprites[i].hp = 0;
		map.sprites[i].pick = 0;
		map.sprites[i].death_time = 0;
	}


	player.coord.x = -5;
	player.coord.y = -5;
	player.coord.z = 0;
	player.sector = 1;
	player.angle = 0;
	player.angle_z = 0;
	player.anglecos = cosf(player.angle);
	player.anglesin = sinf(player.angle);

	//radio
	map.num_paint = 2;
	map.paint[0].sector_no = 1;
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
	map.paint[0].num_sheet = 12;

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
	map.paint[0].num_sheet = 12;




	map.inverse_colors = 0;
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