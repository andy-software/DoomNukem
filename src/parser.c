/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:41:51 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/24 19:27:16 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	info_about_player(t_player *player)
{
	ft_putstr("player's sector");
	ft_putnbr(player->sector);
	ft_putstr("\n");
}

int			read_file2(t_map *map, int fd, int i)
{
	read(fd, &map->sectors[i].num, sizeof(Uint32));
	read(fd, &MAP_N_VER, sizeof(Uint32));
	map->sectors[i].vert = (t_vertex*)malloc(sizeof(t_vertex) \
	* (MAP_N_VER + 1));
	read(fd, map->sectors[i].vert, sizeof(t_vertex) * MAP_N_VER);
	map->sectors[i].vert[MAP_N_VER].x = map->sectors[i].vert[0].x;
	map->sectors[i].vert[MAP_N_VER].y = map->sectors[i].vert[0].y;
	map->sectors[i].neighbors = (char*)malloc(sizeof(char) * MAP_N_VER);
	map->sectors[i].lines = (t_line*)malloc(sizeof(t_line) * MAP_N_VER);
	read(fd, map->sectors[i].lines, sizeof(t_line) * MAP_N_VER);
	read(fd, map->sectors[i].neighbors, sizeof(char) * MAP_N_VER);
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

int			read_file(t_doom *doom, char *file_name)
{
	t_map		*map;
	t_player	*player;

	INT_2(fd, i);
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
	while (++i < map->num_sect)
		read_file2(map, fd, i);
	read(fd, player, sizeof(t_player));
	read(fd, &map->num_sprites, sizeof(Uint32));
	read(fd, map->sprites, sizeof(t_sprite) * map->num_sprites);
	read(fd, &map->num_paint, sizeof(Uint32));
	read(fd, map->paint, sizeof(t_painting) * map->num_paint);
	info_about_player(player);
	close(fd);
	return (1);
}
