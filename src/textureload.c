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
	if (!(texture->wall_tex = ft_memalloc(sizeof(SDL_Surface) * 3)))
		stop("\033[22;31mERROR: failed to malloc textures");
	texture->wall_tex[0] = load_tex("./textures/walls/WALL0.png", sdl);
	texture->wall_tex[1] = load_tex("./textures/walls/WALL-1.png", sdl);
	texture->wall_tex[2] = load_tex("./textures/walls/WALL0.png", sdl);
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