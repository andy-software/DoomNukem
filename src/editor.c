/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:26:08 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/02 17:27:19 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		ft_map_editor(t_doom *doom, char *name)
{
	p("\nIN FT_MAP_EDITOR\n");
	int		fd;
	
	if (open(name, O_EXCL) > 0) //if exist
	{
		fd = open(name, O_RDONLY);
		ft_read_map_edit(doom, fd);
		printf("READ MAP-----------------------------------------\n");
		int	i = -1;
		printf("doom->num_sect                     %d\n", doom->map.num_sect);
		while (++i < (int)doom->map.num_sect)
		{
			p("HER\n");
			printf("doom->map.sectors[%d].num_vert:     %d\n", i, doom->map.sectors[i].num_vert);
			int j = -1;
			while (++j < (int)doom->map.sectors[i].num_vert)
			{
				printf("doom->map.sectors[%d].vert[%d].x:   %f\n", i, j, doom->map.sectors[i].vert[j].x);
				printf("doom->map.sectors[%d].vert[%d].y:   %f\n", i, j, doom->map.sectors[i].vert[j].y);
				printf("doom->map.sectors[%d].neighbors[%d]:   %d\n", i, j, doom->map.sectors[i].neighbors[j]);
				p("\n");
			}
		}
		printf("doom->player.coord.x:                      %f\n", doom->player.coord.x);
		printf("doom->player.coord.y:                      %f\n", doom->player.coord.y);
		printf("READ MAP-----------------------------------------\n\n\n");
		close(fd);
		fd = open(name, O_WRONLY);
	}
	else
		fd = open(name, O_CREAT | O_WRONLY);
	if (fd < 0)
		return (error_message("fd is bad :(\n") + 1);
	if (doom->editor.save_del != 2) // при удалении не создавать новое окно
	{
		if (ft_create_window(doom, name) != 1)
			exit(0);
	}
	ft_prepare_editor(doom);
	ft_start_edit(doom, fd);
	if (doom->editor.save_del == 2)
	{
		doom->map.num_vert = 0;
		ft_map_editor(doom, name);
		
	}
	close(fd);
	return (0);
}

