/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:18:31 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/22 21:01:19 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static	void	pick_map_sprites(t_doom *doom, int i)
{
	if (MAP_SPRT[i].pick == 0)
	{
		IMG[2].exist++;
		IMG[2].im_x[IMG[2].exist - 1] = (MAP_SPRT[i].coord.x * SCL) - 50;
		IMG[2].im_y[IMG[2].exist - 1] = (MAP_SPRT[i].coord.y * SCL) - 50;
	}
	if (MAP_SPRT[i].pick == 1)
	{
		IMG[4].exist++;
		IMG[4].im_x[IMG[4].exist - 1] = (MAP_SPRT[i].coord.x * SCL) - 50;
		IMG[4].im_y[IMG[4].exist - 1] = (MAP_SPRT[i].coord.y * SCL) - 50;
	}
}

static	void	pick_buttons(t_doom *doom, int i)
{
	IMG[i].im_x = (double *)malloc(sizeof(double) * 100);
	IMG[i].im_y = (double *)malloc(sizeof(double) * 100);
	ft_null_items(doom, i, 0);
	ft_null_items(doom, i, 1);
	IMG[i].exist = 0;
}

void			ft_prepare_editor(t_doom *doom, int i)
{
	INIT4(DEDI.is_sector, 1, DEDI.ind_text, 5, \
		DEDI.press.ind_action, 5, DEDI.fl_or_ceil, 1);
	while (++i < NB_BUTTONS)
		pick_buttons(doom, i);
	if (doom->player.coord.x && doom->player.coord.y)
	{
		IMG[1].exist = 1;
		IMG[1].im_x[1] = (doom->player.coord.x * SCL) - 50;
		IMG[1].im_y[1] = (doom->player.coord.y * SCL) - 50;
		INIT3(IMG[2].exist, 0, IMG[4].exist, 0, i, -1);
		while (++i < (int)doom->map.num_sprites)
			pick_map_sprites(doom, i);
		ft_null_items(doom, 2, IMG[2].exist);
		ft_null_items(doom, 4, IMG[4].exist);
		IMG[3].exist = doom->map.num_paint;
		ft_null_items(doom, 3, doom->map.num_paint);
		i = -1;
		while (++i < (int)doom->map.num_paint)
		{
			IMG[3].im_x[i] = (doom->map.paint[i].v1.x * SCL) - 50;
			IMG[3].im_y[i] = (doom->map.paint[i].v1.y * SCL) - 50;
		}
	}
	INIT5(DEDI.fline.num_line1, -1, DEDI.fline.num_line2, -1, \
		DEDI.fline.sec1, -1, DEDI.fline.sec2, 1, DEDI.which_wall, 1);
}

void			ft_render_editor(t_doom *doom)
{
	ft_render_interface(doom);
	ft_render_previous(doom);
	ft_render_other(doom);
}
