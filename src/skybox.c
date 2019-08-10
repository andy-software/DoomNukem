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
#ifndef W_H2
# define W_H2 (WIN_HEIGHT * WIN_WIDTH)
#endif

int		prepare_to_sky(t_doom *d)
{
	int		i;
	int		start_tex_x;

	i = -1;
	start_tex_x = (d->player.angle / (2 * M_PI) * (SKY_W - 1));
	while (++i < MAX_THREADS_IN_SKY)
	{
		d->sky[i].start_text_y = 640 + d->player.angle_z * 120;
		d->sky[i].win_x = WIN_WIDTH / MAX_THREADS_IN_SKY * i;
		d->sky[i].end_x = WIN_WIDTH / MAX_THREADS_IN_SKY * (i + 1);
		d->sky[i].text_x = start_tex_x + d->sky[i].win_x;
		if (d->sky[i].text_x < 0)
			d->sky[i].text_x += SKY_W;
		else if (d->sky[i].text_x >= SKY_W)
			d->sky[i].text_x %= SKY_W;
		d->sky[i].doom = d;
	}
	return (1);
}

void	*sky_threads(void *data)
{
	t_skybox	sky;
	Uint32		*pix;
	SDL_Surface	*surr;

	sky = *(t_skybox*)data;
	pix = sky.doom->render.pix;
	surr = sky.doom->texture.sky_box[0];
	while (sky.win_x < sky.end_x)
	{
		sky.text_x++;
		if (sky.text_x < 0)
			sky.text_x = SKY_W - 1;
		if (sky.text_x >= SKY_W)
			sky.text_x = 0;
		sky.win_y = 0;
		sky.text_y = sky.start_text_y - 1;
		while (sky.win_y < W_H2 && ++sky.text_y < SKY_H - 1)
		{
			pix[sky.win_y + sky.win_x] = \
				pix_from_text(surr, sky.text_x, sky.text_y);
			if (sky.doom->map.inverse_colors)
				pix[sky.win_y + sky.win_x] = ~pix[sky.win_y + sky.win_x];
			sky.win_y += WIN_WIDTH;
		}
		sky.win_x++;
	}
	return (0);
}

void	draw_skybox(t_doom *d)
{
	int		t;

	prepare_to_sky(d);
	t = -1;
	while (++t < MAX_THREADS_IN_SKY)
		pthread_create(&d->threads[t].thrd, NULL, sky_threads, d->sky + t);
	t = -1;
	while (++t < MAX_THREADS_IN_SKY)
		pthread_join(d->threads[t].thrd, NULL);
}
