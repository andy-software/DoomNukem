/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 15:52:00 by arudyi            #+#    #+#             */
/*   Updated: 2019/07/01 21:23:01 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

char	*ft_free_strjoin(char *s1, char const *s2)
{
	char	*str;
	int		a;
	int		b;

	a = ft_strlen(s1);
	b = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char*)ft_strnew(a + b)))
		return (NULL);
	a = 0;
	b = 0;
	while (s1[a])
	{
		str[a] = s1[a];
		a++;
	}
	while (s2[b])
		str[a++] = s2[b++];
	str[a] = '\0';
	free(s1);
	return (str);
}

void	ft_draw_pixel(t_doom *doom, int x, int y, int color)
{
	int index;

	if (x < (WIN_WIDTH - 400) || doom->editor.interface.is_drawing_interface == 1)
	{
		index = doom->sdl.surface->pitch * y + x * doom->sdl.surface->format->BytesPerPixel;
		// if (*(unsigned *)(doom->sdl.surface->pixels + index) != 0)
		// 	return ;
			// printf("doom->sdl.surface->pixels + index %u\n", *(unsigned int *)(doom->sdl.surface->pixels));
		*(unsigned *)(doom->sdl.surface->pixels + index) = color;
	}
}

int		ft_write_changes_to_file(t_doom *doom, int fd)
{
	int i;
 
	i = -1;
	write(fd, &doom->map.num_sect, sizeof(Uint32));
	write(fd, &doom->map.num_vert, sizeof(Uint32));

	write(fd, doom->map.vertex, sizeof(t_vertex) * doom->map.num_vert);
	i = -1;
	while (++i < doom->map.num_sect)
	{
		write(fd, &doom->map.sectors[i].num, sizeof(Uint32));
		write(fd, &doom->map.sectors[i].num_vert, sizeof(Uint32));
		write(fd, doom->map.sectors[i].vert, sizeof(t_vertex) * doom->map.sectors[i].num_vert);
		//write(fd, doom->map.sectors[i].lines, sizeof(t_line) * doom->map.sectors[i].num_vert); //this one is unusable here
		write(fd, doom->map.sectors[i].neighbors, sizeof(char) * doom->map.sectors[i].num_vert);
		write(fd, &doom->map.sectors[i].floor_z, sizeof(Uint32));
		write(fd, &doom->map.sectors[i].ceil_z, sizeof(Uint32));
		write(fd, &doom->map.sectors[i].floor_plane, sizeof(t_plane));
		write(fd, &doom->map.sectors[i].ceil_plane, sizeof(t_plane));
	}

	write(fd, &doom->player, sizeof(t_player));
	write(fd, &doom->map.num_sprites, sizeof(Uint32));
	write(fd, doom->map.sprites, sizeof(t_sprite) * MAX_SPRITES_COUNT);
	write(fd, &doom->map.num_paint, sizeof(Uint32));
	write(fd, doom->map.paint, sizeof(t_painting) * doom->map.num_paint);
	return (1);
}

int		ft_map_editor(t_doom *doom, char *name)
{
	int		fd;
	
	if (open(name, O_EXCL) > 0) //if exist
	{
		fd = open(name, O_RDONLY);
		ft_read_map_edit(doom, fd);
		printf("READ MAP---------------\n");
		printf("doom->map.num_vert: %d\n", doom->map.num_vert - 1);
		printf("doom->map.num_sect: %d\n", doom->map.num_sect);
		printf("doom->player.coord.x: %f\n", doom->player.coord.x);
		printf("doom->player.coord.y: %f\n", doom->player.coord.y);
		
		int i = -1;
		if (doom->map.num_vert != -1) // FIX (before saving)
			while (++i < doom->map.num_vert)
				printf("doom->map.sectors[0].vert[j].y: %f\n", doom->map.sectors[0].vert[i].y);
			// printf("doom->map.vertex[%d].x: %f\n", i, doom->map.vertex[i].y);

		printf("READ MAP---------------\n\n");
		// printf("doom->map.sectors[0].num_vert: %d\n", doom->map.sectors[0].num_vert);
		// printf("doom->map.sectors[0].num: %d\n", doom->map.sectors[0].num);
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
	else
		doom->editor.save_del = 0;
	ft_prepare_editor(doom);
	ft_start_edit(doom, fd, name);
	if (doom->editor.save_del == 2)
		ft_map_editor(doom, name);
	close(fd);
	return (0);
}

int		ft_create_window(t_doom *doom, char *name)
{
	char	*str;
	char	*str1;
	char 	*str2;
	int		i;
	
	i = 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (error_message((char *)SDL_GetError()));
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
		return (error_message((char *)SDL_GetError()));
	if (!(doom->sdl.window = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, \
		WIN_HEIGHT, SDL_WINDOW_SHOWN)))
		return (error_message((char *)SDL_GetError()));
	if (!(doom->sdl.surface = SDL_GetWindowSurface(doom->sdl.window)))
		return (error_message((char *)SDL_GetError()));
	if (TTF_Init() < 0)
		return (error_message((char *)SDL_GetError()));
	// doom->editor.font.text_color.b = 200; // init font
	doom->editor.font.text_color = (SDL_Color){255, 255, 250};
	doom->editor.font.text_font = TTF_OpenFont("./textures/editor/font.ttf", 30);
	while (++i < NB_BUTTONS) // download buttons
	{
		str2 = ft_itoa(i);
		str1 = ft_strjoin("./textures/editor/photo", str2);
		str = ft_strjoin(str1, ".png");
		doom->editor.images[i].image = load_tex(str, &doom->sdl);
		free(str2); free(str); free(str1);
		if (!doom->editor.images[i].image)
		printf ( "IMG_Load: %s\n", IMG_GetError());
	}
	i = 0;
	while (++i < NB_IMAGES)
	{
		str2 = ft_itoa(i);
		str1 = ft_strjoin("./textures/editor/sector", str2);
		str = ft_strjoin(str1, ".png");
		doom->editor.sector[i].image = load_tex(str, &doom->sdl);
		free(str2); free(str); free(str1);
		if (!doom->editor.sector[i].image)
		printf ( "IMG_Load: %s\n", IMG_GetError());
	}
	SDL_UpdateWindowSurface(doom->sdl.window);
	// SDL_SetWindowGrab(doom->sdl.window, 1);
	return (1);
}

int     ft_read_map_edit(t_doom *doom, int fd) // exist int			read_file(t_doom *doom, char *file_name)
{
	int i;

	i = -1;
	read(fd, &doom->map.num_sect, sizeof(Uint32));
	read(fd, &doom->map.num_vert, sizeof(Uint32));
	doom->map.vertex = (t_vertex *)malloc(sizeof(t_vertex) * doom->map.num_vert);
	read(fd, doom->map.vertex, sizeof(t_vertex) * doom->map.num_vert);
	doom->map.sectors = (t_sector*)malloc(sizeof(t_sector) * doom->map.num_sect);
	while (++i < doom->map.num_sect)
	{
		read(fd, &doom->map.sectors[i].num, sizeof(Uint32));
		read(fd, &doom->map.sectors[i].num_vert, sizeof(Uint32));
		doom->map.sectors[i].vert = (t_vertex*)malloc(sizeof(t_vertex) * (doom->map.sectors[i].num_vert + 1));
		read(fd, doom->map.sectors[i].vert, sizeof(t_vertex) * doom->map.sectors[i].num_vert);
		doom->map.sectors[i].vert[doom->map.sectors[i].num_vert].x = doom->map.sectors[i].vert[0].x; //MAKE ONE LAST SAME WITH THE FIRST FOR RENDERING
		doom->map.sectors[i].vert[doom->map.sectors[i].num_vert].y = doom->map.sectors[i].vert[0].y; //MAKE ONE LAST SAME WITH THE FIRST FOR RENDERING
		doom->map.sectors[i].neighbors = (char *)malloc(sizeof(char) * doom->map.sectors[i].num_vert);
		//map->sectors[i].lines = (t_line*)malloc(sizeof(t_line) * map->sectors[i].num_vert); //this one is unusable in first test map
		//read(fd, map->sectors[i].lines, sizeof(t_line) * map->sectors[i].num_vert); //this one is unusable in first test map
		read(fd, doom->map.sectors[i].neighbors, sizeof(char) * doom->map.sectors[i].num_vert);
		read(fd, &doom->map.sectors[i].floor_z, sizeof(Uint32));
		read(fd, &doom->map.sectors[i].ceil_z, sizeof(Uint32));
		read(fd, &doom->map.sectors[i].floor_plane, sizeof(t_plane));
		read(fd, &doom->map.sectors[i].ceil_plane, sizeof(t_plane));
		printf("in map reader\n");
	}
	read(fd, &doom->player, sizeof(t_player));
	return (0);
}

int		ft_example(t_doom *doom)
{
	doom->map.num_vert = 6;
	doom->map.vertex = (t_vertex*)malloc(sizeof(t_vertex) * doom->map.num_vert);

	doom->map.num_sect = 2;
	doom->map.sectors = (t_sector*)malloc(sizeof(t_sector) * doom->map.num_sect);
	doom->map.sectors[0].num_vert = 4;
	doom->map.sectors[0].num = 0;

	doom->map.sectors[0].ceil_plane.a = 1;
	doom->map.sectors[0].ceil_plane.b = 0;
	doom->map.sectors[0].ceil_plane.c = 1;
	doom->map.sectors[0].ceil_plane.h = -40;

	doom->map.sectors[0].floor_plane.a = 0;
	doom->map.sectors[0].floor_plane.b = 0;
	doom->map.sectors[0].floor_plane.c = 1;
	doom->map.sectors[0].floor_plane.h = 0;

	// doom->map.sectors[0].floor_z = 0;
	// doom->map.sectors[0].ceil_z = 40;

	doom->map.sectors[0].neighbors = (char*)malloc(sizeof(char) * doom->map.sectors->num_vert);
	doom->map.sectors[0].vert = (t_vertex*)malloc(sizeof(t_vertex) * doom->map.sectors->num_vert);

	doom->map.sectors[0].vert[0].x = 0;
	doom->map.sectors[0].vert[0].y = 0;
	doom->map.sectors[0].vert[3].x = 10;
	doom->map.sectors[0].vert[3].y = 0;
	doom->map.sectors[0].vert[2].x = 10;
	doom->map.sectors[0].vert[2].y = -10;
	doom->map.sectors[0].vert[1].x = 0;
	doom->map.sectors[0].vert[1].y = -10;

	for (int i = 0; i < doom->map.sectors->num_vert; i++)
		doom->map.sectors[0].neighbors[i] = -1;
	doom->map.sectors[0].neighbors[0] = 1;

	doom->map.sectors[1].num_vert = 4;
	doom->map.sectors[1].num = 1;

	doom->map.sectors[1].ceil_plane.a = -1;
	doom->map.sectors[1].ceil_plane.b = 0;
	doom->map.sectors[1].ceil_plane.c = 1;
	doom->map.sectors[1].ceil_plane.h = -40;

	doom->map.sectors[1].floor_plane.a = 0;
	doom->map.sectors[1].floor_plane.b = 0;
	doom->map.sectors[1].floor_plane.c = 1;
	doom->map.sectors[1].floor_plane.h = -20;

	// doom->map.sectors[1].floor_z = 20;
	// doom->map.sectors[1].ceil_z = 40;

	doom->map.sectors[1].neighbors = (char*)malloc(sizeof(char) * doom->map.sectors->num_vert);
	doom->map.sectors[1].vert = (t_vertex*)malloc(sizeof(t_vertex) * doom->map.sectors->num_vert);

	doom->map.sectors[1].vert[0].x = 0;
	doom->map.sectors[1].vert[0].y = 0;
	doom->map.sectors[1].vert[3].x = 0;
	doom->map.sectors[1].vert[3].y = -10;
	doom->map.sectors[1].vert[2].x = -10;
	doom->map.sectors[1].vert[2].y = -10;
	doom->map.sectors[1].vert[1].x = -10;
	doom->map.sectors[1].vert[1].y = 0;

	for (int i = 0; i < doom->map.sectors[1].num_vert; i++)
		doom->map.sectors[1].neighbors[i] = -1;
	doom->map.sectors[1].neighbors[3] = 0;

	doom->player.coord.x = -5;
	doom->player.coord.y = -5;
	doom->player.coord.z = 0;
	doom->player.sector = 1;
	doom->player.angle = 0;
	doom->player.angle_z = 0;
	doom->player.anglecos = cosf(doom->player.angle);
	doom->player.anglesin = sinf(doom->player.angle);
	return (0);
}

int		ft_prepare_to_write(t_doom *doom)
{
	int		i;
	int		j;

	i = -1;
	if (!NUM_VER || !NUM_SECT || !doom->player.coord.y)
	{
		printf("Nothing to store;(\n"); // FIX without exit 
		return (0);
	}
	else	
		doom->map.num_vert = NUM_VER - 1;
	doom->map.num_sect = NUM_SECT;
	doom->map.sectors[0].num_vert = NUM_VER - 1; // change it
	doom->map.sectors[0].vert = (t_vertex *)malloc(sizeof(t_vertex) * 100);
	while (++i < doom->map.num_sect)
	{
		j = -1;
		while (++j < doom->map.num_vert)
		{
			doom->map.sectors[0].vert[j].y = doom->map.vertex[j].y;
			doom->map.sectors[0].vert[j].x = doom->map.vertex[j].x;
		}
	}
	// doom->map.sectors[0].ceil_plane.a = 0;
	// doom->map.sectors[0].ceil_plane.b = 0;
	// doom->map.sectors[0].ceil_plane.c = 1;
	// doom->map.sectors[0].ceil_plane.h = -60;

	// doom->map.sectors[0].floor_plane.a = 0;
	// doom->map.sectors[0].floor_plane.b = 0;
	// doom->map.sectors[0].floor_plane.c = 1;
	// doom->map.sectors[0].floor_plane.h = 0;

	// doom->map.sectors[0].floor_z = 0;
	// doom->map.sectors[0].ceil_z = 40;
	
	doom->map.sectors[0].neighbors = (char*)malloc(sizeof(char) * doom->map.sectors->num_vert);
	for (int i = 0; i < doom->map.sectors->num_vert; i++)
		doom->map.sectors[0].neighbors[i] = -1;
	// doom->player.coord.x = 0;
	// doom->player.coord.y = 0;
	doom->player.coord.z = 10;
	doom->player.sector = 0;
	doom->player.angle = 0;
	doom->player.angle_z = 0;
	doom->player.anglecos = cosf(doom->player.angle);
	doom->player.anglesin = sinf(doom->player.angle);

	doom->map.num_sprites = 0;
	doom->map.num_paint = 0;
	return (1);
}

void	ft_prepare_editor(t_doom *doom)
{
	int		i;

	i = 0;
	// doom->map.vertex = (t_vertex *)malloc(sizeof(t_vertex) * 10000);
	doom->map.sectors = (t_sector*)malloc(sizeof(t_sector) * 1000);  //leaks
	doom->game.quit = 0;
	doom->editor.but1_press = 0;
	doom->editor.is_drawing = 0;
	doom->editor.interface.nbr_vertex = 0;
	doom->editor.interface.iterator_num_vertex = 0;
	doom->editor.interface.is_drawing_interface = 0;
	doom->editor.interface.nbr_sectors = 0;
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
	doom->editor.ind_img = 0;
	doom->editor.is_sector = 0;
	doom->editor.ind_text = 5; // as 0
	doom->editor.img_press = 0;
	doom->editor.press.ind_action = 5;
	doom->editor.save_del = 0;

	/*  make it for all sectors  */
	doom->map.sectors[0].ceil_plane.a = 0;
	doom->map.sectors[0].ceil_plane.b = 0;
	doom->map.sectors[0].ceil_plane.c = 1;
	doom->map.sectors[0].ceil_plane.h = -60;

	doom->map.sectors[0].floor_plane.a = 0;
	doom->map.sectors[0].floor_plane.b = 0;
	doom->map.sectors[0].floor_plane.c = 1;
	doom->map.sectors[0].floor_plane.h = 0;

	doom->map.sectors[0].floor_z = 0;
	doom->map.sectors[0].ceil_z = 40;
	/* ****** */
}

