/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:18:31 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/05 21:19:00 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_draw_pixel(t_doom *doom, int x, int y, int color)
{
	int index;

	if (x < (WIN_WIDTH - 400) || doom->editor.interface.is_drawing_interface == 1)
	{
		index = doom->editor.sdl.surface->pitch * y + x * doom->editor.sdl.surface->format->BytesPerPixel;
		*(unsigned *)(doom->editor.sdl.surface->pixels + index) = color;
	}
}

int		ft_create_window(t_doom *doom, char *name) //norm
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
	if (!(doom->editor.sdl.window = SDL_CreateWindow("DOOM", 1500, \
		5, WIN_WIDTH, \
		WIN_HEIGHT, SDL_WINDOW_SHOWN)))
		return (error_message((char *)SDL_GetError()));
	if (!(doom->editor.sdl.surface = SDL_GetWindowSurface(doom->editor.sdl.window)))
		return (error_message((char *)SDL_GetError()));
	if (TTF_Init() < 0)
		return (error_message((char *)SDL_GetError()));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (error_message((char *)SDL_GetError()));
	doom->editor.font.text_color = (SDL_Color){255, 255, 250, 1};
	doom->editor.font.text_font = TTF_OpenFont("./materials/textures/editor/font.ttf", 30);
	while (++i < NB_BUTTONS) // download buttons
	{
		str2 = ft_itoa(i);
		str1 = ft_strjoin("./materials/textures/editor/photo", str2);
		str = ft_strjoin(str1, ".png");
		doom->editor.images[i].image = load_tex(str, doom->editor.sdl.surface->format->format);
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
		doom->editor.sector[i].image = load_tex(str, doom->editor.sdl.surface->format->format);
		free(str2); free(str); free(str1);
		if (!doom->editor.sector[i].image)
		printf ( "IMG_Load: %s\n", IMG_GetError());
	}
	name = 0; // use this parametr to name window
	if (load_all(&doom->texture, doom->editor.sdl.surface->format->format, doom) == 0) //
		return (error_message("Error with textures") + 1);
	SDL_UpdateWindowSurface(doom->editor.sdl.window);
	return (1);
}

void	key_editor_change(t_doom *doom, const Uint8 *state)
{
	if (state[SDL_SCANCODE_L] && state[SDL_SCANCODE_TAB] && doom->map.sectors[doom->player.sector].light_lvl > 0)
		doom->map.sectors[doom->player.sector].light_lvl--;
	else if (state[SDL_SCANCODE_L] && doom->map.sectors[doom->player.sector].light_lvl < 90)
		doom->map.sectors[doom->player.sector].light_lvl++;
}