int     ft_read_map_edit(t_doom *doom, int fd) // exist int			read_file(t_doom *doom, char *file_name)
{
	p("\nIN FT_READ_MAP_EDIT\n");
	int i;

	read(fd, &doom->map.editing, sizeof(int));
	read(fd, &doom->map.fog, sizeof(int));
	read(fd, &doom->map.fog_color, sizeof(Uint32));
	read(fd, &doom->map.num_sect, sizeof(Uint32));
	read(fd, &doom->map.num_vert, sizeof(Uint32));
	doom->map.sectors = (t_sector*)malloc(sizeof(t_sector) * MAX_SECTORS);

	if (doom->map.num_sect > MAX_NUM_SECTORS)
	{
		ft_putstr("Wrong file or to many sectors\n");
		exit(0);
	}
	i = -1;
	while (++i < (int)doom->map.num_sect)
	{
		read(fd, &doom->map.sectors[i].num, sizeof(Uint32));
		read(fd, &doom->map.sectors[i].num_vert, sizeof(Uint32));
		doom->map.sectors[i].vert = (t_vertex*)malloc(sizeof(t_vertex) * (doom->map.sectors[i].num_vert + 1));
		read(fd, doom->map.sectors[i].vert, sizeof(t_vertex) * doom->map.sectors[i].num_vert);
		doom->map.sectors[i].vert[doom->map.sectors[i].num_vert].x = doom->map.sectors[i].vert[0].x;
		doom->map.sectors[i].vert[doom->map.sectors[i].num_vert].y = doom->map.sectors[i].vert[0].y;
		doom->map.sectors[i].neighbors = (char *)malloc(sizeof(char) * doom->map.sectors[i].num_vert);
		doom->map.sectors[i].lines = (t_line*)malloc(sizeof(t_line) * doom->map.sectors[i].num_vert); //this one is unusable in first test map
		read(fd, doom->map.sectors[i].lines, sizeof(t_line) * doom->map.sectors[i].num_vert); //this one is unusable in first test map
		read(fd, doom->map.sectors[i].neighbors, sizeof(char) * doom->map.sectors[i].num_vert);
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

int		ft_prepare_to_write(t_doom *doom)
{
	p("\nIN FT_PREAPARE_TO_WRITE\n");
	int		i;

	i = -1;
	if (!doom->map.num_sect || !doom->player.coord.y)
	{
		printf("Nothing to store;(\n");
		return (0);
	}

	doom->player.coord.z = 10;
	doom->player.angle = 0;
	doom->player.angle_z = 0;
	doom->player.anglecos = cosf(doom->player.angle);
	doom->player.anglesin = sinf(doom->player.angle);

	doom->map.num_sprites = 2;
	for (int i = 0; i < 2; i++)
	{
		doom->map.sprites[i].spr_num = i;
		doom->map.sprites[i].text_no = 0;
		doom->map.sprites[i].coord = (t_vector){-2, -3, get_z(doom->map.sectors[0].floor_plane, -2, -3)};
		doom->map.sprites[i].sector_no = -10+0.3*i < 0 ? 1 : -2;
		doom->map.sprites[i].width = 5;
		doom->map.sprites[i].start_z = 0;
		doom->map.sprites[i].end_z = 5;
		doom->map.sprites[i].mob = 1;
		doom->map.sprites[i].angle = M_PI / 4;
		doom->map.sprites[i].anglecos = cos(doom->map.sprites[i].angle);
		doom->map.sprites[i].anglesin = sin(doom->map.sprites[i].angle);
		doom->map.sprites[i].own_moves = i;
		doom->map.sprites[i].move_speed = 0.03 * (i + 1);
		doom->map.sprites[i].draw = 1;
		doom->map.sprites[i].live = 1;
		doom->map.sprites[i].vision_forward = 5; //must be positive //could be same for all sprites
		doom->map.sprites[i].vision_backward = -3; //must be negative //could be same for all sprites
	}

	doom->map.paint = (t_painting*)ft_memalloc(sizeof(t_painting) * 1);
	doom->map.num_paint = 1;
	doom->map.paint[0].sector_no = 1;
	doom->map.paint[0].v1.x = -6;
	doom->map.paint[0].v1.y = -10;
	doom->map.paint[0].v1.z = 40;
	doom->map.paint[0].v2.x = -3;
	doom->map.paint[0].v2.y = -10;
	doom->map.paint[0].v2.z = 30;
	doom->map.paint[0].text_no = 0;

	doom->editor.fl_or_ceil = 1;

	// doom->map.num_sprites = 0;
	// doom->map.num_paint = 0;
	doom->editor.images[1].im_x[1] = (doom->player.coord.x * 10) - 50;
	doom->editor.images[1].im_y[1] = (doom->player.coord.y * 10) - 50;
	return (1);
}

void	ft_prepare_editor(t_doom *doom)
{
	p("\nIN FT_PREPARE_EDITOR\n");
	int		i;
	int		j;

	i = 0;
	doom->game.quit = 0;
	doom->editor.but1_press = 0;
	doom->editor.is_drawing = 0;
	doom->editor.is_portal = 0;
	doom->editor.ind_img = 0;
	doom->editor.is_sector = 1;
	doom->editor.ind_text = 5; // as 0
	doom->editor.img_press = 0;
	doom->editor.press.ind_action = 5;
	doom->editor.save_del = 0;
	doom->editor.fl_or_ceil = 1;
	if (!doom->map.num_sect || doom->editor.save_del == 2) // если не было сохранений 
	{
		printf("\nIT WAS NO SAVINGS BEFORE\n");
		doom->map.sectors = (t_sector*)malloc(sizeof(t_sector) * MAX_SECTORS);  //leaks
		doom->editor.interface.nbr_vertex = 0;
		doom->editor.interface.iterator_num_vertex = 0;
		doom->editor.interface.nbr_sectors = 0;
		doom->editor.save_del = 0;
		j = -1;
		while (++j < MAX_SECTORS)
		{
			doom->map.sectors[j].light_lvl = 1;
			doom->map.sectors[j].num_vert = 0;
			doom->map.sectors[j].num = j;
			doom->map.sectors[j].ceil_plane.a = 0;
			doom->map.sectors[j].ceil_plane.b = 0;
			doom->map.sectors[j].ceil_plane.c = 1;
			doom->map.sectors[j].ceil_plane.h = -80;

			doom->map.sectors[j].floor_plane.a = 0;
			doom->map.sectors[j].floor_plane.b = 0;
			doom->map.sectors[j].floor_plane.c = 1;
			doom->map.sectors[j].floor_plane.h = -10;

			doom->map.sectors[j].ceil_tex = 4;
			doom->map.sectors[j].floor_tex = 4;

			doom->map.sectors[j].x_c_scale = 1;
			doom->map.sectors[j].y_c_scale = 1;
			doom->map.sectors[j].x_c_shift = 0;
			doom->map.sectors[j].y_c_shift = 0;

			doom->map.sectors[j].x_f_scale = 1.0 / 10;
			doom->map.sectors[j].y_f_scale = 1.0 / 10;
			doom->map.sectors[j].x_f_shift = 0;
			doom->map.sectors[j].y_f_shift = 0;
			doom->map.sectors[j].render_ceil = 1;

			doom->map.sectors[j].lines = (t_line*)malloc(sizeof(t_line) * MAX_VERT);
			for (int l = 0; l < MAX_VERT; l++)
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

				doom->map.sectors[j].lines[l].y_w_shift = 0;
				doom->map.sectors[j].lines[l].y_b_shift = 0;
				doom->map.sectors[j].lines[l].y_t_shift = 0;
			} 
		}
		
	}
	doom->editor.interface.is_drawing_interface = 0;
	doom->editor.interface.start_new_sector = 0;
	while (++i < NB_BUTTONS)
	{
		doom->editor.images[i].im_x = (double *)malloc(sizeof(double) * 100);
		doom->editor.images[i].im_y = (double *)malloc(sizeof(double) * 100);
		doom->editor.images[i].im_x[0] = 700 + (i * 100); // обнулить
		doom->editor.images[i].im_y[0] = 20;
		doom->editor.images[i].im_x[1] = 700 + (i * 100); // обнулить
		doom->editor.images[i].im_y[1] = 20;
		doom->editor.images[i].exist = 0;
	}
	/******      FOG      ********/
	doom->map.fog = 0;
	doom->map.fog_color = 0x00FF00;
	/****************************/

	/****   To make objects visible on map (player, sprite..)  *****/
	if (doom->player.coord.x && doom->player.coord.y)
	{
		doom->editor.images[1].exist = 1;
		doom->editor.images[1].im_x[1] = (doom->player.coord.x * 10) - 50;
		doom->editor.images[1].im_y[1] = (doom->player.coord.y * 10) - 50;
	}
	/* *********************************************************** */
	doom->editor.fline.num_line1 = -1;
	doom->editor.fline.num_line2 = -1;
	doom->editor.fline.sec1 = -1;
	doom->editor.fline.sec2 = -1;
	doom->player.sector = 0;
}

int		ft_start_edit(t_doom *doom, int fd)
{
	p("\nIN FT_START_EDIT\n");
	SDL_Event event;
	while (doom->game.quit != 1)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				doom->game.quit = 1;
			else if (event.type == SDL_KEYUP)
				ft_check_key(doom, &event);
			else if (event.type == SDL_KEYDOWN)
				key_floor_ceil(doom);
			else if (event.type == SDL_MOUSEBUTTONUP)
				ft_mouse_press_edit(doom, &event);
			else if (event.type == SDL_MOUSEBUTTONDOWN)
				ft_mouse_release_edit(doom, &event);
			else if (event.type == SDL_MOUSEMOTION)
				ft_mouse_move_edit(doom, &event);
			ft_bzero(doom->editor.sdl.surface->pixels, WIN_HEIGHT * WIN_WIDTH * sizeof(Uint32));
		}
		ft_render_editor(doom);
		SDL_UpdateWindowSurface(doom->editor.sdl.window);
		/**** CREATE FUNCTION: CHECK SAVE DEL ***/
		if (doom->editor.save_del == 1) //saving
		{
			if (ft_prepare_to_write(doom))
				ft_write_changes_to_file(doom, fd);
			doom->editor.save_del = 0;
		}
		else if (doom->editor.save_del == 3)
		{
			if (ft_prepare_to_write(doom)) // функция должна возврщать инт чтобы проверить хватает ли данных 
			{
				doom->map.editing = 1;
				// ft_write_changes_to_file(doom, fd);
				game_mod_editor(doom);
				ft_prepare_to_write(doom);
				ft_write_changes_to_file(doom, fd);
			}
			doom->editor.save_del = 0;
		}
	}
	return (0);
}

