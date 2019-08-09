/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_info_in_term.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:24:53 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/06 21:30:23 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	info_action(t_doom *doom, int pain)
{
	if (doom->map.paint[pain].event_num == TURN_LIG)
		ft_putstr("\x1B[33m          turn light event\x1B[0m\n");
	else if (doom->map.paint[pain].event_num == LIFT_FL)
		ft_putstr("\x1B[33m          lift floor event\x1B[0m\n");
	else if (doom->map.paint[pain].event_num == LIFT_CEIL)
		ft_putstr("\x1B[33m          lift ceil event\x1B[0m\n");
	else if (doom->map.paint[pain].event_num == FIRST_AID)
		ft_putstr("\x1B[33m          first aid event\x1B[0m\n");
	else if (doom->map.paint[pain].event_num == GET_AMMO)
		ft_putstr("\x1B[33m          get ammo event\x1B[0m\n");
	else if (doom->map.paint[pain].event_num == WIN_PNT)
		ft_putstr("\x1B[33m          win pnt event\x1B[0m\n");
}

void	info_f_c_w_s2(t_doom *doom)
{
	if (doom->editor.fl_or_ceil == FLOOR
	&& (doom->editor.press.ind_action = 8))
		ft_putstr("\x1B[34m\n   FLOOR\x1B[0m\n");
	else if (doom->editor.fl_or_ceil == CEIL
	&& (doom->editor.press.ind_action = 8))
		ft_putstr("\x1B[34m\n   CEILING\x1B[0m\n");
	else if (doom->editor.fl_or_ceil == WALL
	&& (doom->editor.press.ind_action = 7))
	{
		doom->editor.which_wall = MIDDLE;
		ft_putstr("\x1B[34m\n   WALL\n          middle wall\x1B[0m\n");
	}
	else if (doom->editor.fl_or_ceil == SPRITES
	&& (doom->editor.press.ind_action = 6))
		ft_putstr("\x1B[34m\n   SPRITES\x1B[0m\n");
	else if (doom->editor.fl_or_ceil == PAINTINGS
	&& (doom->editor.press.ind_action = 6))
		ft_putstr("\x1B[34m\n   PAINTINGS\x1B[0m\n");
}

void	info_f_c_w_s(t_doom *doom, int ind)
{
	if (ind == 1)
		info_f_c_w_s2(doom);
	else
	{
		if (doom->editor.which_wall == BOTTOM)
			ft_putstr("\x1B[34m          bottom wall \x1B[0m\n");
		else if (doom->editor.which_wall == MIDDLE)
			ft_putstr("\x1B[34m          middle wall \x1B[0m\n");
		else if (doom->editor.which_wall == TOP)
			ft_putstr("\x1B[34m          top    wall \x1B[0m\n");
	}
}