void	key_texure_change(t_doom *doom, const Uint8 *state)
{
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
	SDL_BlitSurface(doom->editor.sector[3].image, NULL, doom->editor.sdl.surface, &bigger);
	bigger.x = 1150;
	SDL_BlitSurface(doom->editor.sector[4].image, NULL, doom->editor.sdl.surface, &bigger);
	bigger.x = 850;
	SDL_BlitSurface(doom->editor.images[doom->editor.press.ind_action].image, NULL, doom->editor.sdl.surface, &bigger);
	/* ********** */


	/* draw ceil, floor */
	if (doom->editor.press.ind_action == 8) // leaks
	{	
	// SDL_Rect kappa = (SDL_Rect){0, 0, doom->editor.images[10].image->w / 2, doom->editor.images[10].image->h / 2};
		bigger = (SDL_Rect){850, 230, 0, 0};
		if (doom->editor.fl_or_ceil == 1)
			SDL_BlitSurface(doom->editor.images[10].image, NULL, doom->editor.sdl.surface, &bigger);
		if (doom->editor.fl_or_ceil == 2)
			SDL_BlitSurface(doom->editor.images[11].image, NULL, doom->editor.sdl.surface, &bigger);
		info_ceil_floor(doom);
	}
	/* ********* */

	
	/* draw: save, delete, play */
	bigger = (SDL_Rect){10, 750, 250, 0};
		SDL_BlitSurface(doom->editor.images[9].image, NULL, doom->editor.sdl.surface, &bigger);
	/* ********** */
	
	/*  Make portal  */
	if (doom->editor.press.ind_action == 7)
	{
		bigger = (SDL_Rect){850, 420, 0, 0};
		if (doom->editor.is_portal == 0)
			SDL_BlitSurface(doom->editor.images[12].image, NULL, doom->editor.sdl.surface, &bigger);
		if (doom->editor.is_portal == 1) // если выбранна линия и мы нажали в 1115х450  1155х470
			SDL_BlitSurface(doom->editor.images[13].image, NULL, doom->editor.sdl.surface, &bigger);
	}
	/* ********** */

	/****  FOG  ****/
	if (doom->editor.press.ind_action == 5) //DRAW SECTOR // FIX add colors (0x00AAAA 0xFFFFFF 0x000000)
	{
		bigger = (SDL_Rect){840, 630, 0, 0};
		if (doom->map.fog == 1)
			SDL_BlitSurface(doom->editor.images[14].image, NULL, doom->editor.sdl.surface, &bigger);
		// if fog need to be removed
		else 
			SDL_BlitSurface(doom->editor.images[15].image, NULL, doom->editor.sdl.surface, &bigger);
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
			SDL_BlitSurface(doom->editor.sector[3].image, NULL, doom->editor.sdl.surface, &bigger);
			bigger.x = 1070;
			SDL_BlitSurface(doom->editor.sector[4].image, NULL, doom->editor.sdl.surface, &bigger);
			bigger.x = 890;
			bigger.y = 530;
				SDL_BlitSurface(doom->editor.sector[doom->editor.ind_text].image, NULL, doom->editor.sdl.surface, &bigger);
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
	while (++it[0] < (NB_BUTTONS - 12)) // minus
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
		while (exist != -1)
		{
			if (it[0] == 1 && exist == 0)
				break ;
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
		SDL_BlitSurface(doom->editor.images[it[0]].image, NULL, doom->editor.sdl.surface, &bigger);	
	}
	bigger.y = 710;
	bigger.x = 900;
	if (doom->editor.is_sector != 0)
		SDL_BlitSurface(doom->editor.sector[doom->editor.is_sector].image, NULL, doom->editor.sdl.surface, &bigger);
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
	if (doom->editor.img_press != 0 && (event->button.x > 30 && event->button.x < WIN_WIDTH - 30) &&(event->button.y > 30 && event->button.y < WIN_HEIGHT - 30))
	{
		doom->editor.images[doom->editor.ind_img].im_x[exist] = (doom->editor.ind_img == 1 && exist == 4) ? doom->editor.images[doom->editor.ind_img].im_x[exist] : event->button.x - 50;
		doom->editor.images[doom->editor.ind_img].im_y[exist] = (doom->editor.ind_img == 1 && exist == 4) ? doom->editor.images[doom->editor.ind_img].im_y[exist] : event->button.y - 50;
	}
}

void	info_f_c_w_s(t_doom *doom, int ind)
{
	if (ind == 1) // floor, ceil..
	{
		if (doom->editor.fl_or_ceil == FLOOR && (doom->editor.press.ind_action = 8))
			ft_putstr("\x1B[34m\n   FLOOR\x1B[0m\n");
		else if (doom->editor.fl_or_ceil == CEIL && (doom->editor.press.ind_action = 8))
			ft_putstr("\x1B[34m\n   CEILING\x1B[0m\n");
		else if (doom->editor.fl_or_ceil == WALL && (doom->editor.press.ind_action = 7) && (doom->editor.which_wall = MIDDLE))
			ft_putstr("\x1B[34m\n   WALL\n          middle wall\x1B[0m\n");
		else if (doom->editor.fl_or_ceil == SPRITES && (doom->editor.press.ind_action = 6))
			ft_putstr("\x1B[34m\n   SPRITES\x1B[0m\n");
	}
	else // wall
	{	
		if (doom->editor.which_wall == BOTTOM)
			ft_putstr("\x1B[34m          bottom wall \x1B[0m\n");
		else if (doom->editor.which_wall == MIDDLE)
			ft_putstr("\x1B[34m          middle wall \x1B[0m\n");
		else if (doom->editor.which_wall == TOP)
			ft_putstr("\x1B[34m          top    wall \x1B[0m\n");
	}
	
}

void	editor_scale_y(t_doom *doom, const Uint8 *state)
{
	if (doom->editor.fl_or_ceil == WALL)
	{
		doom->editor.nb_vert = check_what_line_player_are_looking(doom);
		if (doom->editor.which_wall == MIDDLE)
			doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].y_w_scale += (state[SDL_SCANCODE_TAB]) ? -0.1 : 0.1;
		else if (doom->editor.which_wall == BOTTOM)
			doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].y_b_scale += (state[SDL_SCANCODE_TAB]) ? -0.1 : 0.1;
		else if (doom->editor.which_wall == TOP)
			doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].y_t_scale += (state[SDL_SCANCODE_TAB]) ? -0.1 : 0.1;
	}
	if (doom->editor.fl_or_ceil == CEIL)
		doom->map.sectors[doom->player.sector].y_c_scale += (state[SDL_SCANCODE_TAB]) ? -0.01 : 0.01;
	if (doom->editor.fl_or_ceil == FLOOR)
		doom->map.sectors[doom->player.sector].y_f_scale += (state[SDL_SCANCODE_TAB]) ? -0.01 : 0.01;
}