void	 ft_render_editor(t_doom *doom)
{
	ft_render_interface(doom);
	ft_render_previous(doom);
	ft_render_other(doom);
}

void	ft_render_previous(t_doom *doom)
{
	int		j;
	int		it;


	j = -1;
	doom->editor.interface.tmp_x1 = doom->editor.brezen.x1;
	doom->editor.interface.tmp_y1 = doom->editor.brezen.y1;
	doom->editor.interface.tmp_x2 = doom->editor.brezen.x2;
	doom->editor.interface.tmp_y2 = doom->editor.brezen.y2;
	while (++j < (int)doom->map.num_sect)
	{
		it = -1;
		while (++it < (int)doom->map.sectors[j].num_vert)
		{
			doom->editor.brezen.x1 = doom->map.sectors[j].vert[it].x * 10;
			doom->editor.brezen.y1 = doom->map.sectors[j].vert[it].y * 10;
			doom->editor.brezen.x2 = doom->map.sectors[j].vert[it + 1].x * 10;
			doom->editor.brezen.y2 = doom->map.sectors[j].vert[it + 1].y * 10;
			doom->editor.brezen.color = 0x66ff8a;
			/* Another color for portals */
			// printf("doom->map.sectors[%d].neighbors[%d]:      %d\n", j, it, doom->map.sectors[j].neighbors[it]);
			if (doom->map.sectors[j].neighbors[it] != -1)
				doom->editor.brezen.color = 0xFF0001;
			/* ************************ */
			ft_line(doom);
		}
	}
	it = 0;
	if (doom->editor.is_drawing == 0) // segfault here
		doom->map.sectors[doom->map.num_sect].num_vert = 0;
	while (++it < (int)doom->map.sectors[doom->map.num_sect].num_vert)
	{
		doom->editor.brezen.x1 = (doom->map.sectors[doom->map.num_sect].vert[it].x * 10);
		doom->editor.brezen.y1 = doom->map.sectors[doom->map.num_sect].vert[it].y * 10;
		doom->editor.brezen.x2 = doom->map.sectors[doom->map.num_sect].vert[it - 1].x * 10;
		doom->editor.brezen.y2 = doom->map.sectors[doom->map.num_sect].vert[it - 1].y * 10;
		doom->editor.brezen.color = 0xFFFFFF;
		ft_line(doom);
	}	
	doom->editor.brezen.x1 = doom->editor.interface.tmp_x1;
	doom->editor.brezen.y1 = doom->editor.interface.tmp_y1;
	doom->editor.brezen.x2 = doom->editor.interface.tmp_x2;
	doom->editor.brezen.y2 = doom->editor.interface.tmp_y2;	
}

