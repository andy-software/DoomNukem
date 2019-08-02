/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:18:31 by myuliia           #+#    #+#             */
/*   Updated: 2019/07/24 14:29:52 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_draw_pixel(t_doom *doom, int x, int y, int color)
{
	int index;

	if (x < (WIN_WIDTH - 400) || doom->editor.interface.is_drawing_interface == 1)
	{
		index = doom->sdl.surface->pitch * y + x * doom->sdl.surface->format->BytesPerPixel;
		*(unsigned *)(doom->sdl.surface->pixels + index) = color;
	}
}

int		ft_write_changes_to_file(t_doom *doom, int fd)
{
	
	p("\nIN FT_WRITE_CHANGES_TO_FILE\n");
	int i;

	write(fd, &doom->map.editing, sizeof(int));

	write(fd, &doom->map.fog, sizeof(int));
	write(fd, &doom->map.fog_color, sizeof(Uint32));

	write(fd, &doom->map.num_sect, sizeof(Uint32));
	
	i = -1;
	while (++i < (int)doom->map.num_sect)
	{
		write(fd, &doom->map.sectors[i].num, sizeof(Uint32));
		write(fd, &doom->map.sectors[i].num_vert, sizeof(Uint32));
		write(fd, doom->map.sectors[i].vert, sizeof(t_vertex) * doom->map.sectors[i].num_vert);
		write(fd, doom->map.sectors[i].lines, sizeof(t_line) * doom->map.sectors[i].num_vert);
		write(fd, doom->map.sectors[i].neighbors, sizeof(char) * doom->map.sectors[i].num_vert);
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

	write(fd, &doom->player, sizeof(t_player));
	write(fd, &doom->map.num_sprites, sizeof(Uint32));
	write(fd, doom->map.sprites, sizeof(t_sprite) * MAX_SPRITES_COUNT);
	write(fd, &doom->map.num_paint, sizeof(Uint32));
	write(fd, doom->map.paint, sizeof(t_painting) * doom->map.num_paint); //*//
	printf("Количесвто вертексов в сеторе 0: %d\n", doom->map.sectors[0].num_vert);
	return (1);
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
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG))
		return (error_message((char *)SDL_GetError()));
	if (!(doom->sdl.window = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, \
		WIN_HEIGHT, SDL_WINDOW_SHOWN)))
		return (error_message((char *)SDL_GetError()));
	if (!(doom->sdl.surface = SDL_GetWindowSurface(doom->sdl.window)))
		return (error_message((char *)SDL_GetError()));
	if (TTF_Init() < 0)
		return (error_message((char *)SDL_GetError()));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (error_message((char *)SDL_GetError()));
	// doom->editor.font.text_color.b = 200; // init font
	doom->editor.font.text_color = (SDL_Color){255, 255, 250, 1};
	doom->editor.font.text_font = TTF_OpenFont("./materials/textures/editor/font.ttf", 30);
	while (++i < NB_BUTTONS) // download buttons
	{
		str2 = ft_itoa(i);
		str1 = ft_strjoin("./materials/textures/editor/photo", str2);
		str = ft_strjoin(str1, ".png");
		doom->editor.images[i].image = load_tex(str, doom->sdl.surface->format->format);
		free(str2); free(str); free(str1);
		if (!doom->editor.images[i].image)
		printf ( "IMG_Load: %s\n", IMG_GetError());
	}
	i = 0;
	while (++i < NB_IMAGES)
	{
		str2 = ft_itoa(i);
		str1 = ft_strjoin("./materials/textures/editor/sector", str2);
		str = ft_strjoin(str1, ".png");
		doom->editor.sector[i].image = load_tex(str, doom->sdl.surface->format->format);
		free(str2); free(str); free(str1);
		if (!doom->editor.sector[i].image)
		printf ( "IMG_Load: %s\n", IMG_GetError());
	}
	name = 0; // use this parametr to name window

	//it will be here may couse seg faults
	if (load_all(&doom->texture, doom->sdl.surface->format->format, doom) == 0) //
		return (error_message("Error with textures") + 1);
	//

	SDL_UpdateWindowSurface(doom->sdl.window);
	return (1);
}

void	key_floor_ceil(t_doom *doom) // a, b, c, h, z - меняется на 0,1
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (doom->editor.fl_or_ceil == FLOOR)
	{
		if (!state[SDL_SCANCODE_LSHIFT])
		{
			if (state[SDL_SCANCODE_A] && doom->map.sectors[0].floor_plane.a < 50)
				doom->map.sectors[0].floor_plane.a += 0.1;
			else if (state[SDL_SCANCODE_B] && doom->map.sectors[0].floor_plane.b < 50)
				doom->map.sectors[0].floor_plane.b += 0.1;
			else if (state[SDL_SCANCODE_H] && doom->map.sectors[0].floor_plane.h < 50)
				doom->map.sectors[0].floor_plane.h += 0.1;
		}
		else if (state[SDL_SCANCODE_LSHIFT])
		{
			if (state[SDL_SCANCODE_A] && doom->map.sectors[0].floor_plane.a < 50)
				doom->map.sectors[0].floor_plane.a -= 0.1;
			else if (state[SDL_SCANCODE_B] && doom->map.sectors[0].floor_plane.b < 50)
				doom->map.sectors[0].floor_plane.b -= 0.1;
			else if (state[SDL_SCANCODE_H] && doom->map.sectors[0].floor_plane.h < 50)
				doom->map.sectors[0].floor_plane.h -= 0.1;
			}
	}
	if (doom->editor.fl_or_ceil == CEIL)
	{
		if (!state[SDL_SCANCODE_LSHIFT])
		{
			if (state[SDL_SCANCODE_A] && doom->map.sectors[0].ceil_plane.a < 50)
				doom->map.sectors[0].ceil_plane.a += 0.1;
			else if (state[SDL_SCANCODE_B] && doom->map.sectors[0].ceil_plane.b < 50)
				doom->map.sectors[0].ceil_plane.b += 0.1;
			else if (state[SDL_SCANCODE_H] && doom->map.sectors[0].ceil_plane.h < 50)
				doom->map.sectors[0].ceil_plane.h += 0.1;
		}
		else if (state[SDL_SCANCODE_LSHIFT])
		{
			if (state[SDL_SCANCODE_A] && doom->map.sectors[0].ceil_plane.a < 50)
				doom->map.sectors[0].ceil_plane.a -= 0.1;
			else if (state[SDL_SCANCODE_B] && doom->map.sectors[0].ceil_plane.b < 50)
				doom->map.sectors[0].ceil_plane.b -= 0.1;
			else if (state[SDL_SCANCODE_H] && doom->map.sectors[0].ceil_plane.h < 50)
				doom->map.sectors[0].ceil_plane.h -= 0.1;
		}
	}
}