void	editor_scale_x(t_doom *doom, const Uint8 *state)
{
	if (doom->editor.fl_or_ceil == WALL)
	{
		doom->editor.nb_vert = check_what_line_player_are_looking(doom);
		if (doom->editor.which_wall == MIDDLE)
			doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].x_w_scale += (state[SDL_SCANCODE_TAB]) ? -0.1 : 0.1;
		else if (doom->editor.which_wall == BOTTOM)
			doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].x_b_scale += (state[SDL_SCANCODE_TAB]) ? -0.1 : 0.1;
		else if (doom->editor.which_wall == TOP)
			doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].x_t_scale += (state[SDL_SCANCODE_TAB]) ? -0.1 : 0.1;
	}
	if (doom->editor.fl_or_ceil == CEIL)
		doom->map.sectors[doom->player.sector].x_c_scale += (state[SDL_SCANCODE_TAB]) ? -0.01 : 0.01;
	if (doom->editor.fl_or_ceil == FLOOR)
		doom->map.sectors[doom->player.sector].x_f_scale += (state[SDL_SCANCODE_TAB]) ? -0.01 : 0.01;
}

void	editor_wall_texture(t_doom *doom, const Uint8 *state)
{
	if (doom->editor.fl_or_ceil == WALL)
	{
		doom->editor.nb_vert = check_what_line_player_are_looking(doom);
		if (doom->editor.which_wall == MIDDLE)
		{
			if ((state[SDL_SCANCODE_TAB]) && doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].wall != 0)
				doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].wall--;
			else if (!(state[SDL_SCANCODE_TAB]) && doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].wall != NUM_TEXT)
				doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].wall++;
		}
		else if (doom->editor.which_wall == TOP)
		{
			if ((state[SDL_SCANCODE_TAB]) && doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].top != 0)
				doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].top--;
			else if (!(state[SDL_SCANCODE_TAB]) && doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].top != NUM_TEXT)
				doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].top++;
		}
		else if (doom->editor.which_wall == BOTTOM)
		{
			if ((state[SDL_SCANCODE_TAB]) && doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].bot != 0)
				doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].bot--;
			else if (!(state[SDL_SCANCODE_TAB]) && doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].bot != NUM_TEXT)
				doom->map.sectors[doom->player.sector].lines[doom->editor.nb_vert].bot++;
		}
	}
}

void	editor_fc_texture(t_doom *doom, const Uint8 *state)
{
	if (doom->editor.fl_or_ceil == FLOOR)
	{
		if ((state[SDL_SCANCODE_TAB]) && doom->map.sectors[doom->player.sector].floor_tex != 0)
			doom->map.sectors[doom->player.sector].floor_tex--;
		else if ( !(state[SDL_SCANCODE_TAB]) && doom->map.sectors[doom->player.sector].floor_tex != 5)
			doom->map.sectors[doom->player.sector].floor_tex++;
	}
	else if (doom->editor.fl_or_ceil == CEIL)
	{
		if ((state[SDL_SCANCODE_TAB]) && doom->map.sectors[doom->player.sector].ceil_tex != 0)
			doom->map.sectors[doom->player.sector].ceil_tex--;
		else if ( !(state[SDL_SCANCODE_TAB]) && doom->map.sectors[doom->player.sector].ceil_tex != 5)
			doom->map.sectors[doom->player.sector].ceil_tex++;
	}

}

