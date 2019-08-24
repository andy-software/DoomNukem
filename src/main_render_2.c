/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_render_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 19:45:34 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/23 19:45:35 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	draw_dot(int x, int y, Uint32 *surr_pixel, int color)
{
	Uint32	*pixels = (Uint32*)surr_pixel;

	if (y >= 0 && y < WIN_HEIGHT - 1 && x >= 0 && x < WIN_WIDTH - 1)
		pixels[y * WIN_WIDTH + x] = color;
}

void	prepare_to_render_next_sector(t_render *r)
{
	int	max1;
	int	max2;
	int	min1;
	int	min2;

	max1 = MAX((r->begin_x - r->x1) * r->kza + r->z1a, \
							(r->begin_x - r->x1) * r->nkza + r->nz1a);
	max2 = MAX((r->end_x - r->x1) * r->kza + r->z1a, \
							(r->end_x - r->x1) * r->nkza + r->nz1a);
	min1 = MIN((r->begin_x - r->x1) * r->kzb + r->z1b, \
							(r->begin_x - r->x1) * r->nkzb + r->nz1b);
	min2 = MIN((r->end_x - r->x1) * r->kzb + r->z1b, \
							(r->end_x - r->x1) * r->nkzb + r->nz1b);
	*r->head = (t_rend_sector) {r->neighbor, r->tail - 1, r->begin_x, r->end_x, \
		max1, max2, min1, min2};

	// for (int x = r->begin_x; x < r->end_x; x++)
	// {
	// 	float	perc = (x - r->begin_x )/ (r->end_x - r->begin_x);
	// 	draw_dot(x, line_point(min1, min2, perc), r->pix, 0x00ff00);
	// 	draw_dot(x, line_point(max1, max2, perc), r->pix, 0x0000ff);
	// }
	if (++r->head == (r->queue + MAX_SECTORS_RENDERED))
		r->head = r->queue;
}

void	prepare_to_rendering(t_render *r, t_doom d)
{
	int i;

	r->now.num = d.player.sector;
	r->sect = d.map.sectors + r->now.num;
	r->now.sx1 = 0;
	r->now.sx2 = WIN_WIDTH - 1;
	r->pcos = d.player.anglecos;
	r->psin = d.player.anglesin;
	r->pix = (Uint32*)d.sdl.surface->pixels;
	r->p_x = d.player.coord.x;
	r->p_y = d.player.coord.y;
	r->p_z = d.player.coord.z;
	r->angle_z = d.player.angle_z;
	i = -1;
	while (++i < MAX_SECTORS_RENDERED)
		r->queue[i] = (t_rend_sector){-1, 0, 0, WIN_WIDTH - 1, \
								0, 0, WIN_HEIGHT - 1, WIN_HEIGHT - 1};
	r->head = r->queue;
	r->tail = r->queue;
	ft_memset(r->rendered_sectors, 0, sizeof(int) * d.map.num_sect);
	intset(r->ztop, 0, WIN_WIDTH);
	intset(r->zbottom, WIN_HEIGHT - 1, WIN_WIDTH);
	ft_bzero(r->pix, WIN_HEIGHT * WIN_WIDTH * sizeof(Uint32));
}

void	upper_textline(int y1, int y2, t_render *r, t_thread *t)
{
	SDL_Surface	*surr;

	if (y2 == y1)
		return ;
	surr = r->texture->wall_tex[r->line.top];
	t->win_y = CLAMP(y1, r->ztop[t->win_x], r->zbottom[t->win_x]);
	t->wall_end = CLAMP(y2, r->ztop[t->win_x], r->zbottom[t->win_x]);
	t->d_betta = 1.0 / (t->nza - t->za);
	t->betta = (t->win_y - t->za) * t->d_betta;
	t->float_y_text = (1 - t->betta) * t->u0_t + t->betta * t->u1_t;
	t->d_y_text = -t->d_betta * t->u0_t + t->d_betta * t->u1_t;
	while (t->win_y < t->wall_end)
	{
		t->color = pix_from_text(surr, (unsigned int)t->x_text_upper %\
					surr->w, (unsigned int)t->float_y_text % surr->h);
		cool_simple_function((t_int_vertex){t->win_x, t->win_y}, \
								t->r, t->color, t->y);
		t->win_y++;
		t->betta += t->d_betta;
		t->float_y_text += t->d_y_text;
	}
}

void	lower_textline(int y1, int y2, t_render *r, t_thread *t)
{
	SDL_Surface	*surr;

	if (y2 == y1)
		return ;
	surr = r->texture->wall_tex[r->line.bot];
	t->win_y = CLAMP(y1, r->ztop[t->win_x], r->zbottom[t->win_x]);
	t->wall_end = CLAMP(y2, r->ztop[t->win_x], r->zbottom[t->win_x]);
	t->d_betta = 1.0 / (t->zb - t->nzb);
	t->betta = (t->win_y - t->nzb) * t->d_betta;
	t->float_y_text = (1 - t->betta) * t->u0_b + t->betta * t->u1_b;
	t->d_y_text = -t->d_betta * t->u0_b + t->d_betta * t->u1_b;
	while (t->win_y < t->wall_end)
	{
		t->color = pix_from_text(surr, (unsigned int)t->x_text_lower %\
							surr->w, (unsigned int)t->float_y_text % surr->h);
		cool_simple_function((t_int_vertex){t->win_x, t->win_y}, \
					t->r, t->color, t->y);
		t->win_y++;
		t->betta += t->d_betta;
		t->float_y_text += t->d_y_text;
	}
}

void	textline_draw(int y1, int y2, t_render *r, t_thread *t)
{
	SDL_Surface	*surr;

	if (y2 == y1)
		return ;
	surr = r->texture->wall_tex[r->line.wall];
	t->win_y = CLAMP(y1, r->ztop[t->win_x], r->zbottom[t->win_x]);
	t->wall_end = CLAMP(y2, r->ztop[t->win_x], r->zbottom[t->win_x]);
	t->d_betta = 1.0 / (t->zb - t->za);
	t->betta = (t->win_y - t->za) * t->d_betta;
	t->float_y_text = ((1 - t->betta) * t->u0 + t->betta * t->u1);
	t->d_y_text = -t->d_betta * t->u0 + t->d_betta * t->u1;
	while (t->win_y <= t->wall_end)
	{
		t->color = pix_from_text(surr, (unsigned int)t->x_text % \
						surr->w, (unsigned int)t->float_y_text % surr->h);
		cool_simple_function((t_int_vertex){t->win_x, t->win_y}, \
				t->r, t->color, t->y);
		t->win_y++;
		t->betta += t->d_betta;
		t->float_y_text += t->d_y_text;
	}
}