int		check_on_point(t_doom *doom)
{
	int		i;
	int		j;

	j = -1;
	if (doom->map.num_sect > 0)
	{
		j = -1;
		while (++j < (int)doom->map.num_sect)
		{
			i = -1;
			while (++i < (int)doom->map.sectors[j].num_vert)
			{
				if ((doom->editor.brezen.x1 / 10) == doom->map.sectors[j].vert[i].x &&
				(doom->editor.brezen.y1 / 10) == doom->map.sectors[j].vert[i].y)
					return (1);
			}
		}
		doom->editor.but1_press = 0;
		return (0);
	}
	return (1);
}

void	ft_render_other(t_doom *doom) 
{
	doom->editor.brezen.color = 0xFFFFFF;
	if (doom->editor.is_drawing == 0 && doom->editor.but1_press == 1 && doom->editor.is_sector == 1)
	{
		doom->editor.brezen.x1 = doom->editor.brezen.x2;
		doom->editor.brezen.y1 = doom->editor.brezen.y2;
		if(check_on_point(doom))
		{
			ft_line(doom);
			doom->map.sectors[doom->map.num_sect].vert = (t_vertex *)malloc(sizeof(t_vertex) * 100);
			doom->map.sectors[doom->map.num_sect].neighbors = (char *)malloc(sizeof(char) * 100);
			doom->map.sectors[doom->map.num_sect].vert[0].x = doom->editor.brezen.x1 / 10;
			doom->map.sectors[doom->map.num_sect].vert[0].y = doom->editor.brezen.y1 / 10;
			doom->map.sectors[doom->map.num_sect].neighbors[doom->map.sectors[doom->map.num_sect].num_vert] = -1; // init neighbours

			doom->map.sectors[doom->map.num_sect].num_vert++;
			doom->editor.is_sector = 0;
			doom->editor.is_drawing = 1;
			doom->editor.but1_press = 0;
				write(1, "1\n", 2);
		}
	}
	else if (doom->editor.is_drawing == 1 && doom->editor.but1_press == 1)
	{
		doom->editor.brezen.x1 = doom->editor.brezen.x2;
		doom->editor.brezen.y1 = doom->editor.brezen.y2;
		doom->map.sectors[doom->map.num_sect].neighbors[doom->map.sectors[doom->map.num_sect].num_vert] = -1;  // init neighbours
		doom->map.sectors[doom->map.num_sect].vert[doom->map.sectors[doom->map.num_sect].num_vert].x = doom->editor.brezen.x1 / 10;
		doom->map.sectors[doom->map.num_sect].vert[doom->map.sectors[doom->map.num_sect].num_vert].y = doom->editor.brezen.y1 / 10;
		doom->map.sectors[doom->map.num_sect].num_vert++;

		doom->editor.is_drawing = 1;
		doom->editor.but1_press = 0;
		printf("num_sec: %d   num_vert: %d\n",doom->map.num_sect, doom->map.sectors[doom->map.num_sect].num_vert);
		write(1, "2\n", 2);
	}
	else if (doom->editor.is_drawing == 1 && doom->editor.but1_press == 0)
		ft_line(doom);
}