void	editor_start_z(t_doom *doom, const Uint8 *state)
{
	int sp = check_what_sprite_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == SPRITES)
		doom->map.sprites[sp].start_z += (state[SDL_SCANCODE_TAB]) ? -1 : 1;
}

void	editor_end_z(t_doom *doom, const Uint8 *state)
{
	int sp = check_what_sprite_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == SPRITES)
		doom->map.sprites[sp].end_z += (state[SDL_SCANCODE_TAB]) ? -1 : 1;
}

void	editor_sp_width(t_doom *doom, const Uint8 *state)
{
	int sp = check_what_sprite_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == SPRITES)
		doom->map.sprites[sp].width += (state[SDL_SCANCODE_TAB]) ? -1 : 1;
	
}

void	editor_sprites_texture(t_doom *doom, const Uint8 *state)
{
	int sp = check_what_sprite_player_are_looking(doom);
	if (doom->editor.fl_or_ceil == SPRITES)
	{
		if (doom->map.sprites[sp].num_sheet == 8)
			doom->map.sprites[sp].num_sheet = 7;
		else
			doom->map.sprites[sp].num_sheet = 8;
	}
}

void	editor_player_events(t_doom *doom)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&doom->ev) && doom->game.quit != 1)
	{
		key_floor_ceil(doom);
		// key_texure_change(doom, state);
		key_editor_change(doom, state);
		if (doom->ev.type == SDL_KEYDOWN)
		{
			if (doom->ev.key.keysym.sym == SDLK_t)
			{
				editor_wall_texture(doom, state);
				editor_fc_texture(doom, state);
				editor_sprites_texture(doom, state);
			}
			else if (doom->ev.key.keysym.sym == SDLK_COMMA) // scale change by X
				editor_scale_x(doom, state);
			else if (doom->ev.key.keysym.sym == SDLK_PERIOD) // scale change by Y
				editor_scale_y(doom, state);
			else if (doom->ev.key.keysym.sym == SDLK_r)
			{
				if (doom->editor.fl_or_ceil == CEIL)
				{
					if (doom->map.sectors[doom->player.sector].render_ceil == 1)
						doom->map.sectors[doom->player.sector].render_ceil = 0;
					else
						doom->map.sectors[doom->player.sector].render_ceil = 1;
				}
			}
			else if (doom->ev.key.keysym.sym == SDLK_m)
				doom->map.editing = 0;
			else if (doom->ev.key.keysym.sym == SDLK_z)
				editor_start_z(doom, state);
			else if (doom->ev.key.keysym.sym == SDLK_x)
				editor_end_z(doom, state);
			else if (doom->ev.key.keysym.sym == SDLK_c)
				editor_sp_width(doom, state);
			if (doom->ev.key.keysym.sym == SDLK_PAGEUP || doom->ev.key.keysym.sym == SDLK_PAGEDOWN) // change wall/sprites/ceil
			{
				if (doom->ev.key.keysym.sym == SDLK_PAGEDOWN && doom->editor.fl_or_ceil > 1 &&  (doom->editor.fl_or_ceil--))
					info_f_c_w_s(doom, 1);
				else if (doom->ev.key.keysym.sym == SDLK_PAGEUP && doom->editor.fl_or_ceil < 4 && (doom->editor.fl_or_ceil++))
					info_f_c_w_s(doom, 1);
					
			}
			else if (doom->editor.fl_or_ceil == WALL && (doom->ev.key.keysym.sym == 1073741898 || doom->ev.key.keysym.sym == 1073741901))
			{
				if (doom->ev.key.keysym.sym == 1073741901 && doom->editor.which_wall > BOTTOM && (doom->editor.which_wall--))
					info_f_c_w_s(doom, 2);
				else if (doom->ev.key.keysym.sym ==  1073741898 && doom->editor.which_wall < TOP && (doom->editor.which_wall++))
					info_f_c_w_s(doom, 2);
			}
		}
	}
		ft_render_editor(doom);
		SDL_UpdateWindowSurface(doom->editor.sdl.window);
}