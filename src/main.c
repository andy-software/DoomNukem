/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 13:51:28 by apavlov           #+#    #+#             */
/*   Updated: 2019/03/23 14:07:41 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		editor_mod(t_doom *doom, char *file_name)
{
	ft_map_editor(&doom, file_name);
	return (0);
}

int		game_mod(t_doom *doom, char *file_name)
{
	if (read_file(doom, file_name) == 0)
		return (error_message("Error with file") + 1);
	if (init_sdl(&doom->sdl) == 0)
		return (error_message("Error with SDL init") + 1);
	if (load_all(&doom->texture, doom->sdl.surface->format->format, doom) == 0)
		return (error_message("Error with textures") + 1);
	if (game_loop(*doom) == 0)
		return (error_message("Something really sad is happened") + 1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_doom	doom;

	srand(time(NULL));
	if (argc == 3 || argc == 2)
	{
		if (ft_strcmp(argv[1], "play") == 0)
			return (game_mod(&doom, argv[2]));
		else if (ft_strcmp(argv[1], "edit") == 0)
			return (editor_mod(&doom, argv[2]));
		else
			print_usage();
	}
	else
		print_usage();
	return (0);
}
