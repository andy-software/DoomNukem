/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:41:51 by apavlov           #+#    #+#             */
/*   Updated: 2019/03/23 15:41:52 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	Info_about_map(t_map *map)
{

	printf("sector count %i\nvertex count %i\n", map->num_sect, map->num_vert);

	for (int v = 0; v < map->num_vert; v++)
		printf("vertex %i - {%f, %f}\n", v, map->vertex[v].x, map->vertex[v].y);


	for (int s = 0; s < map->num_sect; s++)
	{
		printf("sector num - %i\n", map->sectors[s].num);
		printf("sector vertx count - %i\n", map->sectors[s].num_vert);
		for (int i = 0; i < map->sectors[s].num_vert; i++)
		{
			printf("vertex %i - {%f, %f}\n", i, map->sectors[s].vert[i].x, map->sectors[s].vert[i].y);
			printf("neightbors %i - %i\n", i, map->sectors[s].neighbors[i]);
		}
		printf("floor consts %f %f %f %f\n", map->sectors[s].floor_plane.a, map->sectors[s].floor_plane.b, map->sectors[s].floor_plane.c, map->sectors[s].floor_plane.h);
		printf("ceils consts %f %f %f %f\n", map->sectors[s].ceil_plane.a, map->sectors[s].ceil_plane.b, map->sectors[s].ceil_plane.c, map->sectors[s].ceil_plane.h);
		printf("ceil height %i\n floor height %i\n", map->sectors[s].ceil_z, map->sectors[s].floor_z);
		printf("sprites count %i\n", map->num_sprites);
		for (int i = 0; i < map->num_sprites; i++)
		{
			printf("sprite %i - {%f, %f, %f}\n texture of sprite %i\n", i, map->sprites[i].coord.x, map->sprites[i].coord.y, map->sprites[i].coord.z, map->sprites[i].text_no);
		}
		printf("sprites count %i\n", map->num_paint);
		for (int i = 0; i < map->num_paint; i++)
		{
			printf("paint %i - {%f, %f, %f} {%f, %f, %f}\n texture of paint %i\n", i, map->paint[i].v1.x, map->paint[i].v1.y, map->paint[i].v1.z, map->paint[i].v2.x, map->paint[i].v2.y, map->paint[i].v2.z, map->paint[i].text_no);
		}
	}
}

static void Info_about_player(t_player *player)
{
	printf("player's coord = {%f, %f, %f}\n", player->coord.x, player->coord.y, player->coord.z);
	printf("player's angles = {%f, %f}\n", player->angle, player->angle_z);
	printf("player's sector %i\n", player->sector);
}

int			read_file(t_doom *doom, char *file_name)
{
	t_map		*map;
	t_player	*player;
	int		fd;
	int		i;

	map = &doom->map;
	player = &doom->player;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (0);
	read(fd, &map->num_sect, sizeof(Uint32));
	read(fd, &map->num_vert, sizeof(Uint32));

	map->vertex = (t_vertex*)malloc(sizeof(t_vertex) * map->num_vert);
	read(fd, map->vertex, sizeof(t_vertex) * map->num_vert);

	map->sectors = (t_sector*)malloc(sizeof(t_sector) * map->num_sect);
	i = -1;
	while (++i < map->num_sect)
	{
		read(fd, &map->sectors[i].num, sizeof(Uint32));
		read(fd, &map->sectors[i].num_vert, sizeof(Uint32));
		map->sectors[i].vert = (t_vertex*)malloc(sizeof(t_vertex) * (map->sectors[i].num_vert + 1));
		read(fd, map->sectors[i].vert, sizeof(t_vertex) * map->sectors[i].num_vert);
		//read(fd, tex->pix, sizeof(Uint32) * tex->width * tex->height);
		map->sectors[i].vert[map->sectors[i].num_vert].x = map->sectors[i].vert[0].x; //MAKE ONE LAST SAME WITH THE FIRST FOR RENDERING
		map->sectors[i].vert[map->sectors[i].num_vert].y = map->sectors[i].vert[0].y; //MAKE ONE LAST SAME WITH THE FIRST FOR RENDERING
		map->sectors[i].neighbors = (char*)malloc(sizeof(char) * map->sectors[i].num_vert);
		// map->sectors[i].lines = (t_line*)malloc(sizeof(t_line) * map->sectors[i].num_vert); //this one is unusable in first test map
		// read(fd, map->sectors[i].lines, sizeof(t_line) * map->sectors[i].num_vert); //this one is unusable in first test map
		read(fd, map->sectors[i].neighbors, sizeof(char) * map->sectors[i].num_vert);
		read(fd, &map->sectors[i].floor_z, sizeof(Uint32));
		read(fd, &map->sectors[i].ceil_z, sizeof(Uint32));
		read(fd, &map->sectors[i].floor_plane, sizeof(t_plane));
		read(fd, &map->sectors[i].ceil_plane, sizeof(t_plane));
		
	}
	read(fd, player, sizeof(t_player));

	read(fd, &map->num_sprites, sizeof(Uint32));
	read(fd, map->sprites, sizeof(t_sprite) * MAX_SPRITES_COUNT);
	read(fd, &map->num_paint, sizeof(Uint32));
	map->paint = (t_painting*)ft_memalloc(sizeof(t_painting) * map->num_paint);
	read(fd, map->paint, sizeof(t_painting) * map->num_paint);
	Info_about_map(map);
	Info_about_player(player);

	close(fd);
	return (1);
}