int		ft_start_edit(t_doom *doom, int fd, char *name)
{
	SDL_Event event;

	while (doom->game.quit != 1)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				doom->game.quit = 1;
			else if (event.type == SDL_KEYUP)
				ft_check_key(doom, &event);
			else if (event.type == SDL_MOUSEBUTTONUP)
				ft_mouse_press_edit(doom, &event);
			else if (event.type == SDL_MOUSEBUTTONDOWN)
				ft_mouse_release_edit(doom, &event);
			else if (event.type == SDL_MOUSEMOTION)
				ft_mouse_move_edit(doom, &event);
			ft_bzero(doom->sdl.surface->pixels, WIN_HEIGHT * WIN_WIDTH * sizeof(Uint32));
		}
		ft_render_editor(doom);
		SDL_UpdateWindowSurface(doom->sdl.window);
		/**** CREATE FUNCTION: CHECK SAVE DEL ***/
		if (doom->editor.save_del == 1) //saving
		{
			if (ft_prepare_to_write(doom))
				ft_write_changes_to_file(doom, fd);
			doom->editor.save_del = 0;
		}
		else if (doom->editor.save_del == 3)
		{
			// if (!(ft_prepare_to_write(doom)))
				// printf("Не хватает данных для записи");
			if (ft_prepare_to_write(doom)) // функция должна возврщать инт чтобы проверить хватает ли данных 
			{
				ft_write_changes_to_file(doom, fd);
				return (game_mod(name));
			}
			doom->editor.save_del = 0;
		}
	}
	return (0);
}

