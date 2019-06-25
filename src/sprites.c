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

t_sprite_list	*new_branch(SDL_Surface *surr, int w, int h) //sprite list should be useless cos map must already containt all the sprites and sprites textures
{
	t_sprite_list	*res;
	int		i;

	res = ft_memalloc(sizeof(t_sprite_list));
	res->w = surr->w / w;
	res->h = surr->h / h;
	res->sprites = ft_memalloc(sizeof(SDL_Surface*) * w * h);
	i = -1;
	while (++i < w * h)
	{
		res->sprites[i] = SDL_CreateRGBSurface(0, surr->w / w, surr->h / h, 0x20, 0, 0, 0, 0);
		if (res->sprites[i] == 0)
		{
			error_message("Couldnt create a surface. Sprite.c\n");
			exit(1); // im too lazy to avoid licks
			return (0);
		}
	}
	res->next = 0;
	fflush(stdout);
	return (res);
}

t_sprite_list	*split_image_to_sprites(SDL_Surface *surr, int w, int h) // h and w count of the sprites in the row or coloumn
{																		//sprite list should be useless cos map must already containt all the sprites and sprites textures
	int		i;
	int		j;
	SDL_Rect	in_rect;
	t_sprite_list	*res;

	i = -1;
	res = new_branch(surr, w, h);
	in_rect = (SDL_Rect){0, 0, res->w - 1, res->h - 1};
	while (++i < h)
	{
		j = -1;
		while (++j < w)
		{
			if ((SDL_BlitSurface(surr, &in_rect, res->sprites[i * w + j], NULL)) < 0)
			{
				error_message("Couldnt copy a surface. Sprite.c\n");
				exit(1); // im too lazy to avoid licks
				return (0);
			}
			in_rect.x = surr->w / w * j;
			in_rect.y = surr->h / h * i;
		}
	}
	printf("");
	return (res);
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

// int		render_sprites()
// {
	
// }
