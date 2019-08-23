/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_render_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 19:58:27 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/23 19:58:29 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	cool_simple_function(t_int_vertex v, t_render *r, Uint32 color, float y)
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

void	draw_line_of_sprite(t_sprite_render *sr, SDL_Surface *sprtext, t_render *render)
{
	int		wall_end;
	float	y_point;
	float	dy_point;

	if (sr->zb == sr->za)
		return ;

	sr->win_y = clamp(sr->za, sr->clmp_top, sr->clmp_bot);
	wall_end = clamp(sr->zb, sr->clmp_top, sr->clmp_bot);
	dy_point = 1.0 / (sr->zb - sr->za); // derivation of y_point
	y_point = (float)(sr->win_y - (int)sr->za) * dy_point; //seg fault coz of int y
	while(sr->win_y < wall_end)
	{
		sr->y_text = y_point * (sprtext->h - 1);
		sr->color = pix_from_text(sprtext, sr->x_text, sr->y_text);
		if (sr->color != 0)
		{
			sr->color = get_color_value_int(sr->color, 0x0, sr->curr_sect->light_lvl);
			if (sr->map->fog && (int)sr->y > 20)
				sr->color = get_color_value_int(sr->color, sr->map->fog_color, (int)sr->y);
			render->pix[sr->win_y * WIN_WIDTH + (int)sr->win_x] = sr->color;
		}
		sr->win_y++;
		y_point += dy_point;
	}
}

void	render_ceil_line(int start, int end, t_render *r, t_thread *t)
{
	t_ceil_cal	cc;

	if (end > start)
		return ;
	cc = t->cc;
	cc.screen_y = clamp(start, end, WIN_HEIGHT);
	cc.x_multi = (WIN_WIDTH / 2 - t->win_x) / (HFOV);
	cc.denomi = - WIN_HEIGHT / 2 + (cc.rotated.a * (-cc.x_multi) - cc.rotated.b + r->angle_z) * VFOV;
	while (cc.screen_y > end)
	{
		cc.y = (cc.rotated.h) * VFOV / (cc.screen_y + cc.denomi);
		cc.map_x = cc.y * cc.x_multi;
		cc.dummy = cc.y * r->pcos + cc.map_x * r->psin;
		cc.doomy = cc.y * r->psin - cc.map_x * r->pcos;
		cc.map_x = cc.dummy + r->p_x;
		cc.map_y = cc.doomy + r->p_y;
		cc.x_text = (cc.map_x * cc.surr->w) * cc.sect->x_c_scale + cc.sect->x_c_shift;
		cc.y_text = (cc.map_y * cc.surr->h) * cc.sect->y_c_scale + cc.sect->y_c_shift;
		cc.color = pix_from_text(cc.surr, (unsigned)cc.x_text % cc.surr->w, (unsigned)cc.y_text % cc.surr->h);
		if (cc.color != 0)
			cc.color = get_color_value_int(cc.color, 0x0, t->r->sect->light_lvl);
		else
			cc.color = r->pix[cc.screen_y * WIN_WIDTH + t->win_x];
		if (r->map->fog)
			cc.color =  get_fog_color(cc.color, r->map->fog_color, cc.y);
		r->pix[cc.screen_y * WIN_WIDTH + t->win_x] = (r->map->inverse_colors) ? ~cc.color : cc.color;
		cc.screen_y--;
	}
}

void	render_floor_line(int start, int end, t_render *r, t_thread *t)
{
	t_floor_cal	fc;
	
	if (end < start)
		return ;
	fc = r->floor_cal;
	fc.screen_y = clamp(start, 0, end);
	fc.x_multi = (WIN_WIDTH / 2 - t->win_x) / (HFOV);
	fc.denomi = -WIN_HEIGHT / 2 + (fc.rotated.a * (-fc.x_multi) - fc.rotated.b + r->angle_z) * VFOV;
	while (fc.screen_y < end)
	{
		fc.y = (fc.rotated.h) * VFOV / (fc.screen_y + fc.denomi);
		fc.map_x = fc.y * fc.x_multi;
		fc.dummy = fc.y * r->pcos + fc.map_x * r->psin;
		fc.doomy = fc.y * r->psin - fc.map_x * r->pcos;
		fc.map_x = fc.dummy + r->p_x;
		fc.map_y = fc.doomy + r->p_y;
		fc.x_text = (fc.map_x * fc.surr->w) * fc.sect->x_f_scale + fc.sect->x_f_shift;
		fc.y_text = (fc.map_y * fc.surr->h) * fc.sect->y_f_scale + fc.sect->x_f_shift;
		fc.color = pix_from_text(fc.surr, (unsigned)fc.x_text % fc.surr->w, (unsigned)fc.y_text % fc.surr->h);
		if (fc.color != 0)
			fc.color = get_color_value_int(fc.color, 0x0, t->r->sect->light_lvl);
		else
			fc.color = r->pix[fc.screen_y * WIN_WIDTH + t->win_x];
		if (r->map->fog)
			fc.color = get_fog_color(fc.color, r->map->fog_color, fc.y);
		r->pix[fc.screen_y * WIN_WIDTH + t->win_x] = (r->map->inverse_colors) ? ~fc.color : fc.color;	
		fc.screen_y++;
	}
}
