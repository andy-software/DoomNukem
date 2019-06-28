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

void	wall_tex(t_texture *texture, t_sdl *sdl)
{
	if (!(texture->wall_tex = ft_memalloc(sizeof(SDL_Surface*) * 4)))
		stop("\033[22;31mERROR: failed to malloc textures");
	
	texture->wall_tex[0] = load_tex("./textures/walls/WALL3.png", sdl);
	texture->wall_tex[1] = load_tex("./textures/walls/WALL.png", sdl);
	texture->wall_tex[2] = load_tex("./textures/walls/WALL-1.png", sdl);
	texture->wall_tex[3] = load_tex("./textures/walls/WALL1.png", sdl);
	if (!(texture->sky_box = ft_memalloc(sizeof(SDL_Surface*) * 2)))
		stop("\033[22;31mERROR: failed to malloc textures");
	
	texture->sky_box[0] = load_tex("./textures/sky/sky0.jpg", sdl);
	texture->sky_box[1] = load_tex("./textures/sky/sky1.png", sdl);
	// if (!(texture->pause = ft_memalloc(sizeof(SDL_Surface))))
	// 	stop("\033[22;31mERROR: failed to malloc textures"); // leak
	texture->pause = load_tex("./textures/pause.png", sdl);
	
	load_sprites(texture, sdl, "./textures/sprites/images.png");
	if (!(texture->fonts = ft_memalloc(sizeof(t_font))))
		stop("\033[22;31mERROR: failed to malloc textures");
	if (!(texture->fonts[0].text_font = TTF_OpenFont("fonts/doom.ttf", 28)))
		stop("\033[22;31mERROR: failed to TTF_OpenFont");
	texture->fonts[0].text_color = (SDL_Color){255, 0, 0, 0};
	texture->fonts[0].text_rect = (SDL_Rect){20, 20, 50, 10};
}

void	load_sprites(t_texture *texture, t_sdl *sdl, char *path)
{
	SDL_Surface	*surr;
	t_sprite_list	*head; //it must read more then 1 sprite should right present it

	surr = load_tex(path, sdl);
	
	SDL_SetColorKey(surr, SDL_TRUE, SDL_MapRGB(surr->format, 255, 255, 255));
	texture->c_sprt = 3 * 4;
	
	head = split_image_to_sprites(surr, 3, 4); //check for licks and segs
	SDL_FreeSurface(surr);
	
	surr = load_tex("./textures/sprites/painting_flowers.jpg", sdl);
	head->next = split_image_to_sprites(surr, 1, 1);
	SDL_FreeSurface(surr);
	if (head == 0)
	{
		error_message("Texture load error\n");
		exit(1); // im too lazy to exit it right
		return ;
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
		stop("\033[22;31mERROR: failed to load texture");
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