int		convex(t_doom *doom) // выпуклость
{
	double		product;
	t_vertex	ab;
	t_vertex	bc;
	t_vertex	*polig;
	int			i;

	polig = (t_vertex *)malloc(sizeof(t_vertex) * (doom->map.sectors[doom->map.num_sect].num_vert * 999)); // FIX 
	i = -1;
	while (++i < (int)doom->map.sectors[doom->map.num_sect].num_vert) // FIX_NUM  doom->map.sectors[doom->map.num_sect].num_vert
	{
		polig[i].x = doom->map.sectors[doom->map.num_sect].vert[i + 1].x - doom->map.sectors[doom->map.num_sect].vert[i].x;
		polig[i].y = doom->map.sectors[doom->map.num_sect].vert[i + 1].y - doom->map.sectors[doom->map.num_sect].vert[i].y;
		if (i == ((int)doom->map.sectors[doom->map.num_sect].num_vert - 1))
		{
			polig[i].x = doom->map.sectors[doom->map.num_sect].vert[0].x - doom->map.sectors[doom->map.num_sect].vert[i].x;
			polig[i].y = doom->map.sectors[doom->map.num_sect].vert[0].y - doom->map.sectors[doom->map.num_sect].vert[i].y;
		}
		// printf("polig[%d].x:   %f, polig[%d].y:   %f\n", i, polig[i].x, i, polig[i].y);
	}
	int	j = -1;
	while (++j < (int)doom->map.sectors[doom->map.num_sect].num_vert) // NUM_VER - 2 // FIX_NUM
	{
		printf("\nJ %d\n", j);
		if (j == 0)
		{
			ab.x = polig[j].x - polig[(int)doom->map.sectors[doom->map.num_sect].num_vert - 1].x;
			ab.y = polig[j].y - polig[(int)doom->map.sectors[doom->map.num_sect].num_vert - 1].y;
			bc.x = polig[j + 1].x - polig[j].x;
			bc.y = polig[j + 1].y - polig[j].y;
		}
		else
		{
			ab.x = polig[j].x - polig[j - 1].x;
			ab.y = polig[j].y - polig[j - 1].y;
			bc.x = polig[j + 1].x - polig[j].x;
			bc.y = polig[j + 1].y - polig[j].y;
		}
		product = ab.x * bc.y - bc.x * ab.y;
		// printf("product: %f\n", product);
		if (product < 0)
		{
			printf("\033[1;31m SECTOR ISN'T CONVEX\033[0m\n");
			doom->editor.is_sector = 2;
			return (0);
		}
		// printf("             Product  %f\n", product);
	}
	printf("\033[1;33m SECTOR IS CONVEX\033[0m\n");
	doom->editor.is_sector = 1;
	return (1);
}

