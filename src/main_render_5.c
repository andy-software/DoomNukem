/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_render_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 13:25:33 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/24 13:25:33 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void			cool_simple_function(t_int_vertex v, \
									t_render *r, Uint32 color, float y)
{
	Uint32	*pixels;

	pixels = r->pix + v.y * WIN_WIDTH + v.x;
	if (color != 0)
		color = get_color_value_int(color, 0x0, r->sect->light_lvl);
	else
		color = (r->map->inverse_colors) ? ~*pixels : *pixels;
	if (r->map->fog)
		color = get_fog_color(color, r->map->fog_color, y);
	*pixels = (r->map->inverse_colors) ? ~color : color;
}

void			draw_line_of_sprite(t_sprite_render *sr, \
									SDL_Surface *sprtext, t_render *render)
{
	int		wall_end;
	float	y_point;
	float	dy_point;

	if (sr->zb == sr->za)
		return ;
	sr->win_y = CLAMP(sr->za, sr->clmp_top, sr->clmp_bot);
	wall_end = CLAMP(sr->zb, sr->clmp_top, sr->clmp_bot);
	dy_point = 1.0 / (sr->zb - sr->za);
	y_point = (float)(sr->win_y - (int)sr->za) * dy_point;
	while (sr->win_y < wall_end)
	{
		sr->y_text = y_point * (sprtext->h - 1);
		sr->color = pix_from_text(sprtext, sr->x_text, sr->y_text);
		if (sr->color != 0)
		{
			sr->color = get_color_value_int(sr->color, 0, sr->curr_sect->light_lvl);
			if (sr->map->fog && (int)sr->y > 20)
				sr->color = get_color_value_int(sr->color, sr->map->fog_color, (int)sr->y);
			render->pix[sr->win_y * WIN_WIDTH + (int)sr->win_x] = sr->color;
		}
		sr->win_y++;
		y_point += dy_point;
	}
}

int				draw_screen(t_doom *d)
{
	*d->render.head = (t_rend_sector){d->player.sector, 0, 0, \
					WIN_WIDTH - 1, 0, 0, WIN_HEIGHT - 1, WIN_HEIGHT - 1};
	d->sr.begin = d->render.head;
	if (++d->render.head == d->render.queue + MAX_SECTORS_RENDERED)
		d->render.head = d->render.queue;
	while (d->render.head != d->render.tail)
	{
		d->render.now = *d->render.tail;
		if (++d->render.tail == (d->render.queue + MAX_SECTORS_RENDERED))
			d->render.tail = d->render.queue;
		if (d->render.rendered_sectors[d->render.now.num] \
									& (MAX_SECTORS_RENDERED + 1))
			continue ;
		render_sector(&d->render, d);
	}
	render_painting(d);
	render_sprites(d);
	return (0);
}
