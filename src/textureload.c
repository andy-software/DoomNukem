/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureload.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:14:16 by mmasyush          #+#    #+#             */
/*   Updated: 2019/08/20 03:37:56 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

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
	t->fonts[FPS_F].text_color = (SDL_Color){65, 166, 205, 0};
	t->fonts[FPS_F].text_rect = (SDL_Rect){10, 15, 50, 10};
	t->fonts[HP_F].text_color = (SDL_Color){0, 255, 0, 0};
	load_sounds(&d->sound);
	
	load_ui(t, format, d);
	load_sprites(d);
	return(1);
}

int		load_ui(t_texture *t, Uint32 format, t_doom *d)
{
	t->gun1_l = 18;
	t->gun2_l = 18;
	t->dude_l = 34;
	t->pause = load_tex("./materials/textures/ui/hud/pause.jpg", format);
	t->start = load_tex("./materials/textures/ui/hud/start.jpg", format);
	t->story = load_tex("./materials/textures/ui/hud/story.png", format);
	t->lose = load_tex("./materials/textures/ui/hud/dead.jpg", format);
	t->gun1[0] = load_tex("./materials/textures/ui/gun1/1.png", format);
	t->gun1[1] = load_tex("./materials/textures/ui/gun1/2.png", format);
	t->gun1[2] = load_tex("./materials/textures/ui/gun1/2.png", format);
	t->gun1[3] = load_tex("./materials/textures/ui/gun1/3.png", format);
	t->gun1[4] = load_tex("./materials/textures/ui/gun1/4.png", format);
	t->gun1[5] = load_tex("./materials/textures/ui/gun1/5.png", format);
	t->gun1[6] = load_tex("./materials/textures/ui/gun1/6.png", format);
	t->gun1[7] = load_tex("./materials/textures/ui/gun1/7.png", format);
	t->gun1[8] = load_tex("./materials/textures/ui/gun1/8.png", format);
	t->gun1[9] = load_tex("./materials/textures/ui/gun1/9.png", format);
	t->gun1[10] = load_tex("./materials/textures/ui/gun1/10.png", format);
	t->gun1[11] = load_tex("./materials/textures/ui/gun1/11.png", format);
	t->gun1[12] = load_tex("./materials/textures/ui/gun1/12.png", format);
	t->gun1[13] = load_tex("./materials/textures/ui/gun1/13.png", format);
	t->gun1[14] = load_tex("./materials/textures/ui/gun1/14.png", format);
	t->gun1[15] = load_tex("./materials/textures/ui/gun1/15.png", format);
	t->gun1[16] = load_tex("./materials/textures/ui/gun1/16.png", format);
	t->gun1[17] = load_tex("./materials/textures/ui/gun1/17.png", format);
	//CHAINSAW!!!!!!!!
	t->gun2[0] = load_tex("./materials/textures/ui/gun2/1.png", format);
	t->gun2[1] = load_tex("./materials/textures/ui/gun2/2.png", format);
	t->gun2[2] = load_tex("./materials/textures/ui/gun2/3.png", format);
	t->gun2[3] = load_tex("./materials/textures/ui/gun2/4.png", format);
	t->gun2[4] = load_tex("./materials/textures/ui/gun2/5.png", format);
	t->gun2[5] = load_tex("./materials/textures/ui/gun2/6.png", format);
	t->gun2[6] = load_tex("./materials/textures/ui/gun2/7.png", format);
	t->gun2[7] = load_tex("./materials/textures/ui/gun2/8.png", format);
	t->gun2[8] = load_tex("./materials/textures/ui/gun2/9.png", format);
	t->gun2[9] = load_tex("./materials/textures/ui/gun2/10.png", format);

	t->gun2[10] = load_tex("./materials/textures/ui/gun2/1.1.png", format);
	t->gun2[11] = load_tex("./materials/textures/ui/gun2/1.2.png", format);
	t->gun2[12] = load_tex("./materials/textures/ui/gun2/1.3.png", format);
	t->gun2[13] = load_tex("./materials/textures/ui/gun2/1.4.png", format);

	t->gun2[14] = load_tex("./materials/textures/ui/gun2/2.1.png", format);
	t->gun2[15] = load_tex("./materials/textures/ui/gun2/2.2.png", format);
	t->gun2[16] = load_tex("./materials/textures/ui/gun2/2.3.png", format);
	t->gun2[17] = load_tex("./materials/textures/ui/gun2/2.4.png", format);
	//chainsaw_end....

	t->dude[0] = load_tex("./materials/textures/ui/win/1.png", format);
	t->dude[1] = load_tex("./materials/textures/ui/win/2.png", format);
	t->dude[2] = load_tex("./materials/textures/ui/win/3.png", format);
	t->dude[3] = load_tex("./materials/textures/ui/win/4.png", format);
	t->dude[4] = load_tex("./materials/textures/ui/win/5.png", format);
	t->dude[5] = load_tex("./materials/textures/ui/win/6.png", format);
	t->dude[6] = load_tex("./materials/textures/ui/win/7.png", format);
	t->dude[7] = load_tex("./materials/textures/ui/win/8.png", format);
	t->dude[8] = load_tex("./materials/textures/ui/win/9.png", format);
	t->dude[9] = load_tex("./materials/textures/ui/win/10.png", format);
	t->dude[10] = load_tex("./materials/textures/ui/win/11.png", format);
	t->dude[11] = load_tex("./materials/textures/ui/win/12.png", format);
	t->dude[12] = load_tex("./materials/textures/ui/win/13.png", format);
	t->dude[13] = load_tex("./materials/textures/ui/win/14.png", format);
	t->dude[14] = load_tex("./materials/textures/ui/win/15.png", format);
	t->dude[15] = load_tex("./materials/textures/ui/win/16.png", format);
	t->dude[16] = load_tex("./materials/textures/ui/win/17.png", format);
	t->dude[17] = load_tex("./materials/textures/ui/win/18.png", format);
	t->dude[18] = load_tex("./materials/textures/ui/win/19.png", format);
	t->dude[19] = load_tex("./materials/textures/ui/win/20.png", format);
	t->dude[20] = load_tex("./materials/textures/ui/win/21.png", format);
	t->dude[21] = load_tex("./materials/textures/ui/win/22.png", format);
	t->dude[22] = load_tex("./materials/textures/ui/win/23.png", format);
	t->dude[23] = load_tex("./materials/textures/ui/win/24.png", format);
	t->dude[24] = load_tex("./materials/textures/ui/win/25.png", format);
	t->dude[25] = load_tex("./materials/textures/ui/win/26.png", format);
	t->dude[26] = load_tex("./materials/textures/ui/win/27.png", format);
	t->dude[27] = load_tex("./materials/textures/ui/win/28.png", format);
	t->dude[28] = load_tex("./materials/textures/ui/win/29.png", format);
	t->dude[29] = load_tex("./materials/textures/ui/win/30.png", format);
	t->dude[30] = load_tex("./materials/textures/ui/win/31.png", format);
	t->dude[31] = load_tex("./materials/textures/ui/win/32.png", format);
	t->dude[32] = load_tex("./materials/textures/ui/win/33.png", format);
	t->dude[33] = load_tex("./materials/textures/ui/win/34.png", format);
	
	t->visor = load_tex("./materials/textures/ui/hud/visor.png", format);
	SDL_SetColorKey(t->visor, SDL_TRUE, SDL_MapRGB(t->visor->format, 255, 255, 255));
	t->keys = load_tex("./materials/textures/ui/hud/keys_ui.png", format);

	t->len = t->gun1_l;
	resize_surf(WIN_WIDTH, WIN_HEIGHT / 1.1, t->gun1, d);
	t->len = t->gun2_l;
	resize_surf(WIN_WIDTH / 3, WIN_HEIGHT / 3, t->gun2, d);
	t->len = 1;
	resize_surf(WIN_WIDTH, WIN_HEIGHT, &t->visor, d);
	t->len = t->dude_l;
	resize_surf(WIN_WIDTH / 2, WIN_HEIGHT / 2, t->dude, d);
	return (1);
}

void	resize_surf(int w, int h, SDL_Surface** surf, t_doom *d)
{
	SDL_Surface *temp;
	int i;

	i = -1;
	while(++i < d->texture.len)
	{
		temp = surf[i]; 
		surf[i] = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, d->texture.format);
		SDL_BlitScaled(temp , 0, surf[i], 0);
		SDL_FreeSurface(temp);
	}
}

void	load_sprites(t_doom *d)
{
	d->texture.sprt = (t_sprite_sheet*)malloc(sizeof(t_sprite_sheet) * 14);

	d->texture.sprt[0].c_sprt = 1;
	d->texture.sprt[0].sprites = split_surf(1, 1, "./materials/textures/sprites/dude.png", d);
	d->texture.sprt[1].c_sprt = 1;
	d->texture.sprt[1].sprites = split_surf(1, 1, "./materials/textures/sprites/med.png", d);
	d->texture.sprt[2].c_sprt = 1;
	d->texture.sprt[2].sprites = split_surf(1, 1, "./materials/textures/sprites/ammo.png", d);
	d->texture.sprt[3].c_sprt = 3;
	d->texture.sprt[3].w = 3;
	d->texture.sprt[3].h = 1;
	d->texture.sprt[3].sprites = split_surf(3, 1, "./materials/textures/sprites/keys.png", d);
	d->texture.sprt[4].c_sprt = 1;
	d->texture.sprt[4].sprites = split_surf(1, 1, "./materials/textures/sprites/dude1.png", d);
	d->texture.sprt[5].c_sprt = 50;
	d->texture.sprt[5].w = 10;
	d->texture.sprt[5].h = 5;
	d->texture.sprt[5].sprites = split_surf(10, 5, "./materials/textures/sprites/enemy1.png", d);
	d->texture.sprt[6].c_sprt = 30;
	d->texture.sprt[6].w = 6;
	d->texture.sprt[6].h = 5;
	d->texture.sprt[6].sprites = split_surf(6, 5, "./materials/textures/sprites/enemy2.png", d);
	d->texture.sprt[7].c_sprt = 1;
	d->texture.sprt[7].sprites = split_surf(1, 1, "./materials/textures/sprites/fly.png", d);
	d->texture.sprt[8].c_sprt = 30;
	d->texture.sprt[8].w = 6;
	d->texture.sprt[8].h = 5;
	d->texture.sprt[8].sprites = split_surf(6, 5, "./materials/textures/sprites/boss.png", d);
	d->texture.sprt[9].c_sprt = 1;
	d->texture.sprt[9].sprites = split_surf(1, 1, "./materials/textures/sprites/npc.png", d);
	d->texture.sprt[10].c_sprt = 1;
	d->texture.sprt[10].sprites = split_surf(1, 1, "./materials/textures/sprites/painting1.jpg", d);
	d->texture.sprt[11].c_sprt = 1;
	d->texture.sprt[11].sprites = split_surf(1, 1, "./materials/textures/sprites/tree.png", d);
	d->texture.sprt[12].c_sprt = 1;
	d->texture.sprt[12].sprites = split_surf(1, 1, "./materials/textures/sprites/radio.png", d);
	d->texture.sprt[13].c_sprt = 1;
	d->texture.sprt[13].sprites = split_surf(1, 1, "./materials/textures/sprites/button.png", d);
}

SDL_Surface	*load_tex(char *path, Uint32 format)
{
	SDL_Surface		*temp;
	SDL_Surface		*texture;

	temp = IMG_Load(path);
	if (temp == NULL)
	{
		SDL_FreeSurface(temp);
		error_message("Texture load error\n");
		exit(1); // im too lazy to exit it right
	}
	texture = SDL_ConvertSurfaceFormat(temp, format, 0);
	SDL_FreeSurface(temp);
	return (texture);
}

Uint32	pix_from_text(SDL_Surface *texture, int x, int y)
{
	Uint32 *ptr;

	ptr = (Uint32 *)texture->pixels; //surface->pixel
	return (ptr[(y * texture->w) + x]);
}

int		stop(char *str)
{
	ft_putstr(str);
	exit(1);
}

int		color_mix(Uint32 start, Uint32 end, float per)
{
	int		r;
	int		g;
	int		b;

	r = line_point((start >> 16) & 0xFF, (end >> 16) & 0xFF, per);
	g = line_point((start >> 8) & 0xFF, (end >> 8) & 0xFF, per);
	b = line_point(start & 0xFF, end & 0xFF, per);
	return ((r << 16) | (g << 8) | b);
}