int		is_in_sector(t_doom *doom, SDL_Event *event)
{
	int		i;
	int		sec;
	double	product;

	if (event->button.x < WIN_WIDTH - 400)
	{
		t_vertex	vert;
		t_vertex	vert2;
		t_vertex	point;

		sec = -1;
		point = (t_vertex){(event->button.x / 10), (event->button.y / 10)};
		while (++sec < (int)doom->map.num_sect)
		{		
			i = -1;
			while (++i < (int)doom->map.sectors[sec].num_vert)	
			{
				vert = (t_vertex){(doom->map.sectors[sec].vert[i].x - point.x), (doom->map.sectors[sec].vert[i].y - point.y)};
				if (i == (int)doom->map.sectors[sec].num_vert - 1)
					vert2 = (t_vertex){(doom->map.sectors[sec].vert[0].x - point.x), (doom->map.sectors[sec].vert[0].y - point.y)};
				else
					vert2 = (t_vertex){(doom->map.sectors[sec].vert[i + 1].x - point.x), (doom->map.sectors[sec].vert[i + 1].y - point.y)};
				product = vert.x * vert2.y - vert2.x * vert.y;
				if (product < 0 && (i = -1))
				{
					sec++;
					if (sec == (int)doom->map.num_sect)
					{
						printf("\033[1;31m POINT NOT IN THE SECTOR\033[0m\n"); // leave it, but with write
						return (-1);
					}
				}
				if (i == (int)doom->map.sectors[sec].num_vert - 1)
				{
					printf("\033[1;32m POINT IN THE SECTOR: %d\033[0m\n", sec);
					return (sec);
				}
			}
		}
	}
		return (-1);
}

void	rec_action(t_doom *doom, SDL_Event *event)
{
	if (event->button.x <= 850) // Left
	{
		doom->editor.press.ind_action--;
		if (doom->editor.press.ind_action == 4)
			doom->editor.press.ind_action = 8;
		
	}
	if (event->button.x >= 1150) // Right
	{	
		doom->editor.press.ind_action++;
		if (doom->editor.press.ind_action == 9)
			doom->editor.press.ind_action = 5;
	}
}

void	in_sector(t_doom *doom, SDL_Event *event)
{
	if (event->button.x < (WIN_WIDTH - 400))
	{
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			doom->editor.brezen.x2 = ft_specify_coor(event->button.x);
			doom->editor.brezen.y2 = ft_specify_coor(event->button.y);
			doom->editor.but1_press = 1;
			printf("event->button.x: %d\n", event->button.x);
			printf("event->button.y: %d\n", event->button.y);
		}
		if (event->button.button == SDL_BUTTON_RIGHT)
		{
			if (doom->map.sectors[doom->map.num_sect].vert[0].x == doom->map.sectors[doom->map.num_sect].vert[(doom->map.sectors[doom->map.num_sect].num_vert - 1)].x && doom->map.sectors[doom->map.num_sect].num_vert > 2 &&
			doom->map.sectors[doom->map.num_sect].vert[0].y == doom->map.sectors[doom->map.num_sect].vert[(doom->map.sectors[doom->map.num_sect].num_vert - 1)].y)
			{
				p("\nhere to convex\n");
				doom->map.sectors[doom->map.num_sect].num_vert--;
				if (convex(doom))
				{
					doom->map.num_sect++;
					doom->map.sectors[doom->map.num_sect].num_vert = 0;
					doom->editor.is_drawing = 0;
					doom->editor.is_sector = 1;
				}
				else
				{
					doom->map.sectors[doom->map.num_sect].num_vert++;
					doom->editor.is_drawing = 1;
				}
			}
			if (doom->editor.is_drawing == 1)
			{
				printf("button right\n");
				if (doom->map.sectors[doom->map.num_sect].num_vert > 1)
				{
					doom->editor.brezen.x1 = (doom->map.sectors[doom->map.num_sect].vert[(doom->map.sectors[doom->map.num_sect].num_vert - 2)].x * 10);
					doom->editor.brezen.y1 = (doom->map.sectors[doom->map.num_sect].vert[(doom->map.sectors[doom->map.num_sect].num_vert - 2)].y * 10);
					printf("doom->map.sectors[doom->map.num_sect].num_vert:   %d\n", doom->map.sectors[doom->map.num_sect].num_vert);
					doom->map.sectors[doom->map.num_sect].num_vert--;
				}
			}
			printf("here2 Number of sectors:   %d\n", doom->map.num_sect);
			doom->editor.but1_press = 0;
		}
	}
	if ((event->button.x >= 840 && event->button.x <= (840 + 325)) && (event->button.y >= 630 && event->button.y <= (630 + 55)))
	{
		if (doom->map.fog == 1)
			doom->map.fog = 0;
		else
			doom->map.fog = 1;
	}
}






