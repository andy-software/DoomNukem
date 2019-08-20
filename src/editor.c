/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:26:08 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/19 22:31:52 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		ft_map_editor(t_doom *doom, char *name)
{
	int		fd;

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
	{
		if (ft_create_window(doom, name) != 1)
			exit(0);
	}
	ft_prepare_editor(doom, 0);
	ft_start_edit(doom, fd);
	if (doom->editor.save_del == 2)
		remove(doom->editor.name_m);
	free(doom->editor.name_m);
	close(fd);
	return (0);
}

int		ft_start_edit(t_doom *doom, int fd)
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
			else if (event.type == SDL_KEYDOWN)
				key_floor_ceil(doom);
			else if (event.type == SDL_MOUSEBUTTONUP)
				ft_mouse_press_edit(doom, &event);
			else if (event.type == SDL_MOUSEBUTTONDOWN)
				ft_mouse_release_edit(doom, &event);
			else if (event.type == SDL_MOUSEMOTION)
				ft_mouse_move_edit(doom, &event);
			ft_bzero(doom->editor.sdl.surface->pixels,
			WIN_HEIGHT * WIN_WIDTH * sizeof(Uint32));
		}
		ft_render_editor(doom);
		SDL_UpdateWindowSurface(doom->editor.sdl.window);
		check_save_del(doom, fd);
	}
	return (0);
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
		}
		if (event->button.button == SDL_BUTTON_RIGHT)
		{
			if (doom->map.sectors[doom->map.num_sect].num_vert > 2 && (doom->map.sectors[doom->map.num_sect].vert[0].x == doom->map.sectors[doom->map.num_sect].vert[(doom->map.sectors[doom->map.num_sect].num_vert - 1)].x && doom->map.sectors[doom->map.num_sect].num_vert > 2 &&
			doom->map.sectors[doom->map.num_sect].vert[0].y == doom->map.sectors[doom->map.num_sect].vert[(doom->map.sectors[doom->map.num_sect].num_vert - 1)].y))
			{
				doom->map.sectors[doom->map.num_sect].num_vert--;
				if (convex(doom, -1))
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
				if (doom->map.sectors[doom->map.num_sect].num_vert > 1)
				{
					doom->editor.brezen.x1 = (doom->map.sectors[doom->map.num_sect].vert[(doom->map.sectors[doom->map.num_sect].num_vert - 2)].x * SCL);
					doom->editor.brezen.y1 = (doom->map.sectors[doom->map.num_sect].vert[(doom->map.sectors[doom->map.num_sect].num_vert - 2)].y * SCL);
					doom->map.sectors[doom->map.num_sect].num_vert--;
				}
			}
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



void	make_portal(t_doom *doom, SDL_Event *event)
{
	if ((event->button.x >= 840 && event->button.x <= 1160)
	&& (event->button.y >= 630 && event->button.y <= 680))
	{
		if (doom->editor.fline.sec1 != -1 && doom->editor.fline.sec2 != -1)
		{
			if (doom->map.sectors[doom->editor.fline.sec1].neighbors[doom->editor.fline.num_line1] == -1)
			{
				doom->map.sectors[doom->editor.fline.sec1].neighbors[doom->editor.fline.num_line1]
				= doom->editor.fline.sec2;
				doom->map.sectors[doom->editor.fline.sec2].neighbors[doom->editor.fline.num_line2]
				= doom->editor.fline.sec1;
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
	if (event->button.x < WIN_WIDTH - 400)
		lie_point(doom, -1, event->button.x, event->button.y);
}


