/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureload.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:14:16 by mmasyush          #+#    #+#             */
/*   Updated: 2019/08/23 18:49:07 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		resize_surf(int w, int h, SDL_Surface **surf, t_doom *d)
{
	SDL_Surface		*temp;
	int				i;

	i = -1;
	while (++i < (int)d->texture.len)
	{
		temp = surf[i];
		surf[i] = SDL_CreateRGBSurfaceWithFormat(0,
			w, h, 32, d->texture.format);
		SDL_BlitScaled(temp, 0, surf[i], 0);
		SDL_FreeSurface(temp);
	}
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
		exit(1);
	}
	texture = SDL_ConvertSurfaceFormat(temp, format, 0);
	SDL_FreeSurface(temp);
	return (texture);
}

Uint32		pix_from_text(SDL_Surface *texture, int x, int y)
{
	Uint32			*ptr;

	ptr = (Uint32 *)texture->pixels;
	return (ptr[(y * texture->w) + x]);
}

int			stop(char *str)
{
	ft_putstr(str);
	exit(1);
}

int			color_mix(Uint32 start, Uint32 end, float per)
{
	int				r;
	int				g;
	int				b;

	r = line_point((start >> 16) & 0xFF, (end >> 16) & 0xFF, per);
	g = line_point((start >> 8) & 0xFF, (end >> 8) & 0xFF, per);
	b = line_point(start & 0xFF, end & 0xFF, per);
	return ((r << 16) | (g << 8) | b);
}