/**************************************************/
/**************************************************/
/**************************************************/
/************         OTHER STAFF       ***********/
/**************************************************/
/**************************************************/

void	add_items(t_doom *doom, SDL_Event *event)
{
	if (event->button.x < (WIN_WIDTH - 400))
	{
		if (doom->editor.img_press == 1 && event->button.button == SDL_BUTTON_LEFT)
		{
			if (doom->editor.ind_img != 0)
			{
				if (is_in_sector(doom, event) == -1) // FIX not inside sector 
				{
						if (doom->editor.images[doom->editor.ind_img].exist != 0)
							doom->editor.images[doom->editor.ind_img].exist--;
							doom->editor.img_press = 1;
				}
				else // запись 
				{
					doom->editor.images[doom->editor.ind_img].im_x[EXIST + 1] = 700 + (doom->editor.ind_img * 100); // обнулить
					doom->editor.images[doom->editor.ind_img].im_y[EXIST + 1] = 20;
					if (doom->editor.ind_img == 1)
					{
						if (doom->editor.images[doom->editor.ind_img].exist == 1) // чтобы записать только первое значение игрока
							if (doom->editor.ind_img == 1)
							{
								doom->player.coord.x = event->button.x / 10;
								doom->player.coord.y = event->button.y / 10;
							}
						doom->editor.images[doom->editor.ind_img].exist = 1;
					}
					doom->editor.ind_img = 0;
				}
			}
		}
			doom->editor.img_press = 0;
	}
	else if (event->button.x > (WIN_WIDTH - 400))
	{
		if ((event->button.y >= 20 && event->button.y <= 100) && event->button.button == SDL_BUTTON_LEFT)
		{
			doom->editor.img_press = 1;
			doom->editor.ind_img = ((event->button.x / 100) - 7);
			doom->editor.images[doom->editor.ind_img].exist++;
			if (doom->editor.ind_img == 1 && EXIST == 2)
			{
				doom->editor.img_press = 0;
				EXIST = 1;
			}
		}
		if (event->button.button == SDL_BUTTON_RIGHT) // FIX отменить картинку на
		{
			doom->editor.ind_img = ((event->button.x / 100) - 7);
			doom->editor.images[doom->editor.ind_img].im_x[0] = 700 + (doom->editor.ind_img * 100); // обнулить
			doom->editor.images[doom->editor.ind_img].im_y[0] = 20;
			if (doom->editor.images[doom->editor.ind_img].exist != 0)
				doom->editor.images[doom->editor.ind_img].exist--;
		}
	}
}

void	del_save_play(t_doom *doom, SDL_Event *event)
{
	printf("del, save, play\n");
	if (event->button.x <= 65 && (doom->editor.save_del = 2)) // delete
		doom->game.quit = 1;
	else if (event->button.x >= 65 && event->button.x <= 115) //save
		doom->editor.save_del = 1;
	else // play
	{
		doom->editor.save_del = 3;
		// doom->game.quit = 1;
	}
}

void	change_floor_ceil(t_doom *doom, SDL_Event *event)
{
	if ((event->button.x > 850 && event->button.x < 1150) &&  (event->button.y > 230 && event->button.y < 530))
	{
		if (doom->editor.fl_or_ceil == FLOOR)
			doom->editor.fl_or_ceil = CEIL;
		else
			doom->editor.fl_or_ceil = FLOOR;
	}
	int sector = is_in_sector(doom, event);
	if (sector != -1)
	{
		printf("we can choose texture for this sector\n");
	}
}

