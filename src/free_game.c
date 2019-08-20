/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 22:19:24 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/13 22:19:25 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		free_file_data(t_map *map)
{
	int		i;

	i = -1;
	while (++i < map->num_sect)
	{
		free(map->sectors[i].vert);
		free(map->sectors[i].neighbors);
		free(map->sectors[i].lines);
	}
	free(map->sectors);
}

void		free_game_params(t_doom *d)
{
	free(d->render.rendered_sectors);
	free(d->sr.sprites);
	free(d->render.ztop);
	free(d->render.zbottom);
	free(d->render.queue);
	
}

void		free_menu(t_doom *d)
{
	int i;

	i = -1;
	while(i < d->menu.opt + 1)
	{
		SDL_FreeSurface(d->menu.m[i]);
		i++;
	}
}