void	ft_check_key(t_doom *doom, SDL_Event *event)
{
	int key;

	key = event->key.keysym.sym;
	if (ESC)
		doom->game.quit = 1;
}

void	ft_draw_axis(t_doom *doom)
{
	doom->editor.interface.tmp_x1 = doom->editor.brezen.x1;
	doom->editor.interface.tmp_y1 = doom->editor.brezen.y1;
	doom->editor.interface.tmp_x2 = doom->editor.brezen.x2;
	doom->editor.interface.tmp_y2 = doom->editor.brezen.y2;
	doom->editor.brezen.x1 = 400;
	doom->editor.brezen.y1 = 0;
	doom->editor.brezen.x2 = 400;
	doom->editor.brezen.y2 = 798;
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
	char			*str1;

	doom->editor.font.text_rect = (SDL_Rect){935, 275, 0, 0};
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
	doom->editor.font.text_rect.y += 31;
	free(str1);
	SDL_FreeSurface(message);
		str1 = ft_itoa(doom->map.sectors[0].floor_plane.h);
	message = TTF_RenderText_Solid(doom->editor.font.text_font, str1, doom->editor.font.text_color);
	SDL_BlitSurface(message, NULL, doom->sdl.surface, &doom->editor.font.text_rect);
	doom->editor.font.text_rect.x = 1070;
	doom->editor.font.text_rect.y = 277;
	free(str1);
	SDL_FreeSurface(message);
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
	doom->editor.font.text_rect.y += 31;
	free(str1);
	SDL_FreeSurface(message);
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
	bigger = (SDL_Rect){800, 130, 0, 0};
	SDL_BlitSurface(doom->editor.sector[3].image, NULL, doom->sdl.surface, &bigger);
	bigger.x = 1150;
	SDL_BlitSurface(doom->editor.sector[4].image, NULL, doom->sdl.surface, &bigger);
	bigger.x = 850;
	SDL_BlitSurface(doom->editor.images[doom->editor.press.ind_action].image, NULL, doom->sdl.surface, &bigger);
	/* ********** */


	/* draw ceil, floor */
	if (doom->editor.press.ind_action == 8) // leaks
	{	
	// SDL_Rect kappa = (SDL_Rect){0, 0, doom->editor.images[10].image->w / 2, doom->editor.images[10].image->h / 2};
		bigger = (SDL_Rect){850, 230, 0, 0};
		if (doom->editor.fl_or_ceil == 1)
			SDL_BlitSurface(doom->editor.images[10].image, NULL, doom->sdl.surface, &bigger);
		if (doom->editor.fl_or_ceil == 2)
			SDL_BlitSurface(doom->editor.images[11].image, NULL, doom->sdl.surface, &bigger);
		info_ceil_floor(doom);
	}
	/* ********* */

	
	/* draw: save, delete, play */
	bigger = (SDL_Rect){10, 750, 250, 0};
		SDL_BlitSurface(doom->editor.images[9].image, NULL, doom->sdl.surface, &bigger);
	/* ********** */
	
	/*  Make portal  */
	if (doom->editor.press.ind_action == 7)
	{
		bigger = (SDL_Rect){850, 420, 0, 0};
		if (doom->editor.is_portal == 0)
			SDL_BlitSurface(doom->editor.images[12].image, NULL, doom->sdl.surface, &bigger);
		if (doom->editor.is_portal == 1) // если выбранна линия и мы нажали в 1115х450  1155х470
			SDL_BlitSurface(doom->editor.images[13].image, NULL, doom->sdl.surface, &bigger);
	}
	/* ********** */

	/****  FOG  ****/
	if (doom->editor.press.ind_action == 5) //DRAW SECTOR // FIX add colors (0x00AAAA 0xFFFFFF 0x000000)
	{
		bigger = (SDL_Rect){840, 630, 0, 0};
		if (doom->map.fog == 1)
			SDL_BlitSurface(doom->editor.images[14].image, NULL, doom->sdl.surface, &bigger);
		// if fog need to be removed
		else 
			SDL_BlitSurface(doom->editor.images[15].image, NULL, doom->sdl.surface, &bigger);
	}
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
	while (++it[0] < (NB_BUTTONS - 11))
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