void	ft_mouse_press_edit(t_doom *doom, SDL_Event *event)
{
	if ((event->button.y >= 130 && event->button.y <= 180) && (event->button.x >= 800 && event->button.x <= 1200))
		rec_action(doom, event);
	if ((event->button.y >= 750 && event->button.y <= 785) && (event->button.x >= 25 && event->button.x <= 140))
		del_save_play(doom, event);
	else if (doom->editor.press.ind_action == 5)
		in_sector(doom, event);
	if (doom->editor.press.ind_action == 6)
		add_items(doom, event);
	if (doom->editor.press.ind_action == 7)
		change_text(doom, event);
	if (doom->editor.press.ind_action == 8)
		change_floor_ceil(doom, event);
}

void	change_text(t_doom *doom, SDL_Event *event)
{
	int		i;

	if ((event->button.y >= 550 && event->button.y <= 600) && (event->button.x >= 1000 && event->button.x <= 1120))
	{
		if (doom->map.num_sect != 0)
		{
			if (event->button.x <= 1050)
			{
				printf("Left Arrow\n");
				doom->editor.ind_text--;
				if (doom->editor.ind_text == 4)
					doom->editor.ind_text = NUM_WALL;
			}
			else
			{
				printf("Rigth Arrow\n");
				doom->editor.ind_text++;
				if (doom->editor.ind_text == (NUM_WALL + 1))
					doom->editor.ind_text = 5;
			}
		}
	}
	p("\n");
	if ((event->button.x >= 850 && event->button.x <= 1170) && (event->button.y >= 420 && event->button.y <= 470))
	{
		if (doom->editor.fline.sec1 != -1 && doom->editor.fline.sec2 != -1)
		{
			if (doom->map.sectors[doom->editor.fline.sec1].neighbors[doom->editor.fline.num_line1] == -1)
			{
				doom->map.sectors[doom->editor.fline.sec1].neighbors[doom->editor.fline.num_line1] = doom->editor.fline.sec2;
				doom->map.sectors[doom->editor.fline.sec2].neighbors[doom->editor.fline.num_line2] = doom->editor.fline.sec1;
				doom->editor.is_portal = 1;
			}
			else
			{
				doom->map.sectors[doom->editor.fline.sec1].neighbors[doom->editor.fline.num_line1] = -1;
				doom->map.sectors[doom->editor.fline.sec2].neighbors[doom->editor.fline.num_line2] = -1;
				doom->editor.is_portal = 0;
			}
		}
	}
	if (event->button.x < WIN_WIDTH - 400) // FIX на какой прямой лежит точка
	{
		t_vertex	point;
		double		p;
		int			k;
		int			more;

		more = 0;
		k = -1;
		point = (t_vertex){(event->button.x / 10), (event->button.y / 10)};
		while (++k < (int)doom->map.num_sect)
		{
			i = -1;
			while (++i < (int)doom->map.sectors[k].num_vert)
			{
				p = ((point.x - doom->map.sectors[k].vert[i].x) * (doom->map.sectors[k].vert[i + 1].y - doom->map.sectors[k].vert[i].y))
				- ((doom->map.sectors[k].vert[i + 1].x - doom->map.sectors[k].vert[i].x) * (point.y - doom->map.sectors[k].vert[i].y));
				// printf(" p:  %0.2f   \n", fabs(p));
				if (more == 0 && fabs(p) < 50)
				{
					printf("\033[1;32m skhoditsa LINIA #%d \033[0m\n", i + 1);
					doom->editor.fline.num_line1 = i;
					doom->editor.fline.num_line2 = -1;
					doom->editor.fline.sec1 = k;
					doom->editor.fline.sec2 = -1;
					more++;
					break ;
				}
				else if (more == 1 && fabs(p) < 50)
				{
					doom->editor.fline.num_line2 = i;
					doom->editor.fline.sec2 = k;
				}
			}
		}
		printf("\n");
	}
	printf("\033[1;34m   num_line1: %d\n   num_line2: %d\n   sec1: %d\n   sec2: %d \033[0m\n\n", doom->editor.fline.num_line1, doom->editor.fline.num_line2, doom->editor.fline.sec1, doom->editor.fline.sec2);
}

/* Save information in sector by using left/right     */
/* разбить отдельно обработку секторов и кнопок       */
/* Check function is in sector                        */
/* Check function convex                              */
/* При нажатии выбирать портал и записывать в neighb  */
/*                                                    */
