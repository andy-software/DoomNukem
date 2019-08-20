/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 06:24:27 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/14 17:17:18 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	check_save_del(t_doom *doom, int fd)
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

void	del_save_play(t_doom *doom, SDL_Event *event)
{
	if (event->button.x <= 65 && (doom->editor.save_del = 2))
		doom->game.quit = 1;
	else if (event->button.x >= 65 && event->button.x <= 115)
		doom->editor.save_del = 1;
	else
		doom->editor.save_del = 3;
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