void	ft_check_key(t_doom *doom, SDL_Event *event)
{
	int key;

	key = event->key.keysym.sym;
	if (ESC)
		doom->game.quit = 1;
}

void	 ft_render_editor(t_doom *doom)
{
	ft_render_interface(doom);
	ft_render_previous(doom);
	ft_render_other(doom);
}

void	ft_render_previous(t_doom *doom)
{
	int i;

	i = -1;
	doom->editor.brezen.color = 0xFFFFFF;
	doom->editor.interface.tmp_x1 = doom->editor.brezen.x1;
	doom->editor.interface.tmp_y1 = doom->editor.brezen.y1;
	doom->editor.interface.tmp_x2 = doom->editor.brezen.x2;
	doom->editor.interface.tmp_y2 = doom->editor.brezen.y2;
	while (++i < doom->editor.interface.nbr_vertex - 1)
	{
		if (doom->editor.interface.start_new_sector - 1 == i && doom->editor.interface.start_new_sector != 0)
			continue ;
		doom->editor.brezen.x1 = doom->editor.interface.arr_vertex_map_coor[i].x;
		doom->editor.brezen.y1 = doom->editor.interface.arr_vertex_map_coor[i].y;
		doom->editor.brezen.x2 = doom->editor.interface.arr_vertex_map_coor[i + 1].x;
		doom->editor.brezen.y2 = doom->editor.interface.arr_vertex_map_coor[i + 1].y;
		ft_line(doom);
	}
	doom->editor.brezen.x1 = doom->editor.interface.tmp_x1;
	doom->editor.brezen.y1 = doom->editor.interface.tmp_y1;
	doom->editor.brezen.x2 = doom->editor.interface.tmp_x2;
	doom->editor.brezen.y2 = doom->editor.interface.tmp_y2;
}

