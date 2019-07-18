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
	const	int	text_y_start = 900 + d.player.angle_z * 160;
	static	const int	W_H2 = WIN_HEIGHT * WIN_WIDTH;

	d.sky.win_x = 0;
	d.sky.pos_angle = ((d.player.anglesin) / (2 / 360.0));
	d.sky.pos_max = 5;
	d.sky.pos_max = SKY_W / 2 / 360;
	if (d.player.anglecos >= 0)
		d.sky.text_x = (int)(d.sky.pos_angle * d.sky.pos_max);
	else
		d.sky.text_x = (int)(SKY_W / 2 - d.sky.pos_angle * d.sky.pos_max);
	if (d.sky.text_x < 0)
		d.sky.text_x = 4096 + d.sky.text_x;
	while (d.sky.win_x < WIN_WIDTH && d.sky.text_x <= SKY_W)
	{
		d.sky.text_x++;
		if (d.sky.text_x < 0)
			d.sky.text_x = SKY_W;
		if (d.sky.text_x > SKY_W)
			d.sky.text_x = 0;
		d.sky.win_y = 0;
		d.sky.text_y = text_y_start;
		while (d.sky.win_y < W_H2 && d.sky.text_y < SKY_H - 1)
		{
			r->pix[d.sky.win_y + d.sky.win_x] =
				pix_from_text(d.texture.sky_box[0], d.sky.text_x, d.sky.text_y);
			d.sky.text_y++;
			d.sky.win_y += WIN_WIDTH;
		}
		d.sky.win_x++;
	}
}
