/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:18:31 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/20 01:54:39 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		ft_prepare_to_write(t_doom *doom, int i)
{
	if (!doom->map.num_sect || !doom->player.coord.y)
		return (0);
	PR_TO_W(doom->player.coord.z, doom->player.angle, doom->player.angle_z);
	doom->player.anglecos = cosf(doom->player.angle);
	doom->player.anglesin = sinf(doom->player.angle);
	doom->map.num_sprites = IMG[2].exist + IMG[4].exist;
	while (++i < (int)doom->map.num_sprites)
	{
		MAP_SPRT[i].sector_no = is_in_sector(doom,
		(MAP_SPRT[i].coord.x * SCL), (MAP_SPRT[i].coord.y * SCL));
		if (MAP_SPRT[i].sector_no < 0)
			exit(0);
		PR_TO_WR(MAP_SPRT[i].live, MAP_SPRT[i].draw);
		MAP_SPRT[i].own_moves = i;
	}
	doom->editor.fl_or_ceil = 1;
	IMG[1].im_x[1] = (doom->player.coord.x * SCL) - 48;
	IMG[1].im_y[1] = (doom->player.coord.y * SCL) - 48;
	doom->player.sector = is_in_sector(doom,
	(doom->player.coord.x * SCL), (doom->player.coord.y * SCL));
	doom->player.coord.z = -doom->map.sectors[doom->player.sector].floor_plane.h + 10;
	if ((int)doom->player.sector < 0)
		exit(0);
	return (1);
}

void	ft_prepare_editor(t_doom *doom, int i)
{
	FT_PR_ED(doom->editor.is_sector, doom->editor.ind_text, doom->editor.press.ind_action, doom->editor.fl_or_ceil);
	while (++i < NB_BUTTONS)
	{
		IMG[i].im_x = (double *)malloc(sizeof(double) * 100);
		IMG[i].im_y = (double *)malloc(sizeof(double) * 100);
		ft_null_items(doom, i, 0);
		ft_null_items(doom, i, 1);
		IMG[i].exist = 0;
	}
	if (doom->player.coord.x && doom->player.coord.y)
	{
		IMG[1].exist = 1;
		IMG[1].im_x[1] = (doom->player.coord.x * SCL) - 50;
		IMG[1].im_y[1] = (doom->player.coord.y * SCL) - 50;
		IMG[2].exist = 0;
		IMG[4].exist = 0;
		i = -1;
		while (++i < (int)doom->map.num_sprites)
		{
			if (MAP_SPRT[i].mob == 1)
			{
				IMG[2].exist++;
				IMG[2].im_x[IMG[2].exist - 1] = (MAP_SPRT[i].coord.x * SCL) - 50;
				IMG[2].im_y[IMG[2].exist - 1] = (MAP_SPRT[i].coord.y * SCL) - 50;
			}
			if (MAP_SPRT[i].mob == 0)
			{
				IMG[4].exist++;
				IMG[4].im_x[IMG[4].exist - 1] = (MAP_SPRT[i].coord.x * SCL) - 50;
				IMG[4].im_y[IMG[4].exist - 1] = (MAP_SPRT[i].coord.y * SCL) - 50;
			}
		}
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
	FT_PR_ED2(doom->editor.fline.num_line1, doom->editor.fline.num_line2,
	doom->editor.fline.sec1, doom->editor.fline.sec2, doom->editor.which_wall);
}
