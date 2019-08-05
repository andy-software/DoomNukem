/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_write_read.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 21:17:49 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/05 21:26:03 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		ft_read_map_edit(t_doom *doom, int fd)
{
	int		i;
	p("\nIN FT_READ_MAP_EDIT\n");
	read(fd, &doom->map.editing, sizeof(int));
	read(fd, &doom->map.fog, sizeof(int));
	read(fd, &doom->map.fog_color, sizeof(Uint32));
	read(fd, &doom->map.num_sect, sizeof(Uint32));
	if (doom->map.num_sect > MAX_NUM_SECTORS)
		ft_error(2);
	i = -1;
	while (++i < (int)doom->map.num_sect)
	{
		read(fd, &doom->map.sectors[i].num, sizeof(Uint32));
		read(fd, &NUM_VERTEX, sizeof(Uint32));
		doom->map.sectors[i].vert = (t_vertex*)malloc(sizeof(t_vertex) * (NUM_VERTEX + 1));
		read(fd, doom->map.sectors[i].vert, sizeof(t_vertex) * NUM_VERTEX);
		doom->map.sectors[i].vert[NUM_VERTEX].x = doom->map.sectors[i].vert[0].x;
		doom->map.sectors[i].vert[NUM_VERTEX].y = doom->map.sectors[i].vert[0].y;
		doom->map.sectors[i].neighbors = (char *)malloc(sizeof(char) * NUM_VERTEX);
		read(fd, doom->map.sectors[i].lines, sizeof(t_line) * NUM_VERTEX);
		read(fd, doom->map.sectors[i].neighbors, sizeof(char) * NUM_VERTEX);
		read(fd, &doom->map.sectors[i].ceil_plane, sizeof(t_plane));
		read(fd, &doom->map.sectors[i].floor_plane, sizeof(t_plane));
		read(fd, &doom->map.sectors[i].render_ceil, sizeof(int));
		read(fd, &doom->map.sectors[i].ceil_tex, sizeof(int));
		read(fd, &doom->map.sectors[i].floor_tex, sizeof(int));
		read(fd, &doom->map.sectors[i].x_c_scale, sizeof(float));
		read(fd, &doom->map.sectors[i].x_c_shift, sizeof(int));
		read(fd, &doom->map.sectors[i].y_c_scale, sizeof(float));
		read(fd, &doom->map.sectors[i].y_c_shift, sizeof(int));
		read(fd, &doom->map.sectors[i].x_f_scale, sizeof(float));
		read(fd, &doom->map.sectors[i].x_f_shift, sizeof(int));
		read(fd, &doom->map.sectors[i].y_f_scale, sizeof(float));
		read(fd, &doom->map.sectors[i].y_f_shift, sizeof(int));
		read(fd, &doom->map.sectors[i].light_lvl, sizeof(int));
	}
	read(fd, &doom->player, sizeof(t_player));
	read(fd, &doom->map.num_sprites, sizeof(Uint32));
	read(fd, doom->map.sprites, sizeof(t_sprite) * MAX_SPRITES_COUNT);
	read(fd, &doom->map.num_paint, sizeof(Uint32));
	read(fd, doom->map.paint, sizeof(t_painting) * doom->map.num_paint);
	return (0);
}

int		ft_write_changes_to_file2(t_doom *doom, int fd, int i)
{
	while (++i < (int)doom->map.num_sect)
	{
		write(fd, &doom->map.sectors[i].num, sizeof(Uint32));
		write(fd, &NUM_VERTEX, sizeof(Uint32));
		write(fd, doom->map.sectors[i].vert, sizeof(t_vertex) * NUM_VERTEX);
		write(fd, doom->map.sectors[i].lines, sizeof(t_line) * NUM_VERTEX);
		write(fd, doom->map.sectors[i].neighbors, sizeof(char) * NUM_VERTEX);
		write(fd, &doom->map.sectors[i].ceil_plane, sizeof(t_plane));
		write(fd, &doom->map.sectors[i].floor_plane, sizeof(t_plane));
		write(fd, &doom->map.sectors[i].render_ceil, sizeof(int));
		write(fd, &doom->map.sectors[i].ceil_tex, sizeof(int));
		write(fd, &doom->map.sectors[i].floor_tex, sizeof(int));
		write(fd, &doom->map.sectors[i].x_c_scale, sizeof(float));
		write(fd, &doom->map.sectors[i].x_c_shift, sizeof(int));
		write(fd, &doom->map.sectors[i].y_c_scale, sizeof(float));
		write(fd, &doom->map.sectors[i].y_c_shift, sizeof(int));
		write(fd, &doom->map.sectors[i].x_f_scale, sizeof(float));
		write(fd, &doom->map.sectors[i].x_f_shift, sizeof(int));
		write(fd, &doom->map.sectors[i].y_f_scale, sizeof(float));
		write(fd, &doom->map.sectors[i].y_f_shift, sizeof(int));
		write(fd, &doom->map.sectors[i].light_lvl, sizeof(int));
	}
}

int		ft_write_changes_to_file(t_doom *doom, int fd)
{
	p("\nIN FT_WRITE_CHANGES_TO_FILE\n");
	write(fd, &doom->map.editing, sizeof(int));
	write(fd, &doom->map.fog, sizeof(int));
	write(fd, &doom->map.fog_color, sizeof(Uint32));
	write(fd, &doom->map.num_sect, sizeof(Uint32));
	ft_write_changes_to_file2(doom, fd, -1);
	write(fd, &doom->player, sizeof(t_player));
	write(fd, &doom->map.num_sprites, sizeof(Uint32));
	write(fd, doom->map.sprites, sizeof(t_sprite) * MAX_SPRITES_COUNT);
	write(fd, &doom->map.num_paint, sizeof(Uint32));
	write(fd, doom->map.paint, sizeof(t_painting) * doom->map.num_paint);
	return (1);
}