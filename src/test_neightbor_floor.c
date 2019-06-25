/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_neightbors_ceil.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:39:11 by apavlov           #+#    #+#             */
/*   Updated: 2019/04/27 15:39:14 by apavlov          ###   ########.fr       */
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

	write(fd, &map.num_sect, sizeof(Uint32));
	write(fd, &map.num_vert, sizeof(Uint32));

	write(fd, map.vertex, sizeof(t_vertex) * map.num_vert);

	i = -1;
	while (++i < map.num_sect)
	{
		write(fd, &map.sectors[i].num, sizeof(Uint32));
		write(fd, &map.sectors[i].num_vert, sizeof(Uint32));
		write(fd, map.sectors[i].vert, sizeof(t_vertex) * map.sectors[i].num_vert);
		//write(fd, map.sectors[i].lines, sizeof(t_line) * map.sectors[i].num_vert); //this one is unusable here
		write(fd, map.sectors[i].neighbors, sizeof(char) * map.sectors[i].num_vert);
		write(fd, &map.sectors[i].floor_z, sizeof(Uint32));
		write(fd, &map.sectors[i].ceil_z, sizeof(Uint32));
		write(fd, &map.sectors[i].floor_plane, sizeof(t_plane));
		write(fd, &map.sectors[i].ceil_plane, sizeof(t_plane));
		
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

	map.num_vert = 6;
	map.vertex = (t_vertex*)malloc(sizeof(t_vertex) * map.num_vert);

	map.num_sect = 2;
	map.sectors = (t_sector*)malloc(sizeof(t_sector) * map.num_sect);
	map.sectors[0].num_vert = 4;
	map.sectors[0].num = 0;

	map.sectors[0].ceil_plane.a = 1;
	map.sectors[0].ceil_plane.b = 0;
	map.sectors[0].ceil_plane.c = 1;
	map.sectors[0].ceil_plane.h = -40;

	map.sectors[0].floor_plane.a = -0.6;
	map.sectors[0].floor_plane.b = 0.6;
	map.sectors[0].floor_plane.c = 1;
	map.sectors[0].floor_plane.h = 0;

	map.sectors[0].floor_z = 0;
	map.sectors[0].ceil_z = 40;

	map.sectors[0].neighbors = (char*)malloc(sizeof(char) * map.sectors->num_vert);
	map.sectors[0].vert = (t_vertex*)malloc(sizeof(t_vertex) * map.sectors->num_vert);

	map.sectors[0].vert[0].x = 0;
	map.sectors[0].vert[0].y = 0;
	map.sectors[0].vert[3].x = 10;
	map.sectors[0].vert[3].y = 0;
	map.sectors[0].vert[2].x = 10;
	map.sectors[0].vert[2].y = -10;
	map.sectors[0].vert[1].x = 0;
	map.sectors[0].vert[1].y = -10;

	for (int i = 0; i < map.sectors->num_vert; i++)
		map.sectors[0].neighbors[i] = -1;
	map.sectors[0].neighbors[0] = 1;

	map.sectors[1].num_vert = 4;
	map.sectors[1].num = 1;

	map.sectors[1].ceil_plane.a = 0;
	map.sectors[1].ceil_plane.b = 0;
	map.sectors[1].ceil_plane.c = 1;
	map.sectors[1].ceil_plane.h = -40;

	map.sectors[1].floor_plane.a = 0;
	map.sectors[1].floor_plane.b = 0;
	map.sectors[1].floor_plane.c = 1;
	map.sectors[1].floor_plane.h = -20;

	map.sectors[1].floor_z = 20;
	map.sectors[1].ceil_z = 40;

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


	for (int i = 0; i < 1; i++)
	{
		map.sprites[i].text_no = i % 12;
		map.sprites[i].coord = (t_vector){-5+0.3*i, -5+0.3*i, get_z(map.sectors[1].floor_plane, -5+0.3*i, -5+0.3*i)};
		map.sprites[i].sector_no = -10+0.3*i < 0 ? 1 : -2;
	}

	for (int i = 1; i < 2; i++)
	{
		map.sprites[i].text_no = i % 12;
		map.sprites[i].coord = (t_vector){5+0.3*i, -5+0.3*i, get_z(map.sectors[0].floor_plane, 5+0.3*i, -5+0.3*i)};
		map.sprites[i].sector_no = -10+0.3*i < 0 ? 0 : -2;
	}

	map.paint = (t_painting*)ft_memalloc(sizeof(t_painting) * 1);
	map.num_paint = 1;
	map.paint->sector_no = 1;
	map.paint->v1.x = -6;
	map.paint->v1.y = -10;
	map.paint->v1.z = 35;
	map.paint->v2.x = -3;
	map.paint->v2.y = -10;
	map.paint->v2.z = 25;
	map.paint->text_no = 0;

	map.num_sprites = 2;
	write_to_file(map, argv[1], player);
	return (0);
}