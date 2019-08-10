/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:26:08 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/10 15:32:35 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"


int		ft_map_editor(t_doom *doom, char *name)
{
	p("\nIN FT_MAP_EDITOR\n");
	int		fd;

	doom->editor.name_m = ft_strjoin("maps/", name);
	ft_prepare_read(doom);
	if (open(doom->editor.name_m, O_EXCL) > 0)
	{
		fd = open(doom->editor.name_m, O_RDONLY);
		ft_read_map_edit(doom, fd);
		printf("doom->map.paint[0].event: %d, \n", doom->map.paint[0].event_num);
		printf("doom->map.paint[0].key: %d, \n", doom->map.paint[0].key);
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
	ft_prepare_editor(doom);
	ft_start_edit(doom, fd);
	if (doom->editor.save_del == 2)
		remove(doom->editor.name_m);
	free(doom->editor.name_m);
	close(fd);
	return (0);
}

int		ft_prepare_to_write(t_doom *doom)
{
	int		i;

	i = -1;
	if (!doom->map.num_sect || !doom->player.coord.y)
	{
		ft_putstr("Nothing to store:(\n");
		return (0);
	}
	doom->player.coord.z = 10;
	doom->player.angle = 0;
	doom->player.angle_z = 0;
	doom->player.anglecos = cosf(doom->player.angle);
	doom->player.anglesin = sinf(doom->player.angle);

	doom->map.num_sprites = doom->editor.images[2].exist + doom->editor.images[4].exist;
	//printf(" doom->editor.images[2].exist:  %d +   doom->editor.images[4].exist:  %d = doom->map.num_sprites   %d\n\n", doom->editor.images[2].exist, doom->editor.images[4].exist, doom->map.num_sprites);
	i = -1;
	while (++i < (int)doom->map.num_sprites)
	{
		doom->map.sprites[i].sector_no = is_in_sector(doom, (doom->map.sprites[i].coord.x * 10), (doom->map.sprites[i].coord.y * 10));
		doom->map.sprites[i].live = 1;
		doom->map.sprites[i].draw = 1;
		doom->map.sprites[i].own_moves = i;
		// doom->map.sprites[i].spr_num = i;
		// doom->editor.images[2].im_x[i] = (doom->map.sprites[i].coord.x * 10) - 50;
		// doom->editor.images[2].im_y[i] = (doom->map.sprites[i].coord.y * 10) - 50;
	}

	doom->editor.fl_or_ceil = 1;
	doom->editor.images[1].im_x[1] = (doom->player.coord.x * 10) - 48;
	doom->editor.images[1].im_y[1] = (doom->player.coord.y * 10) - 48;
	doom->player.sector = is_in_sector(doom, (doom->player.coord.x * 10), (doom->player.coord.y * 10));
	// remove(doom->editor.name_m);
	// int fd = open(doom->editor.name_m, O_CREAT | O_WRONLY);
	return (1);
}

void	ft_prepare_editor(t_doom *doom)
{
	p("\nIN FT_PREPARE_EDITOR\n");
	int		i;

	i = 0;
	doom->game.quit = 0;
	doom->editor.but1_press = 0;
	doom->editor.is_drawing = 0;
	doom->editor.is_portal = 0;
	doom->editor.ind_img = 0;
	doom->editor.is_sector = 1;
	doom->editor.ind_text = 5;
	doom->editor.img_press = 0;
	doom->editor.press.ind_action = 5;
	doom->editor.save_del = 0;
	doom->editor.fl_or_ceil = 1;
	if (doom->editor.save_del == 2)
		doom->editor.save_del = 0;
	doom->editor.interface.is_drawing_interface = 0;
	doom->editor.interface.start_new_sector = 0;
	while (++i < NB_BUTTONS)
	{
		doom->editor.images[i].im_x = (double *)malloc(sizeof(double) * 100);
		doom->editor.images[i].im_y = (double *)malloc(sizeof(double) * 100);
		ft_null_items(doom, i, 0);
		ft_null_items(doom, i, 1);
		doom->editor.images[i].exist = 0;
	}
	/***** fog ****/
	doom->editor.ind_fog = 0; 
	/****   To make objects visible on map (player, sprite..)  *****/
	if (doom->player.coord.x && doom->player.coord.y)
	{
		doom->editor.images[1].exist = 1;
		doom->editor.images[1].im_x[1] = (doom->player.coord.x * 10) - 50;
		doom->editor.images[1].im_y[1] = (doom->player.coord.y * 10) - 50;
		doom->editor.images[2].exist = doom->map.num_sprites;
		i = -1;
		ft_null_items(doom, 2, doom->map.num_sprites);
		while (++i < (int)doom->map.num_sprites)
		{
			doom->editor.images[2].im_x[i] = (doom->map.sprites[i].coord.x * 10) - 50;
			doom->editor.images[2].im_y[i] = (doom->map.sprites[i].coord.y * 10) - 50;
		}
		i = -1;
		doom->editor.images[3].exist = doom->map.num_paint;
		ft_null_items(doom, 3, doom->map.num_paint);
		while (++i < (int)doom->map.num_paint)
		{
			doom->editor.images[3].im_x[i] = (doom->map.paint[i].v1.x * 10) - 50;
			doom->editor.images[3].im_y[i] = (doom->map.paint[i].v1.y * 10) - 50;
		}
		// doom->editor.images[4].exist = doom->map.num_;
		// ft_null_items(doom, 4, doom->map.num_);
		// while (++i < (int)doom->map.num_)
		// {
		// 	doom->editor.images[4].im_x[i] = (doom->map.paint[i].v1.x * 10) - 50;
		// 	doom->editor.images[4].im_y[i] = (doom->map.paint[i].v1.y * 10) - 50;
		// }
	}
	doom->editor.fline.num_line1 = -1;
	doom->editor.fline.num_line2 = -1;
	doom->editor.fline.sec1 = -1;
	doom->editor.fline.sec2 = -1;
	doom->player.sector = 0;
	doom->editor.which_wall = BOTTOM;
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
			ft_bzero(doom->editor.sdl.surface->pixels, WIN_HEIGHT * WIN_WIDTH * sizeof(Uint32));
		}
		ft_render_editor(doom);
		SDL_UpdateWindowSurface(doom->editor.sdl.window);
		if (doom->editor.save_del == 1)
		{
			if (ft_prepare_to_write(doom))
				ft_write_changes_to_file(doom, fd);
			doom->editor.save_del = 0;
		}
		else if (doom->editor.save_del == 3)
		{
			if (ft_prepare_to_write(doom))
			{
				doom->map.editing = 1;
				game_mod_editor(doom);
				doom->map.editing = 0;
				ft_prepare_to_write(doom);
				ft_write_changes_to_file(doom, fd);
			}
			doom->editor.save_del = 0;
		}
	}
	return (0);
}