void	ft_render_other(t_doom *doom)
{
	doom->editor.brezen.color = 0xFFFFFF;
	if (doom->editor.is_drawing == 0 && doom->editor.but1_press == 1)
	{
		doom->editor.brezen.x1 = doom->editor.brezen.x2;
		doom->editor.brezen.y1 = doom->editor.brezen.y2;
		ft_line(doom);
		doom->editor.is_drawing = 1;
		doom->editor.but1_press = 0;
		doom->editor.is_sector = 0;
		write(1, "1\n", 2);
		
		doom->editor.interface.arr_vertex_map_coor[NUM_VER].x = doom->editor.brezen.x1;
		doom->editor.interface.arr_vertex_map_coor[NUM_VER++].y = doom->editor.brezen.y1;
		doom->editor.interface.nbr_vertex++;
	}
	else if (doom->editor.is_drawing == 1 && doom->editor.but1_press == 1)
	{
		ft_line(doom);
		doom->editor.brezen.x1 = doom->editor.brezen.x2;
		doom->editor.brezen.y1 = doom->editor.brezen.y2;
		doom->editor.is_drawing = 1;
		doom->editor.but1_press = 0;
		write(1, "2\n", 2);

		doom->editor.interface.arr_vertex_map_coor[NUM_VER].x = doom->editor.brezen.x1;
		doom->editor.interface.arr_vertex_map_coor[NUM_VER++].y = doom->editor.brezen.y1;
		doom->editor.interface.nbr_vertex++;
		// printf("doom->editor.brezen.x1: %d   NUM_SECT %d, NUM_VER %d\n", doom->editor.brezen.x1, NUM_SECT, NUM_VER);
	}
	else if (doom->editor.is_drawing == 1 && doom->editor.but1_press == 0)
	{
		ft_line(doom);
	}
}

