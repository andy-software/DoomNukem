/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureload_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 18:42:37 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/24 17:39:36 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	load_walls_sky(t_texture *t, Uint32 format)
{
	t->wall_tex[0] = load_tex("./materials/textures/walls/1.png", format);
	t->wall_tex[1] = load_tex("./materials/textures/walls/2.png", format);
	t->wall_tex[2] = load_tex("./materials/textures/walls/3.png", format);
	t->wall_tex[3] = load_tex("./materials/textures/walls/4.png", format);
	t->wall_tex[4] = load_tex("./materials/textures/walls/5.png", format);
	t->wall_tex[5] = load_tex("./materials/textures/walls/6.png", format);
	t->wall_tex[6] = load_tex("./materials/textures/walls/7.png", format);
	t->wall_tex[7] = load_tex("./materials/textures/walls/8.png", format);
	t->wall_tex[8] = load_tex("./materials/textures/walls/9.png", format);
	t->wall_tex[9] = load_tex("./materials/textures/walls/10.png", format);
	t->wall_tex[10] = load_tex("./materials/textures/walls/11.png", format);
	t->wall_tex[11] = load_tex("./materials/textures/walls/12.png", format);
	t->wall_tex[12] = load_tex("./materials/textures/walls/13.png", format);
	t->wall_tex[13] = load_tex("./materials/textures/walls/14.png", format);
	t->wall_tex[14] = load_tex("./materials/textures/walls/15.png", format);
	t->wall_tex[15] = load_tex("./materials/textures/walls/16.png", format);
	t->wall_tex[16] = load_tex("./materials/textures/walls/17.png", format);
	t->wall_tex[17] = load_tex("./materials/textures/walls/18.png", format);
	t->wall_tex[18] = load_tex("./materials/textures/walls/19.png", format);
	t->sky_box[0] = load_tex("./materials/textures/sky/sky1.jpg", format);
	t->sky_box[1] = load_tex("./materials/textures/sky/sky1.jpg", format);
}

int		load_all(t_texture *t, Uint32 format, t_doom *d)
{
	d->texture.format = format;
	if (!(t->fonts[FPS_F].text_font = TTF_OpenFont("fonts/doom.ttf", 30)))
		return (error_message("failed to malloc textures"));
	if (!(t->fonts[HP_F].text_font = TTF_OpenFont("fonts/doom.ttf", 40)))
		return (error_message("failed to malloc textures"));
	if (!(t->fonts[AMMO_F].text_font = TTF_OpenFont("fonts/doom.ttf", 50)))
		return (error_message("failed to malloc textures"));
	if (!(t->fonts[MENU_F].text_font = TTF_OpenFont("fonts/doom.ttf", 75)))
		return (error_message("failed to malloc textures"));
	load_walls_sky(t, format);
	t->fonts[FPS_F].text_color = (SDL_Color){65, 166, 205, 0};
	t->fonts[FPS_F].text_rect = (SDL_Rect){10, 15, 50, 10};
	t->fonts[HP_F].text_color = (SDL_Color){0, 255, 0, 0};
	load_sounds(&d->sound);
	load_ui(t, format, d);
	load_sprites(d);
	return (1);
}

void	load_other_sprites2(t_doom *d)
{
	d->texture.sprt[11].c_sprt = 1;
	d->texture.sprt[11].sprites = \
		split_surf(1, 1, "./materials/textures/sprites/tree.png", d);
	d->texture.sprt[12].c_sprt = 1;
	d->texture.sprt[12].sprites = \
		split_surf(1, 1, "./materials/textures/sprites/radio.png", d);
	d->texture.sprt[13].c_sprt = 1;
	d->texture.sprt[13].sprites = \
		split_surf(1, 1, "./materials/textures/sprites/button.png", d);
}

void	load_other_sprites(t_doom *d)
{
	d->texture.sprt[6].c_sprt = 30;
	d->texture.sprt[6].w = 6;
	d->texture.sprt[6].h = 5;
	d->texture.sprt[6].sprites = \
		split_surf(6, 5, "./materials/textures/sprites/enemy2.png", d);
	d->texture.sprt[7].c_sprt = 1;
	d->texture.sprt[7].sprites = \
		split_surf(1, 1, "./materials/textures/sprites/fly.png", d);
	d->texture.sprt[8].c_sprt = 30;
	d->texture.sprt[8].w = 6;
	d->texture.sprt[8].h = 5;
	d->texture.sprt[8].sprites = \
		split_surf(6, 5, "./materials/textures/sprites/boss.png", d);
	d->texture.sprt[9].c_sprt = 1;
	d->texture.sprt[9].sprites = \
		split_surf(1, 1, "./materials/textures/sprites/npc.png", d);
	d->texture.sprt[10].c_sprt = 1;
	d->texture.sprt[10].sprites = \
		split_surf(1, 1, "./materials/textures/sprites/painting1.jpg", d);
	load_other_sprites2(d);
}

void	load_sprites(t_doom *d)
{
	d->texture.sprt = (t_sprite_sheet*)malloc(sizeof(t_sprite_sheet) * 14);
	d->texture.sprt[0].c_sprt = 1;
	d->texture.sprt[0].sprites = \
		split_surf(1, 1, "./materials/textures/sprites/dude.png", d);
	d->texture.sprt[1].c_sprt = 1;
	d->texture.sprt[1].sprites = \
		split_surf(1, 1, "./materials/textures/sprites/med.png", d);
	d->texture.sprt[2].c_sprt = 1;
	d->texture.sprt[2].sprites = \
		split_surf(1, 1, "./materials/textures/sprites/ammo.png", d);
	d->texture.sprt[3].c_sprt = 3;
	d->texture.sprt[3].w = 3;
	d->texture.sprt[3].h = 1;
	d->texture.sprt[3].sprites = \
		split_surf(3, 1, "./materials/textures/sprites/keys.png", d);
	d->texture.sprt[4].c_sprt = 1;
	d->texture.sprt[4].sprites = \
		split_surf(1, 1, "./materials/textures/sprites/dude1.png", d);
	d->texture.sprt[5].c_sprt = 50;
	d->texture.sprt[5].w = 10;
	d->texture.sprt[5].h = 5;
	d->texture.sprt[5].sprites = \
		split_surf(10, 5, "./materials/textures/sprites/enemy1.png", d);
	load_other_sprites(d);
}
