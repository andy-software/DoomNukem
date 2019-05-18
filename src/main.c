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
//Testing kfmgiu fnghcujdyujruhikruhodingtyi
int		editor_mod(char *file_name, int new_file)
{
	if (new_file)
		ft_putstr("File creating\n");
	ft_putstr("Editor\n");
	return (0);
}

int		game_mod(char *file_name)
{
	t_doom	doom;

	if (read_file(&doom, file_name) == 0)
		return (error_message("Error with file") + 1);
	if (init_sdl(&doom.sdl, &doom.options) == 0)
		return (error_message("Error with SDL init") + 1);
	wall_tex(&doom.texture, &doom.sdl);
	if (game_loop(doom) == 0)
		return (error_message("Something really sad is happened") + 1);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc == 3)
	{
		if (ft_strcmp(argv[1], "play") == 0)
			return (game_mod(argv[2]));
		else if (ft_strcmp(argv[1], "new") == 0)
			return (editor_mod(argv[2], 1));
		else if (ft_strcmp(argv[1], "edit") == 0)
			return (editor_mod(argv[2], 0));
		else
			print_usage();
	}
	else
		print_usage();
	return (0);
}