void	ft_draw_axis(t_doom *doom)
{
	doom->editor.interface.tmp_x1 = doom->editor.brezen.x1;
	doom->editor.interface.tmp_y1 = doom->editor.brezen.y1;
	doom->editor.interface.tmp_x2 = doom->editor.brezen.x2;
	doom->editor.interface.tmp_y2 = doom->editor.brezen.y2;

	doom->editor.brezen.x1 = (WIN_WIDTH - 400) / 2;
	doom->editor.brezen.y1 = 0;
	doom->editor.brezen.x2 = (WIN_WIDTH - 400) / 2;
	doom->editor.brezen.y2 = WIN_HEIGHT;
	doom->editor.brezen.color = 0x333333;
	ft_line(doom);
	
	doom->editor.brezen.x1 = 0;
	doom->editor.brezen.y1 = WIN_HEIGHT / 2;
	doom->editor.brezen.x2 = WIN_WIDTH - 400;
	doom->editor.brezen.y2 = WIN_HEIGHT / 2;
	doom->editor.brezen.color = 0x333333;
	ft_line(doom);
	doom->editor.brezen.x1 = doom->editor.interface.tmp_x1;
	doom->editor.brezen.y1 = doom->editor.interface.tmp_y1;
	doom->editor.brezen.x2 = doom->editor.interface.tmp_x2;
	doom->editor.brezen.y2 = doom->editor.interface.tmp_y2;
}

