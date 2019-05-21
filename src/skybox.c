/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:28:05 by mmasyush          #+#    #+#             */
/*   Updated: 2019/05/16 13:28:06 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

//x = const * a
//y = const * tan(b)
void	draw_skybox(t_render *r, t_doom d)
{
	int win_x;
	int text_x;
	int win_y;
	int text_y;
	double pos_angle;
	double pos_max;

	win_x = 0;
	pos_angle = d.player.anglesin / 0.005556;
	pos_max = SKYBOX_WIDTH / 2 / 360;
	if (d.player.anglecos >= 0)
		text_x = (int)(pos_angle * pos_max);
	else
		text_x = (int)(SKYBOX_WIDTH / 2 - (pos_angle * pos_max));
	if (text_x < 0)
		text_x = 4096 + text_x;
	while (win_x < WIN_WIDTH)
	{
		text_x++;
		if (text_x < 0)
			text_x = SKYBOX_WIDTH;
		if (text_x > SKYBOX_WIDTH)
			text_x = 0;
		win_y = 0;
		text_y = 900 + (d.player.angle_z * 160);
		while (win_y < WIN_HEIGHT && text_y < SKYBOX_HEIGHT - 1 && text_x <= SKYBOX_WIDTH)
		{
			r->pix[win_y++ * WIN_WIDTH + win_x] = pix_from_text(d.texture.sky_box, text_x, text_y);
			text_y++;
		}
		win_x++;
	}
}