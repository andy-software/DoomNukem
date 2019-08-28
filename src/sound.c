/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:47:33 by mmasyush          #+#    #+#             */
/*   Updated: 2019/08/23 18:33:11 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

Mix_Music	*load_music(char *path)
{
	Mix_Music *load;

	load = Mix_LoadMUS(path);
	if (load == NULL)
		error_message("\033[22;31mERROR: failed to load musi1c");
	return (load);
}

Mix_Chunk	*load_sound(char *path)
{
	Mix_Chunk *load;

	load = Mix_LoadWAV(path);
	if (load == NULL)
		error_message("\033[22;31mERROR: failed to load sound");
	return (load);
}