void	info_ceil_floor(t_doom *doom)
{
	SDL_Surface		*message;
	SDL_Rect		rect;
	char			*str1;

	rect = (SDL_Rect){850, 230};
	SDL_BlitSurface(doom->editor.images[10].image, NULL, doom->sdl.surface, &rect);
	doom->editor.font.text_rect = (SDL_Rect){935, 275, 0, 0};
		str1 = ft_itoa(doom->map.sectors[0].ceil_plane.a);
	message = TTF_RenderText_Solid(doom->editor.font.text_font, str1, doom->editor.font.text_color);
	SDL_BlitSurface(message, NULL, doom->sdl.surface, &doom->editor.font.text_rect);
	doom->editor.font.text_rect.y += 30;
	free(str1);
	SDL_FreeSurface(message);
		str1 = ft_itoa(doom->map.sectors[0].ceil_plane.b);
	message = TTF_RenderText_Solid(doom->editor.font.text_font, str1, doom->editor.font.text_color);
	SDL_BlitSurface(message, NULL, doom->sdl.surface, &doom->editor.font.text_rect);
	doom->editor.font.text_rect.y += 30;
	free(str1);
	SDL_FreeSurface(message);
		str1 = ft_itoa(doom->map.sectors[0].ceil_plane.c);
	message = TTF_RenderText_Solid(doom->editor.font.text_font, str1, doom->editor.font.text_color);
	SDL_BlitSurface(message, NULL, doom->sdl.surface, &doom->editor.font.text_rect);
	doom->editor.font.text_rect.y += 30;
	free(str1);
	SDL_FreeSurface(message);
		str1 = ft_itoa(doom->map.sectors[0].ceil_plane.h);
	message = TTF_RenderText_Solid(doom->editor.font.text_font, str1, doom->editor.font.text_color);
	SDL_BlitSurface(message, NULL, doom->sdl.surface, &doom->editor.font.text_rect);
	doom->editor.font.text_rect.y += 30;
	free(str1);
	SDL_FreeSurface(message);
		str1 = ft_itoa(doom->map.sectors[0].ceil_z);
	message = TTF_RenderText_Solid(doom->editor.font.text_font, str1, doom->editor.font.text_color);
	SDL_BlitSurface(message, NULL, doom->sdl.surface, &doom->editor.font.text_rect);
	doom->editor.font.text_rect.x = 1070;
	doom->editor.font.text_rect.y = 277;
	free(str1);
	SDL_FreeSurface(message);
		str1 = ft_itoa(doom->map.sectors[0].floor_plane.a);
	message = TTF_RenderText_Solid(doom->editor.font.text_font, str1, doom->editor.font.text_color);
	SDL_BlitSurface(message, NULL, doom->sdl.surface, &doom->editor.font.text_rect);
	doom->editor.font.text_rect.y += 30;
	free(str1);
	SDL_FreeSurface(message);
		str1 = ft_itoa(doom->map.sectors[0].floor_plane.b);
	message = TTF_RenderText_Solid(doom->editor.font.text_font, str1, doom->editor.font.text_color);
	SDL_BlitSurface(message, NULL, doom->sdl.surface, &doom->editor.font.text_rect);
	doom->editor.font.text_rect.y += 30;
	free(str1);
	SDL_FreeSurface(message);
		str1 = ft_itoa(doom->map.sectors[0].floor_plane.c);
	message = TTF_RenderText_Solid(doom->editor.font.text_font, str1, doom->editor.font.text_color);
	SDL_BlitSurface(message, NULL, doom->sdl.surface, &doom->editor.font.text_rect);
	doom->editor.font.text_rect.y += 30;
	free(str1);
	SDL_FreeSurface(message);
		str1 = ft_itoa(doom->map.sectors[0].floor_plane.h);
	message = TTF_RenderText_Solid(doom->editor.font.text_font, str1, doom->editor.font.text_color);
	SDL_BlitSurface(message, NULL, doom->sdl.surface, &doom->editor.font.text_rect);
	doom->editor.font.text_rect.y += 30;
	free(str1);
	SDL_FreeSurface(message);
		str1 = ft_itoa(doom->map.sectors[0].floor_z);
	message = TTF_RenderText_Solid(doom->editor.font.text_font, str1, doom->editor.font.text_color);
	SDL_BlitSurface(message, NULL, doom->sdl.surface, &doom->editor.font.text_rect);
	SDL_FreeSurface(message);
	free(str1);
}

