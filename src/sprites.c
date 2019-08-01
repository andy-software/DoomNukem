/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:53:05 by apavlov           #+#    #+#             */
/*   Updated: 2019/06/15 16:53:05 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

SDL_Surface		**split_surf(int w, int h, char *path, t_doom *d)
{
	int			i;
	int			j;
	int			count;
	SDL_Rect	rect;
	SDL_Surface	**splited;
	SDL_Surface *sheet;

	i = -1;
	count = 0;
	sheet = load_tex(path, &d->sdl);
	SDL_SetColorKey(sheet, SDL_TRUE, SDL_MapRGB(sheet->format, 255, 255, 255));
	splited = ft_memalloc(sizeof(SDL_Surface*) * (w * h));
	rect = (SDL_Rect){0, 0, sheet->w / w - 1, sheet->h / h - 1};
	while (++i < h)
	{
		j = -1;
		while (++j < w)
		{
			rect.x = sheet->w / w * j;
			rect.y = sheet->h / h * i;
			splited[count] = SDL_CreateRGBSurfaceWithFormat(0, rect.w,
				rect.h, 32, d->sdl.surface->format->format);
			SDL_BlitSurface(sheet, &rect, splited[count], NULL );
			count++;
		}
	}
	SDL_FreeSurface(sheet);
	return (splited);
}

int		translate_and_rotate_sprites(t_sprite	*arr_spr, int len, t_player	p)
{
	int		i;

	i = -1;
	while (++i < len)
	{
		arr_spr[i].coord.x -= p.coord.x;
		arr_spr[i].coord.y -= p.coord.y;
		rotate_vector_xy(&arr_spr[i].coord, p.anglesin, p.anglecos);
	}
	return (1);
}


