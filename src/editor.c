/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:26:08 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/24 18:45:30 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int				ft_map_editor(t_doom *doom, char *name)
{
	INT1(fd);
	ft_prepare_read(doom);
	doom->editor.name_m = ft_strjoin("maps/", name);
	if (open(doom->editor.name_m, O_EXCL) > 0)
	{
		fd = open(doom->editor.name_m, O_RDONLY);
		ft_read_map_edit(doom, fd);
		close(fd);
		fd = open(doom->editor.name_m, O_WRONLY);
	}
	else
		fd = open(doom->editor.name_m, O_CREAT | O_WRONLY);
	if (fd < 0)
		return (error_message("fd is bad :(\n") + 1);
	if (doom->editor.save_del != 2)
		if (ft_create_window(doom, name) != 1)
			exit(0);
	ft_prepare_editor(doom, 0);
	ft_start_edit(doom, fd);
	if (doom->editor.save_del == 2)
		remove(doom->editor.name_m);
	free(doom->editor.name_m);
	close(fd);
	return (0);
}

int				ft_start_edit(t_doom *doom, int fd)
{
	SDL_Event	event;

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
			ft_bzero(SDL_SURF->pixels, WIN_HEIGHT * WIN_WIDTH * sizeof(Uint32));
		}
		ft_render_editor(doom);
		SDL_UpdateWindowSurface(doom->editor.sdl.window);
		check_save_del(doom, fd);
	}
	return (0);
}

static	void	check_position(t_doom *doom)
{
	if (MAPS_NUM.num_vert > 2 && (MAPS_NUM.vert[0].x == \
	MAPS_NUM.vert[(MAPS_NUM.num_vert - 1)].x && MAPS_NUM.num_vert > 2 \
	&& MAPS_NUM.vert[0].y == MAPS_NUM.vert[(MAPS_NUM.num_vert - 1)].y))
	{
		MAPS_NUM.num_vert--;
		if (convex(doom, -1))
		{
			NUM_SECT++;
			MAPS_NUM.num_vert = 0;
			doom->editor.is_drawing = 0;
			doom->editor.is_sector = 1;
		}
		else
		{
			MAPS_NUM.num_vert++;
			doom->editor.is_drawing = 1;
		}
	}
	if (doom->editor.is_drawing == 1 && MAPS_NUM.num_vert > 1)
	{
		DBRZ.x1 = (MAPS_NUM.vert[(MAPS_NUM.num_vert - 2)].x * SCL);
		DBRZ.y1 = (MAPS_NUM.vert[(MAPS_NUM.num_vert - 2)].y * SCL);
		MAPS_NUM.num_vert--;
	}
	doom->editor.but1_press = 0;
}

void			in_sector(t_doom *doom, SDL_Event *event)
{
	if (event->button.x < (WIN_WIDTH - 400))
	{
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			DBRZ.x2 = ft_specify_coor(event->button.x);
			DBRZ.y2 = ft_specify_coor(event->button.y);
			doom->editor.but1_press = 1;
		}
		if (event->button.button == SDL_BUTTON_RIGHT)
			check_position(doom);
	}
	if ((event->button.x >= 840 && event->button.x <= (840 + 325)) && \
		(event->button.y >= 630 && event->button.y <= (630 + 55)))
	{
		if (doom->map.fog == 1)
			doom->map.fog = 0;
		else
			doom->map.fog = 1;
	}
}

void			make_portal(t_doom *doom, SDL_Event *event)
{
	if ((event->button.x >= 840 && event->button.x <= 1160) && \
		(event->button.y >= 630 && event->button.y <= 680))
	{
		if (DEFLN.sec1 != -1 && DEFLN.sec2 != -1)
		{
			if (MAPSEC[DEFLN.sec1].neighbors[DEFLN.num_line1] == -1)
			{
				MAPSEC[DEFLN.sec1].neighbors[DEFLN.num_line1] = DEFLN.sec2;
				MAPSEC[DEFLN.sec2].neighbors[DEFLN.num_line2] = DEFLN.sec1;
				doom->editor.is_portal = 1;
			}
			else
			{
				MAPSEC[DEFLN.sec1].neighbors[DEFLN.num_line1] = -1;
				MAPSEC[DEFLN.sec2].neighbors[DEFLN.num_line2] = -1;
				doom->editor.is_portal = 0;
			}
		}
	}
	if (event->button.x < WIN_WIDTH - 400)
		lie_point(doom, event->button.x, event->button.y);
}