void	rec_action(t_doom *doom, SDL_Event *event)
{
	if (event->button.x <= 850)
	{
		doom->editor.press.ind_action--;
		if (doom->editor.press.ind_action == 4)
			doom->editor.press.ind_action = 8;
	}
	if (event->button.x >= WIN_WIDTH - 50)
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
					doom->editor.brezen.x1 = (doom->map.sectors[doom->map.num_sect].vert[(doom->map.sectors[doom->map.num_sect].num_vert - 2)].x * 10);
					doom->editor.brezen.y1 = (doom->map.sectors[doom->map.num_sect].vert[(doom->map.sectors[doom->map.num_sect].num_vert - 2)].y * 10);
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

void	add_items(t_doom *doom, SDL_Event *event)
{
	if (event->button.x < (WIN_WIDTH - 400))
	{
		if (doom->editor.img_press == 1 && event->button.button == SDL_BUTTON_LEFT)
		{
			if (doom->editor.ind_img != 0)
			{
				if (doom->editor.ind_img != 3 && is_in_sector(doom, event->button.x, event->button.y) == -1)
				{
						if (doom->editor.images[doom->editor.ind_img].exist != 0)
							doom->editor.images[doom->editor.ind_img].exist--;
							doom->editor.img_press = 1;
				}
				else
				{
					ft_null_items(doom, doom->editor.ind_img, EXIST + 1);
					// if (doom->editor.ind_img == 2)
					// 	doom->map.sprites[doom->editor.images[doom->editor.ind_img].exist - 1].coord = (t_vector){event->button.x / 10, event->button.y / 10, 10};
					if (doom->editor.ind_img == 2)
					{
						if (doom->editor.images[4].exist > -1)
						{
							doom->map.sprites[(doom->editor.images[2].exist + doom->editor.images[4].exist) - 1].coord = (t_vector){event->button.x / 10, event->button.y / 10, 10};
							doom->map.sprites[(doom->editor.images[2].exist + doom->editor.images[4].exist) - 1].pick = 0;
						}
					}
					else if (doom->editor.ind_img == 4)
					{
						if (doom->editor.images[2].exist > -1)
						{
							doom->map.sprites[(doom->editor.images[2].exist + doom->editor.images[4].exist) - 1].coord = (t_vector){event->button.x / 10, event->button.y / 10, 10};
							doom->map.sprites[(doom->editor.images[2].exist + doom->editor.images[4].exist) - 1].pick = 1;
							doom->map.sprites[(doom->editor.images[2].exist + doom->editor.images[4].exist) - 1].mob = 0;
						}
					}
					else if (doom->editor.ind_img == 1)
					{
						if (doom->editor.images[1].exist == 1)
							if (doom->editor.ind_img == 1)
							{
								doom->player.coord.x = event->button.x / 10;
								doom->player.coord.y = event->button.y / 10;
							}
						doom->editor.images[doom->editor.ind_img].exist = 1;
					}
					else if (doom->editor.ind_img == 3)
					{
						lie_point(doom, -1, event->button.x, event->button.y);
						if (doom->editor.fline.sec2 == -1 && doom->editor.fline.sec1 != -1)
						{
							t_painting	*p = &doom->map.paint[doom->editor.images[3].exist - 1];
							t_vertex	line_param;
							const float 		width = 5;
							
							t_vertex dot_1 = doom->map.sectors[doom->editor.fline.sec1].vert[doom->editor.fline.num_line1];
							t_vertex dot_2;
							if (doom->editor.fline.num_line1 + 1 != (int)doom->map.sectors[doom->editor.fline.sec1].num_vert)
								dot_2 = doom->map.sectors[doom->editor.fline.sec1].vert[doom->editor.fline.num_line1 + 1];
							else
								dot_2 = doom->map.sectors[doom->editor.fline.sec1].vert[0];
							
							line_param = get_line_param(dot_1.x, dot_1.y, dot_2.x, dot_2.y);
							if (!comp_real(dot_1.x, dot_2.x, 0.0001))
							{
								if (dot_1.x < dot_2.x)
								{
									p->v1.x = event->button.x / 10 - width / (2 * sqrt(1 + line_param.x * line_param.x));
									p->v2.x = event->button.x / 10 + width / (2 * sqrt(1 + line_param.x * line_param.x));
									p->v1.y = p->v1.x * line_param.x + line_param.y;
									p->v2.y = p->v2.x * line_param.x + line_param.y;
								}
								else
								{
									p->v1.x = event->button.x / 10 + width / (2 * sqrt(1 + line_param.x * line_param.x));
									p->v2.x = event->button.x / 10 - width / (2 * sqrt(1 + line_param.x * line_param.x));
									p->v1.y = p->v1.x * line_param.x + line_param.y;
									p->v2.y = p->v2.x * line_param.x + line_param.y;
								}
							}
							else
							{
								p->v1.x = event->button.x / 10;
								p->v2.x = event->button.x / 10;
								if (dot_1.y < dot_2.y)
								{
									p->v1.y = event->button.y / 10 - width;
									p->v2.y = event->button.y / 10 + width;
								}
								else
								{
									p->v1.y = event->button.y / 10 + width;
									p->v2.y = event->button.y / 10 - width;
								}
							}
							doom->map.paint[doom->editor.images[3].exist - 1].sector_no = doom->editor.fline.sec1;
							doom->map.num_paint = doom->editor.images[3].exist;
							printf("doom->editor.images[3].exist: %d\n", doom->editor.images[3].exist);
							printf("sheet: %d\n", doom->map.paint[0].num_sheet);
							// doom->map.paint[doom->editor.images[3].exist - 1].v1.x = event->button.x / 10;
							// doom->map.paint[doom->editor.images[3].exist - 1].v1.y = event->button.y / 10;
							// doom->map.paint[doom->editor.images[3].exist - 1].v2.x = (event->button.x / 10) + 3;
							// doom->map.paint[doom->editor.images[3].exist - 1].v2.y = event->button.y / 10 + 3;
						}
						else
						{
							if (doom->editor.images[doom->editor.ind_img].exist != 0)
								doom->editor.images[doom->editor.ind_img].exist--;
							doom->editor.img_press = 1;
						}
						
						// doom->editor.fline.num_line1 = i;
						// doom->editor.fline.num_line2 = -1;
						// doom->editor.fline.sec1 = k;
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
		if (event->button.button == SDL_BUTTON_RIGHT)
		{
			doom->editor.ind_img = ((event->button.x / 100) - 7);	
			ft_null_items(doom, doom->editor.ind_img, 0);
			if (doom->editor.images[doom->editor.ind_img].exist != 0)
				doom->editor.images[doom->editor.ind_img].exist--;
		}
	}
}

void	del_save_play(t_doom *doom, SDL_Event *event)
{
	if (event->button.x <= 65 && (doom->editor.save_del = 2))
		doom->game.quit = 1;
	else if (event->button.x >= 65 && event->button.x <= 115)
		doom->editor.save_del = 1;
	else
		doom->editor.save_del = 3;
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

void	lie_point(t_doom *doom, int k, int x, int y)
{
	t_vertex	point;
	int			more;
	double		koef;
	double		c;
	int			i;
	t_vertex	*v1;
	t_vertex	*v2;

	more = 0;
	k = -1;
	point = (t_vertex){(x / 10), (y / 10)};
	//	printf("x: %d            y: %d\n", x, y);
	while (++k < (int)doom->map.num_sect)
	{
		i = -1;
		while (++i < (int)doom->map.sectors[k].num_vert)
		{
	// 			if (comp_real(doom->map.sectors[k].vert[i + 1].x, doom->map.sectors[k].vert[i].x, 2))
	// 			{
	// 					ft_putstr("\033[1;32m Line coincides2\033[0m\n");
	// 				if (comp_real(point.x, doom->map.sectors[k].vert[i].x, 2))
	// 					ft_putstr("\033[1;32m Line coincides3\033[0m\n");
	// 				if (point.y >= min(doom->map.sectors[k].vert[i].y, doom->map.sectors[k].vert[i + 1].y))
	// 					ft_putstr("\033[1;32m Line coincides5\033[0m\n");
	// 				if (doom->map.sectors[k].vert[i].x <= max(doom->map.sectors[k].vert[i].y, doom->map.sectors[k].vert[i + 1].y))
	// 				{
	// // pritnf(doom->map.sectors[k].vert[i].x);
	// 					ft_putstr("\033[1;32m Line coincides6\033[0m\n\n");
	// 				}
					
	// 			}

				if (i + 1 < (int)doom->map.sectors[k].num_vert)
				{
					v2 = doom->map.sectors[k].vert + i + 1;
					v1 = doom->map.sectors[k].vert + i;
				}
				else
				{
					v2 = doom->map.sectors[k].vert;
					v1 = doom->map.sectors[k].vert + i;
				}


				
				if (comp_real(v2->x, v1->x, 2) && comp_real(point.x, v1->x, 2)) //configurate
				{
					printf("im on vertical line\n");
					if (more == 0 && comp_real(clamp(point.y, min(v2->y, v1->y), max(v2->y, v1->y)), point.y, 0.001))
					{
						printf("first if\n");
						ft_putstr("\033[1;32m Line coincides\033[0m\n");
						doom->editor.fline.num_line1 = i;
						doom->editor.fline.num_line2 = -1;
						doom->editor.fline.sec1 = k;
						doom->editor.fline.sec2 = -1;
						doom->editor.is_portal = 2;
						more++;
						break ;
					}
					else if (more == 1 && comp_real(clamp(point.y, min(v2->y, v1->y), max(v2->y, v1->y)), point.y, 0.001))
					{
						printf("second if\n");
						if (doom->map.sectors[doom->editor.fline.sec1].neighbors[doom->editor.fline.num_line1] == -1)
							doom->editor.is_portal = 0;
						else
							doom->editor.is_portal = 1;
						doom->editor.fline.num_line2 = i;
						doom->editor.fline.sec2 = k;
					}
					else if (more == 0)
					{
						printf("third if\n");
						doom->editor.fline.num_line1 = -1;
						doom->editor.fline.num_line2 = -1;
						doom->editor.fline.sec1 = -1;
						doom->editor.fline.sec2 = -1;
						doom->editor.is_portal = 2;
					}
				}
				else
				{
					koef = (v2->y - v1->y) / (v2->x - v1->x);
					c = v1->y - (koef * v1->x);
				
					if (more == 0 && comp_real(point.y, (point.x * koef + c), 1) &&
					(point.x > min(v1->x, v2->x)) &&
					(point.x < max(v1->x, v2->x)) &&
					(point.y > min(v1->y, v2->y)) &&
					(point.y < max(v1->y, v2->y))) //make a boundary check
					{
						ft_putstr("\033[1;32m Line coincides\033[0m\n");
						doom->editor.fline.num_line1 = i;
						doom->editor.fline.num_line2 = -1;
						doom->editor.fline.sec1 = k;
						doom->editor.fline.sec2 = -1;
						doom->editor.is_portal = 2;
						more++;
						break ;
					}
					else if (more == 1 && comp_real(point.y, (point.x * koef + c), 2) &&
					(point.x > min(v1->x, v2->x)) &&
					(point.x < max(v1->x, v2->x)) &&
					(point.y > min(v1->y, v2->y)) &&
					(point.y < max(v1->y, v2->y)))
					{
						if (doom->map.sectors[doom->editor.fline.sec1].neighbors[doom->editor.fline.num_line1] == -1)
							doom->editor.is_portal = 0;
						else
							doom->editor.is_portal = 1;
						doom->editor.fline.num_line2 = i;
						doom->editor.fline.sec2 = k;
					}
					else if (more == 0)
					{
						doom->editor.fline.num_line1 = -1;
						doom->editor.fline.num_line2 = -1;
						doom->editor.fline.sec1 = -1;
						doom->editor.fline.sec2 = -1;
						doom->editor.is_portal = 2;
					}
				}
		}
	}
	printf("\033[1;34m   num_line1: %d\n   num_line2: %d\n   sec1: %d\n   sec2: %d \033[0m\n\n", doom->editor.fline.num_line1, doom->editor.fline.num_line2, doom->editor.fline.sec1, doom->editor.fline.sec2);
}