void	ft_render_interface(t_doom *doom)
{
	SDL_Rect	bigger;
	int			x;
	int			y;
	int			i;
	int			it[5]; // iterator to save space
	int			exist;
	int			color;

	i = 0;
	y = -1;
	bigger.w = 0;
	bigger.h = 0;
	bigger.y = 20;
	it[0] = 0;
	doom->editor.interface.is_drawing_interface = 1;
	
	while (++y < WIN_HEIGHT) // grey background
	{
		x = WIN_WIDTH - 401;
		while (++x < WIN_WIDTH)
			ft_draw_pixel(doom, x, y, 0x333333);
	}


	/* draw actions */
	bigger = (SDL_Rect){800, 130};
	SDL_BlitSurface(doom->editor.sector[3].image, NULL, doom->sdl.surface, &bigger);
	bigger.x = 1150;
	SDL_BlitSurface(doom->editor.sector[4].image, NULL, doom->sdl.surface, &bigger);
	bigger.x = 850;
	SDL_BlitSurface(doom->editor.images[doom->editor.press.ind_action].image, NULL, doom->sdl.surface, &bigger);
	/* ********** */

	/* draw ceil, floor */
	if (doom->editor.press.ind_action == 8) // leaks
		info_ceil_floor(doom);
	/* ********* */

	
	/* draw: save, delete, play */
	bigger = (SDL_Rect){10, 750, 250};
	SDL_BlitSurface(doom->editor.images[9].image, NULL, doom->sdl.surface, &bigger);
	/* ********** */
	
	if (doom->editor.press.ind_action == 7 || doom->editor.press.ind_action == 8)
	{
		y = 500;
		while (++y < WIN_HEIGHT - 150) // for textures 850/500 300x350
		{
			x = WIN_WIDTH - 350;
			while (++x < WIN_WIDTH - 50)
				ft_draw_pixel(doom, x, y, 0x001100);
			bigger.x = 1000;
			bigger.y = 550;
			SDL_BlitSurface(doom->editor.sector[3].image, NULL, doom->sdl.surface, &bigger);
			bigger.x = 1070;
			SDL_BlitSurface(doom->editor.sector[4].image, NULL, doom->sdl.surface, &bigger);
			bigger.x = 890;
			bigger.y = 530;
				SDL_BlitSurface(doom->editor.sector[doom->editor.ind_text].image, NULL, doom->sdl.surface, &bigger);
		}
	}
	y = 700;
	while (++y < WIN_HEIGHT - 30) // message of sector
	{
		x = WIN_WIDTH - 350;
		while (++x < WIN_WIDTH - 50)
			ft_draw_pixel(doom, x, y, 0);
	}
	ft_draw_axis(doom);
	bigger.y = 20;
	while (++it[0] < (NB_BUTTONS - 6))
	{
		exist = doom->editor.images[it[0]].exist;
		bigger.x = 700 + (it[0] * 100);
		if (doom->editor.ind_img != 0 && doom->editor.img_press == 1)
		{
			it[2] = 10;
			while (++it[2] < doom->editor.images[it[0]].image->w - 10)
			{
				it[1] = 10;
				while (++it[1] < doom->editor.images[it[0]].image->h - 10)
				{
					color = pix_from_text(doom->editor.images[it[0]].image, it[2], it[1]);
					if (color != -13421773) // color of background
						ft_draw_pixel(doom, doom->editor.images[it[0]].im_x[exist] + it[2], doom->editor.images[it[0]].im_y[exist] + it[1], color);
				}
			}
		}
		while (exist != 0)
		{
			it[2] = 10;
			while (++it[2] < doom->editor.images[it[0]].image->w - 10)
			{
				it[1] = 10;
				while (++it[1] < doom->editor.images[it[0]].image->h - 10)
				{
					color = pix_from_text(doom->editor.images[it[0]].image, it[2], it[1]);
					if (color != -13421773) // color of background
						ft_draw_pixel(doom, doom->editor.images[it[0]].im_x[exist] + it[2], doom->editor.images[it[0]].im_y[exist] + it[1], color);
				}
			}
			exist--;
		}
		SDL_BlitSurface(doom->editor.images[it[0]].image, NULL, doom->sdl.surface, &bigger);	
	}
	bigger.y = 710;
	bigger.x = 900;
	if (doom->editor.is_sector != 0)
		SDL_BlitSurface(doom->editor.sector[doom->editor.is_sector].image, NULL, doom->sdl.surface, &bigger);
	doom->editor.interface.is_drawing_interface = 0;
}

