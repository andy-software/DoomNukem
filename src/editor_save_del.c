/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 06:24:27 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/22 19:46:49 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static	int	ft_prepare_to_write(t_doom *doom, int i)
{
	if (!doom->map.num_sect || !doom->player.coord.y)
		return (0);
	INIT3(doom->player.coord.z, 10, doom->player.angle, 0, \
			doom->player.angle_z, 0);
	doom->player.anglecos = cosf(doom->player.angle);
	doom->player.anglesin = sinf(doom->player.angle);
	doom->map.num_sprites = IMG[2].exist + IMG[4].exist;
	while (++i < (int)doom->map.num_sprites)
	{
		MAP_SPRT[i].sector_no = is_in_sector(doom,
		(MAP_SPRT[i].coord.x * SCL), (MAP_SPRT[i].coord.y * SCL));
		if (MAP_SPRT[i].sector_no < 0)
			exit(0);
		INIT2(MAP_SPRT[i].live, 1, MAP_SPRT[i].draw, 1);
	}
	DEDI.fl_or_ceil = 1;
	IMG[1].im_x[1] = (doom->player.coord.x * SCL) - 48;
	IMG[1].im_y[1] = (doom->player.coord.y * SCL) - 48;
	doom->player.sector = is_in_sector(doom,
	(doom->player.coord.x * SCL), (doom->player.coord.y * SCL));
	if ((int)doom->player.sector < 0)
		exit(0);
	return (1);
}

void		check_save_del(t_doom *doom, int fd)
{
	if (doom->editor.save_del == 1)
	{
		if (ft_prepare_to_write(doom, -1))
			ft_write_changes_to_file(doom, fd);
		doom->editor.save_del = 0;
	}
	else if (doom->editor.save_del == 3)
	{
		if (ft_prepare_to_write(doom, -1))
		{
			doom->map.editing = 1;
			game_mod_editor(doom);
			doom->map.editing = 0;
			ft_prepare_to_write(doom, -1);
			ft_write_changes_to_file(doom, fd);
		}
		doom->editor.save_del = 0;
	}
}

void		del_save_play(t_doom *doom, SDL_Event *event)
{
	if (event->button.x <= 65 && (doom->editor.save_del = 2))
		doom->game.quit = 1;
	else if (event->button.x >= 65 && event->button.x <= 115)
		doom->editor.save_del = 1;
	else
		doom->editor.save_del = 3;
}

void		rec_action(t_doom *doom, SDL_Event *event)
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
