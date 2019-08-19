/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 12:23:08 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/18 20:03:06 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_render_interface3(t_doom *doom, SDL_Rect bigger)
{
	int			x;
	int			y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = WIN_WIDTH - 401;
		while (++x < WIN_WIDTH)
			ft_draw_pixel(doom, x, y, 0x333333);
	}
	y = 700;
	while (++y < WIN_HEIGHT - 30)
	{
		x = WIN_WIDTH - 350;
		while (++x < WIN_WIDTH - 50)
			ft_draw_pixel(doom, x, y, 0);
	}
	if (doom->editor.press.ind_action == 5)
	{
		if (doom->map.fog == 1)
			SDL_BlitSurface(IMG[14].image, NULL, SDL_SURF, &bigger);
		else
			SDL_BlitSurface(IMG[15].image, NULL, SDL_SURF, &bigger);
	}
}

void	ft_render_interface2(t_doom *doom, SDL_Rect bigger)
{
	SDL_BlitSurface(SECTOR[3].image, NULL, SDL_SURF, &bigger);
	bigger.x = 1150;
	SDL_BlitSurface(SECTOR[4].image, NULL, SDL_SURF, &bigger);
	bigger.x = 850;
	SDL_BlitSurface(IMG[doom->editor.press.ind_action].image,
	NULL, SDL_SURF, &bigger);
	if (doom->editor.press.ind_action == 8)
	{
		bigger = (SDL_Rect){850, 230, 0, 0};
		if (doom->editor.fl_or_ceil == 1)
			SDL_BlitSurface(IMG[10].image, NULL, SDL_SURF, &bigger);
		if (doom->editor.fl_or_ceil == 2)
			SDL_BlitSurface(IMG[11].image, NULL, SDL_SURF, &bigger);
		info_ceil_floor(doom);
	}
	bigger = (SDL_Rect){10, 750, 250, 0};
	SDL_BlitSurface(IMG[9].image, NULL, SDL_SURF, &bigger);
	if (doom->editor.press.ind_action == 7)
	{
		bigger = (SDL_Rect){840, 630, 0, 0};
		if (doom->editor.is_portal == 0)
			SDL_BlitSurface(IMG[12].image, NULL, SDL_SURF, &bigger);
		else if (doom->editor.is_portal == 1)
			SDL_BlitSurface(IMG[13].image, NULL, SDL_SURF, &bigger);
	}
}

void	ft_render_prev_butt(t_doom *doom, SDL_Rect bigger, int exist)
{
	int			color;
	int			it[3];

	it[0] = 0;
	while (++it[0] < (NB_BUTTONS - 12))
	{
		exist = IMG[it[0]].exist;
		bigger.x = 700 + (it[0] * 100);
		if (doom->editor.ind_img != 0 && doom->editor.img_press == 1)
		{
			it[2] = 10;
			while (++it[2] < IMG[it[0]].image->w - 10)
			{
				it[1] = 10;
				while (++it[1] < IMG[it[0]].image->h - 10)
				{
					color = pix_from_text(IMG[it[0]].image, it[2], it[1]);
					if (color != -13421773)
						ft_draw_pixel(doom, IMG[it[0]].im_x[exist] + it[2],
						IMG[it[0]].im_y[exist] + it[1], color);
				}
			}
		}
		ft_render_other_butt(doom, exist, it, bigger);
	}
}

void	ft_render_other_butt(t_doom *doom, int exist, int *it, SDL_Rect bigger)
{
	int	color;

	while (exist != -1)
	{
		if (it[0] == 1 && exist == 0)
			break ;
		it[2] = 10;
		while (++it[2] < IMG[it[0]].image->w - 10)
		{
			it[1] = 10;
			while (++it[1] < IMG[it[0]].image->h - 10)
			{
				color = pix_from_text(IMG[it[0]].image, it[2], it[1]);
				if (color != -13421773)
					ft_draw_pixel(doom, IMG[it[0]].im_x[exist] + it[2],
					IMG[it[0]].im_y[exist] + it[1], color);
			}
		}
		exist--;
	}
	SDL_BlitSurface(IMG[it[0]].image, NULL, SDL_SURF, &bigger);
}

void	ft_render_interface(t_doom *doom)
{
	SDL_Rect	bigger;
	static int	i;

	i = 0;
	doom->editor.interface.is_drawing_interface = 1;
	ft_draw_axis(doom);
	bigger = (SDL_Rect){840, 630, 0, 0};
	ft_render_interface3(doom, bigger);
	bigger = (SDL_Rect){800, 130, 0, 0};
	ft_render_interface2(doom, bigger);
	bigger.y = 20;
	ft_render_prev_butt(doom, bigger, 0);
	bigger = (SDL_Rect){890, 710, 0, 0};
	if (doom->editor.is_sector != 0)
		SDL_BlitSurface(SECTOR[doom->editor.is_sector].image,
		NULL, SDL_SURF, &bigger);
	doom->editor.interface.is_drawing_interface = 0;
}
