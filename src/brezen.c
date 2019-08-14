/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brezen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 13:54:29 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/13 21:12:34 by myuliia          ###   ########.fr       */
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
			doom->editor.brezen.y2 += BSTARTY;
		}
		else
			doom->editor.brezen.d += doom->editor.brezen.d1;
		doom->editor.brezen.iterator++;
		doom->editor.brezen.x2 += BSTARTX;
		ft_draw_pixel(doom, doom->editor.brezen.x2,
		doom->editor.brezen.y2, doom->editor.brezen.color);
	}
}

void	ft_print_line_high(t_doom *doom)
{
	doom->editor.brezen.y2 = doom->editor.brezen.y1;
	doom->editor.brezen.x2 = doom->editor.brezen.x1;
	doom->editor.brezen.iterator = 1;
	while (doom->editor.brezen.iterator <= BDY)
	{
		if (doom->editor.brezen.d >= 0)
		{
			doom->editor.brezen.d += doom->editor.brezen.d2;
			doom->editor.brezen.x2 += BSTARTX;
		}
		else
			doom->editor.brezen.d += doom->editor.brezen.d1;
		doom->editor.brezen.iterator++;
		doom->editor.brezen.y2 += BSTARTY;
		ft_draw_pixel(doom, doom->editor.brezen.x2,
		doom->editor.brezen.y2, doom->editor.brezen.color);
	}
}

void	ft_line(t_doom *doom)
{
	BDX = abs(doom->editor.brezen.x2 - doom->editor.brezen.x1);
	BDY = abs(doom->editor.brezen.y2 - doom->editor.brezen.y1);
	BSTARTX = doom->editor.brezen.x2 >= doom->editor.brezen.x1 ? 1 : -1;
	BSTARTY = doom->editor.brezen.y2 >= doom->editor.brezen.y1 ? 1 : -1;
	doom->editor.brezen.d = BDY <= BDX ? (BDY << 1)
	- BDX : (BDX << 1) - BDY;
	doom->editor.brezen.d1 = BDY <= BDX ? BDY << 1
	: BDX << 1;
	doom->editor.brezen.d2 = BDY <= BDX ?
	(BDY - doom->editor.brezen.dx) << 1 :
	(BDX - BDY) << 1;
	ft_draw_pixel(doom, doom->editor.brezen.x1,
	doom->editor.brezen.y1, doom->editor.brezen.color);
	if (BDY <= doom->editor.brezen.dx)
		ft_print_line_low(doom);
	else
		ft_print_line_high(doom);
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
