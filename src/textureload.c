/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureload.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:14:16 by mmasyush          #+#    #+#             */
/*   Updated: 2019/05/02 18:14:16 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		load_all(t_texture *t, t_sdl *sdl, t_doom *d)
{
	if (!(t->wall_tex = ft_memalloc(sizeof(SDL_Surface*) * 6)))
		return (error_message("failed to malloc textures"));
	if (!(t->sky_box = ft_memalloc(sizeof(SDL_Surface*) * 2)))
		return (error_message("failed to malloc textures"));
	if (!(t->fonts = ft_memalloc(sizeof(t_font) * 3)))
		return (error_message("failed to malloc textures"));
	if (!(t->fonts[FPS_FONT].text_font = TTF_OpenFont("fonts/doom.ttf", 30)))
		return (error_message("failed to malloc textures"));
	if (!(t->fonts[HP_FONT].text_font = TTF_OpenFont("fonts/doom.ttf", 40)))
		return (error_message("failed to malloc textures"));
	if (!(t->fonts[AMMO_FONT].text_font = TTF_OpenFont("fonts/doom.ttf", 50)))
		return (error_message("failed to malloc textures"));
	t->wall_tex[0] = load_tex("./materials/textures/walls/WALL3.png", sdl);
	t->wall_tex[1] = load_tex("./materials/textures/walls/WALL.png", sdl);
	t->wall_tex[2] = load_tex("./materials/textures/walls/WALL-1.png", sdl);
	t->wall_tex[3] = load_tex("./materials/textures/walls/WALL1.png", sdl);
	t->wall_tex[4] = load_tex("./materials/textures/walls/colorstone.png", sdl);
	t->wall_tex[5] = load_tex("./materials/textures/walls/wood.png", sdl);
	t->sky_box[0] = load_tex("./materials/textures/sky/sky0.jpg", sdl);
	t->sky_box[1] = load_tex("./materials/textures/sky/sky1.png", sdl);
	t->fonts[FPS_FONT].text_color = (SDL_Color){65, 166, 205, 0};
	t->fonts[FPS_FONT].text_rect = (SDL_Rect){10, 15, 50, 10};
	t->fonts[HP_FONT].text_color = (SDL_Color){0, 255, 0, 0};
	load_sprites(t, sdl);
	load_sounds(&d->sound);
	load_ui(t, sdl, d);
	return(1);
}

int		load_ui(t_texture *t, t_sdl *sdl, t_doom *d)
{
	t->gun1_l = 21;
	t->gun2_l = 18;
	t->dude_l = 34;
	if (!(t->dude = ft_memalloc(sizeof(SDL_Surface*) * t->dude_l)))
		return (error_message("failed to malloc textures"));
	if (!(t->gun1 = ft_memalloc(sizeof(SDL_Surface*) * t->gun1_l)))
		return (error_message("failed to malloc textures"));
	if (!(t->gun2 = ft_memalloc(sizeof(SDL_Surface*) * t->gun2_l)))
		return (error_message("failed to malloc textures"));
	t->pause = load_tex("./materials/textures/ui/pause.png", sdl);
	t->gun1[0] = load_tex("./materials/textures/ui/gun1/1.png", sdl);
	t->gun1[1] = load_tex("./materials/textures/ui/gun1/2.png", sdl);
	t->gun1[2] = load_tex("./materials/textures/ui/gun1/2.png", sdl);
	t->gun1[3] = load_tex("./materials/textures/ui/gun1/3.png", sdl);
	t->gun1[4] = load_tex("./materials/textures/ui/gun1/4.png", sdl);
	t->gun1[5] = load_tex("./materials/textures/ui/gun1/5.png", sdl);
	t->gun1[6] = load_tex("./materials/textures/ui/gun1/6.png", sdl);
	t->gun1[7] = load_tex("./materials/textures/ui/gun1/7.png", sdl);
	t->gun1[8] = load_tex("./materials/textures/ui/gun1/8.png", sdl);
	t->gun1[9] = load_tex("./materials/textures/ui/gun1/9.png", sdl);
	t->gun1[10] = load_tex("./materials/textures/ui/gun1/10.png", sdl);
	t->gun1[11] = load_tex("./materials/textures/ui/gun1/11.png", sdl);
	t->gun1[12] = load_tex("./materials/textures/ui/gun1/12.png", sdl);
	t->gun1[13] = load_tex("./materials/textures/ui/gun1/13.png", sdl);
	t->gun1[14] = load_tex("./materials/textures/ui/gun1/14.png", sdl);
	t->gun1[15] = load_tex("./materials/textures/ui/gun1/15.png", sdl);
	t->gun1[16] = load_tex("./materials/textures/ui/gun1/16.png", sdl);
	t->gun1[17] = load_tex("./materials/textures/ui/gun1/17.png", sdl);
	t->gun1[18] = load_tex("./materials/textures/ui/gun1/18.png", sdl);
	t->gun1[19] = load_tex("./materials/textures/ui/gun1/19.png", sdl);
	t->gun1[20] = load_tex("./materials/textures/ui/gun1/20.png", sdl);
	//CHAINSAW!!!!!!!!
	t->gun2[0] = load_tex("./materials/textures/ui/gun2/1.png", sdl);
	t->gun2[1] = load_tex("./materials/textures/ui/gun2/2.png", sdl);
	t->gun2[2] = load_tex("./materials/textures/ui/gun2/3.png", sdl);
	t->gun2[3] = load_tex("./materials/textures/ui/gun2/4.png", sdl);
	t->gun2[4] = load_tex("./materials/textures/ui/gun2/5.png", sdl);
	t->gun2[5] = load_tex("./materials/textures/ui/gun2/6.png", sdl);
	t->gun2[6] = load_tex("./materials/textures/ui/gun2/7.png", sdl);
	t->gun2[7] = load_tex("./materials/textures/ui/gun2/8.png", sdl);
	t->gun2[8] = load_tex("./materials/textures/ui/gun2/9.png", sdl);
	t->gun2[9] = load_tex("./materials/textures/ui/gun2/10.png", sdl);

	t->gun2[10] = load_tex("./materials/textures/ui/gun2/1.1.png", sdl);
	t->gun2[11] = load_tex("./materials/textures/ui/gun2/1.2.png", sdl);
	t->gun2[12] = load_tex("./materials/textures/ui/gun2/1.3.png", sdl);
	t->gun2[13] = load_tex("./materials/textures/ui/gun2/1.4.png", sdl);

	t->gun2[14] = load_tex("./materials/textures/ui/gun2/2.1.png", sdl);
	t->gun2[15] = load_tex("./materials/textures/ui/gun2/2.2.png", sdl);
	t->gun2[16] = load_tex("./materials/textures/ui/gun2/2.3.png", sdl);
	t->gun2[17] = load_tex("./materials/textures/ui/gun2/2.4.png", sdl);
	//chainsaw_end....

	t->dude[0] = load_tex("./materials/textures/ui/win/1.png", sdl);
	t->dude[1] = load_tex("./materials/textures/ui/win/2.png", sdl);
	t->dude[2] = load_tex("./materials/textures/ui/win/3.png", sdl);
	t->dude[3] = load_tex("./materials/textures/ui/win/4.png", sdl);
	t->dude[4] = load_tex("./materials/textures/ui/win/5.png", sdl);
	t->dude[5] = load_tex("./materials/textures/ui/win/6.png", sdl);
	t->dude[6] = load_tex("./materials/textures/ui/win/7.png", sdl);
	t->dude[7] = load_tex("./materials/textures/ui/win/8.png", sdl);
	t->dude[8] = load_tex("./materials/textures/ui/win/9.png", sdl);
	t->dude[9] = load_tex("./materials/textures/ui/win/10.png", sdl);
	t->dude[10] = load_tex("./materials/textures/ui/win/11.png", sdl);
	t->dude[11] = load_tex("./materials/textures/ui/win/12.png", sdl);
	t->dude[12] = load_tex("./materials/textures/ui/win/13.png", sdl);
	t->dude[13] = load_tex("./materials/textures/ui/win/14.png", sdl);
	t->dude[14] = load_tex("./materials/textures/ui/win/15.png", sdl);
	t->dude[15] = load_tex("./materials/textures/ui/win/16.png", sdl);
	t->dude[16] = load_tex("./materials/textures/ui/win/17.png", sdl);
	t->dude[17] = load_tex("./materials/textures/ui/win/18.png", sdl);
	t->dude[18] = load_tex("./materials/textures/ui/win/19.png", sdl);
	t->dude[19] = load_tex("./materials/textures/ui/win/20.png", sdl);
	t->dude[20] = load_tex("./materials/textures/ui/win/21.png", sdl);
	t->dude[21] = load_tex("./materials/textures/ui/win/22.png", sdl);
	t->dude[22] = load_tex("./materials/textures/ui/win/23.png", sdl);
	t->dude[23] = load_tex("./materials/textures/ui/win/24.png", sdl);
	t->dude[24] = load_tex("./materials/textures/ui/win/25.png", sdl);
	t->dude[25] = load_tex("./materials/textures/ui/win/26.png", sdl);
	t->dude[26] = load_tex("./materials/textures/ui/win/27.png", sdl);
	t->dude[27] = load_tex("./materials/textures/ui/win/28.png", sdl);
	t->dude[28] = load_tex("./materials/textures/ui/win/29.png", sdl);
	t->dude[29] = load_tex("./materials/textures/ui/win/30.png", sdl);
	t->dude[30] = load_tex("./materials/textures/ui/win/31.png", sdl);
	t->dude[31] = load_tex("./materials/textures/ui/win/32.png", sdl);
	t->dude[32] = load_tex("./materials/textures/ui/win/33.png", sdl);
	t->dude[33] = load_tex("./materials/textures/ui/win/34.png", sdl);
	
	t->visor = load_tex("./materials/textures/ui/hud/visor.png", sdl);

	t->len = t->gun1_l;
	resize_surf(WIN_WIDTH / 3, WIN_HEIGHT / 3, t->gun1, d);
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
		surf[i] = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, d->sdl.surface->format->format);
		SDL_BlitScaled(temp , 0, surf[i], 0);
		SDL_FreeSurface(temp);
	}
}

void	load_sprites(t_texture *texture, t_sdl *sdl)
{
	SDL_Surface	*surr;
	t_sprite_list	*head; //it must read more then 1 sprite should right present it

	surr = load_tex("./materials/textures/sprites/images.png", sdl);
	
	SDL_SetColorKey(surr, SDL_TRUE, SDL_MapRGB(surr->format, 255, 255, 255));
	texture->c_sprt = 12;
	
	head = split_image_to_sprites(surr, 3, 4); //check for licks and segs
	SDL_FreeSurface(surr);
	
	surr = load_tex("./materials/textures/sprites/dude_sprite.png", sdl);
	head->next = split_image_to_sprites(surr, 1, 1);
	SDL_FreeSurface(surr);
	if (head == 0)
	{
		error_message("Texture load error\n");
		exit(1); // im too lazy to exit it right
	}
	texture->sprites = head;
}

SDL_Surface	*load_tex(char *path, t_sdl *sdl)
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
	texture = SDL_ConvertSurfaceFormat(temp, sdl->surface->format->format, 0);
	SDL_FreeSurface(temp);
	return (texture);
}

Uint32	pix_from_text(SDL_Surface *texture, int x, int y)
{
	Uint32 *ptr;

	ptr = (Uint32 *)texture->pixels;
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