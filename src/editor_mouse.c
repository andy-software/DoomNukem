/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 20:59:40 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/22 17:24:27 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_mouse_press_edit(t_doom *doom, SDL_Event *event)
{
	if ((event->button.y >= 130 && event->button.y <= 180)
	&& (event->button.x >= 800 && event->button.x <= 1200))
		rec_action(doom, event);
	if ((event->button.y >= 750 && event->button.y <= 785)
	&& (event->button.x >= 25 && event->button.x <= 140))
		del_save_play(doom, event);
	else if (doom->editor.press.ind_action == 5)
		in_sector(doom, event);
	if (doom->editor.press.ind_action == 6)
		add_items(doom, event);
	if (doom->editor.press.ind_action == 7)
		make_portal(doom, event);
	if (doom->editor.press.ind_action == 8)
		change_floor_ceil(doom, event);
}

void	ft_mouse_move_edit(t_doom *doom, SDL_Event *event)
{
	int		exist;

	exist = doom->editor.images[doom->editor.ind_img].exist;
	doom->editor.brezen.x2 = event->button.x;
	doom->editor.brezen.y2 = event->button.y;
	if (doom->editor.img_press != 0 && (event->button.x > 30
	&& event->button.x < WIN_WIDTH - 30)
	&& (event->button.y > 30 && event->button.y < WIN_HEIGHT - 30))
	{
		doom->editor.images[doom->editor.ind_img].im_x[exist] =
		(doom->editor.ind_img == 1 && exist == 4) ?
		doom->editor.images[doom->editor.ind_img].im_x[exist]
		: event->button.x - 50;
		doom->editor.images[doom->editor.ind_img].im_y[exist] =
		(doom->editor.ind_img == 1 && exist == 4) ?
		doom->editor.images[doom->editor.ind_img].im_y[exist]
		: event->button.y - 50;
	}
}

void	ft_mouse_release_edit(t_doom *doom, SDL_Event *event)
{
	if (event->button.button == SDL_BUTTON_LEFT)
		doom->editor.but1_press = 0;
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
