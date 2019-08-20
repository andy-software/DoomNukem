/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:41:51 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/19 19:54:53 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	Info_about_map(t_map *map)
{
	for (int s = 0; s < (int)map->num_sect; s++)
	{
		printf("sector num - %i\n", map->sectors[s].num);
		printf("sector vertx count - %i\n", map->sectors[s].num_vert);
		for (int i = 0; i < (int)map->sectors[s].num_vert; i++)
		{
			printf("vertex %i - {%f, %f}\n", i, map->sectors[s].vert[i].x, map->sectors[s].vert[i].y);
			printf("neightbors %i - %i\n", i, map->sectors[s].neighbors[i]);
		}
		printf("floor consts %f %f %f %f\n", map->sectors[s].floor_plane.a, map->sectors[s].floor_plane.b, map->sectors[s].floor_plane.c, map->sectors[s].floor_plane.h);
		printf("ceils consts %f %f %f %f\n", map->sectors[s].ceil_plane.a, map->sectors[s].ceil_plane.b, map->sectors[s].ceil_plane.c, map->sectors[s].ceil_plane.h);
		printf("sprites count %i\n", map->num_sprites);
		// for (int i = 0; i < map->num_sprites; i++)
		// {
		// 	printf("sprite %i - {%f, %f, %f}\n texture of sprite %i\n", i, map->sprites[i].coord.x, map->sprites[i].coord.y, map->sprites[i].coord.z, map->sprites[i].text_no);
		// }
		printf("sprites count %i\n", map->num_paint);
		// for (int i = 0; i < map->num_paint; i++)
		// {
		// 	printf("paint %i - {%f, %f, %f} {%f, %f, %f}\n texture of paint %i\n", i, map->paint[i].v1.x, map->paint[i].v1.y, map->paint[i].v1.z, map->paint[i].v2.x, map->paint[i].v2.y, map->paint[i].v2.z, map->paint[i].text_no);
		// }
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
	int			fd;
	Uint32		i;

	map = &doom->map;
	player = &doom->player;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (0);

	read(fd, &map->editing, sizeof(int));

	read(fd, &map->fog, sizeof(int));
	read(fd, &map->fog_color, sizeof(Uint32));
	read(fd, &map->inverse_colors, sizeof(int));

	read(fd, &map->num_sect, sizeof(Uint32));

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
		map->sectors[i].lines = (t_line*)malloc(sizeof(t_line) * map->sectors[i].num_vert);
		read(fd, map->sectors[i].lines, sizeof(t_line) * map->sectors[i].num_vert);
		read(fd, map->sectors[i].neighbors, sizeof(char) * map->sectors[i].num_vert);
		read(fd, &map->sectors[i].ceil_plane, sizeof(t_plane));
		read(fd, &map->sectors[i].floor_plane, sizeof(t_plane));
		read(fd, &map->sectors[i].render_ceil, sizeof(int));
		read(fd, &map->sectors[i].ceil_tex, sizeof(int));
		read(fd, &map->sectors[i].floor_tex, sizeof(int));
		read(fd, &map->sectors[i].x_c_scale, sizeof(float));
		read(fd, &map->sectors[i].x_c_shift, sizeof(int));
		read(fd, &map->sectors[i].y_c_scale, sizeof(float));
		read(fd, &map->sectors[i].y_c_shift, sizeof(int));
		read(fd, &map->sectors[i].x_f_scale, sizeof(float));
		read(fd, &map->sectors[i].x_f_shift, sizeof(int));
		read(fd, &map->sectors[i].y_f_scale, sizeof(float));
		read(fd, &map->sectors[i].y_f_shift, sizeof(int));
		read(fd, &map->sectors[i].light_lvl, sizeof(int));
	}

	read(fd, player, sizeof(t_player));
	read(fd, &map->num_sprites, sizeof(Uint32));
	read(fd, map->sprites, sizeof(t_sprite) * map->num_sprites);
	read(fd, &map->num_paint, sizeof(Uint32));
	read(fd, map->paint, sizeof(t_painting) * map->num_paint);
	Info_about_map(map);
	Info_about_player(player);

	close(fd);
	return (1);
}
