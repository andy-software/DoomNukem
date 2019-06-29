/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brezen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 16:06:26 by arudyi            #+#    #+#             */
/*   Updated: 2019/06/28 16:28:33 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_print_line_low(t_doom *doom)
{
	doom->editor.brezen.x2 = doom->editor.brezen.x1;
	doom->editor.brezen.y2 = doom->editor.brezen.y1;
	doom->editor.brezen.iterator = 1;
	while (doom->editor.brezen.iterator <= doom->editor.brezen.dx)
	{
		if (doom->editor.brezen.d >= 0)
		{
			doom->editor.brezen.d += doom->editor.brezen.d2;
			doom->editor.brezen.y2 += doom->editor.brezen.starty;
		}
		else
			doom->editor.brezen.d += doom->editor.brezen.d1;
		doom->editor.brezen.iterator++;
		doom->editor.brezen.x2 += doom->editor.brezen.startx;
		ft_draw_pixel(doom, doom->editor.brezen.x2, doom->editor.brezen.y2, doom->editor.brezen.color);
	}
}

void	ft_print_line_high(t_doom *doom)
{
	doom->editor.brezen.y2 = doom->editor.brezen.y1;
	doom->editor.brezen.x2 = doom->editor.brezen.x1;
	doom->editor.brezen.iterator = 1;
	while (doom->editor.brezen.iterator <= doom->editor.brezen.dy)
	{
		if (doom->editor.brezen.d >= 0)
		{
			doom->editor.brezen.d += doom->editor.brezen.d2;
			doom->editor.brezen.x2 += doom->editor.brezen.startx;
		}
		else
			doom->editor.brezen.d += doom->editor.brezen.d1;
		doom->editor.brezen.iterator++;
		doom->editor.brezen.y2 += doom->editor.brezen.starty;
		ft_draw_pixel(doom, doom->editor.brezen.x2, doom->editor.brezen.y2, doom->editor.brezen.color);
	}
}

void	ft_line(t_doom *doom)
{
	doom->editor.brezen.dx = abs(doom->editor.brezen.x2 - doom->editor.brezen.x1);
	doom->editor.brezen.dy = abs(doom->editor.brezen.y2 - doom->editor.brezen.y1);
	doom->editor.brezen.startx = doom->editor.brezen.x2 >= doom->editor.brezen.x1 ? 1 : -1;
	doom->editor.brezen.starty = doom->editor.brezen.y2 >= doom->editor.brezen.y1 ? 1 : -1;
	doom->editor.brezen.d = doom->editor.brezen.dy <= doom->editor.brezen.dx ? (doom->editor.brezen.dy << 1)
	- doom->editor.brezen.dx : (doom->editor.brezen.dx << 1) - doom->editor.brezen.dy;
	doom->editor.brezen.d1 = doom->editor.brezen.dy <= doom->editor.brezen.dx ? doom->editor.brezen.dy << 1
	: doom->editor.brezen.dx << 1;
	doom->editor.brezen.d2 = doom->editor.brezen.dy <= doom->editor.brezen.dx ?
	(doom->editor.brezen.dy - doom->editor.brezen.dx) << 1 :
	(doom->editor.brezen.dx - doom->editor.brezen.dy) << 1;
	ft_draw_pixel(doom, doom->editor.brezen.x1, doom->editor.brezen.y1, doom->editor.brezen.color);
	if (doom->editor.brezen.dy <= doom->editor.brezen.dx)
		ft_print_line_low(doom);
	else
		ft_print_line_high(doom);
}
