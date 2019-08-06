/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brezen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 16:06:26 by arudyi            #+#    #+#             */
/*   Updated: 2019/08/06 21:33:24 by myuliia          ###   ########.fr       */
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