void	convex(t_doom *doom) // выпуклость
{
	double		product;
	t_vertex	ab;
	t_vertex	bc;
	t_vertex	*polig;
	int			i;
	
	polig = (t_vertex *)malloc(sizeof(t_vertex) * (NUM_VER * 999));
	i = -1;
	while (++i < NUM_VER - 1)
	{
		polig[i].x = doom->map.vertex[i + 1].x - doom->map.vertex[i].x;
		polig[i].y = doom->map.vertex[i + 1].y - doom->map.vertex[i].y;
	}
	printf("\n");
	int	j = -1;
	while (++j < (NUM_VER - 1)) // NUM_VER - 2 
	{
		if (j == 0)
		{
			ab.x = polig[j].x - polig[NUM_VER - 1].x;
			ab.y = polig[j].y - polig[NUM_VER - 1].y;
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
		product = ab.x * bc.y - ab.y * bc.x;
		if (product < 0)
		{
			i = -1;
			while (++i < NUM_VER) 
			{
				doom->map.vertex[i].y = 0;
				doom->map.vertex[i].x = 0;
			}
			printf("SECTOR ISN'T CONVEX\n");
			doom->editor.is_sector = 2;
			return ;

		}
		printf("             Product  %f\n", product);
	}
	printf("SECTOR IS CONVEX\n");
	doom->editor.is_sector = 1;
}

void	change_text(t_doom *doom, SDL_Event *event)
{
	int		i;

	if ((event->button.y >= 550 && event->button.y <= 600) && (event->button.x >= 1000 && event->button.x <= 1120))
	{
		if (NUM_SECT != 0)
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
	if (event->button.x < WIN_WIDTH - 400) // FIX на какой прямой лежит точка
	{
		// t_vertex	vert;
		// t_vertex	vert2;
		// double		product;
		t_vertex	point;
		double		p;
		double		p1;
		
		i = -1;
		point = (t_vertex){(event->button.x / 10), (event->button.y / 10)};
		while (++i < NUM_VER - 1)
		{
			p = (point.x - doom->map.vertex[i + 1].x) / (doom->map.vertex[i].x - doom->map.vertex[i + 1].x);
			p1 = (point.y - doom->map.vertex[i + 1].y) / (doom->map.vertex[i].y - doom->map.vertex[i + 1].y);
			// printf("p:  %0.2f         p1 %0.2f \n", (p * 10), (p1 * 10));
			if (((int)(p * 10) == (int)(p1 * 10)))
			{
				SDL_UpdateWindowSurface(doom->sdl.window);
				write(1, "\033[1;32m skhoditsa LINIA #", 25); //18
				write(1, ft_itoa(i + 1), 1);
				write(1, "\033[0m\n", 5);
				// printf("\033[1;32m skhoditsa LINIA #%d \033[0m\n\n", i + 1);
			}

		}
	}
}

int		is_in_sector(t_doom *doom, SDL_Event *event) // передавать сектор 
{
	int i = -1;
	if (event->button.x < WIN_WIDTH - 400) // FIX на какой прямой лежит точка
	{
		t_vertex	vert;
		t_vertex	vert2;
		t_vertex	point;
		double		product;

		point = (t_vertex){(event->button.x / 10), (event->button.y / 10)};
		i = -1;
		// doom->map.sectors[0].vert[0].x = 0;
		while (++i < NUM_VER - 1) //  на один больше (первый и последний)
		{
			vert = (t_vertex){(doom->map.vertex[i].x - point.x), (doom->map.vertex[i].y - point.y)};
			vert2 = (t_vertex){(doom->map.vertex[i + 1].x - point.x), (doom->map.vertex[i + 1].y - point.y)};
			product = vert.x * vert2.y - vert2.x * vert.y;
			if (product < 0)
			{
				printf("\033[1;31m POINT NOT IN THE SECTOR\033[0m\n\n");
				return (0);
			}
			// printf("product:   %f\n", product);
			// printf("x: %f   y: %f  choose\n", point.x, point.y);
			
		}
		printf("\033[1;32m POINT IN THE SECTOR\033[0m\n");
		printf("\n");
	}
		return (1);
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
				doom->map.vertex[NUM_VER].x = (event->button.x / 10);
				doom->map.vertex[NUM_VER].y = (event->button.y / 10);
			}
			if (event->button.button == SDL_BUTTON_RIGHT)
			{
				if (doom->editor.is_drawing == 0)
				{
					if (doom->editor.interface.nbr_vertex > 0)
					{
						doom->editor.interface.nbr_vertex--;
						NUM_VER--;
					}
				}
				//printf("new_sector_ver = %d\n", doom->editor.interface.start_new_sector);
				if ((doom->editor.interface.arr_vertex_map_coor[NUM_VER - 1].x == doom->editor.interface.arr_vertex_map_coor[doom->editor.interface.start_new_sector].x) && (doom->editor.interface.arr_vertex_map_coor[NUM_VER - 1].y == doom->editor.interface.arr_vertex_map_coor[doom->editor.interface.start_new_sector].y) && NUM_VER - 1 != doom->editor.interface.start_new_sector)
				{
					printf("Sector: %d done and it has %d vertexes!\n", NUM_SECT, NUM_VER - 1);
					convex(doom);
					if (doom->editor.is_sector == 1)
					{
						doom->editor.interface.sectors[NUM_SECT].num_vert = (NUM_VER - 1) - doom->editor.interface.start_new_sector;
						doom->editor.interface.start_new_sector = NUM_VER;
						NUM_SECT++;
					}
				}
				doom->editor.but1_press = 0;
				doom->editor.is_drawing = 0;
			}
	}
}

void	add_items(t_doom *doom, SDL_Event *event)
{
	if (event->button.x < (WIN_WIDTH - 400))
	{
		if (doom->editor.img_press == 1 && event->button.button == SDL_BUTTON_LEFT)
		{
			if (doom->editor.ind_img != 0)
			{
				if (!is_in_sector(doom, event)) // FIX not inside sector 
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
}

int		ft_specify_coor(int nbr)
{
	int last_nbr;

	last_nbr = fmod((float)nbr, 10);
	nbr = (nbr / 10) * 10;
	if (last_nbr > 4)
		nbr = nbr + 10;
	return (nbr);
}

void	ft_mouse_release_edit(t_doom *doom, SDL_Event *event)
{
	if (event->button.button == SDL_BUTTON_LEFT)
		doom->editor.but1_press = 0;
}

void	ft_mouse_move_edit(t_doom *doom, SDL_Event *event)
{
	int exist;
	
	exist = doom->editor.images[doom->editor.ind_img].exist;
	doom->editor.brezen.x2 = event->button.x;
	doom->editor.brezen.y2 = event->button.y;
	if (doom->editor.img_press != 0)
	{
		doom->editor.images[doom->editor.ind_img].im_x[exist] = (doom->editor.ind_img == 1 && exist == 4) ? doom->editor.images[doom->editor.ind_img].im_x[exist] : event->button.x - 50;
		doom->editor.images[doom->editor.ind_img].im_y[exist] = (doom->editor.ind_img == 1 && exist == 4) ? doom->editor.images[doom->editor.ind_img].im_y[exist] : event->button.y - 50;
	}
}


/* Save information in sector by using left/right */
/* разбить отдельно обработку секторов и кнопок */
/* */