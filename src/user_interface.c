/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:50:36 by apavlov           #+#    #+#             */
/*   Updated: 2019/04/27 16:50:37 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		prepare_to_draw_ui(t_doom *doom)
{
	t_ui	ui;

	ui.minimap_rect = (SDL_Rect*){WIN_WIDTH - MINIMAP_WIDTH, WIN_HEIGHT - MINIMAP_HEIGHT, MINIMAP_WIDTH, MINIMAP_HEIGHT};
	if (!(ui.minimap_surf = SDL_CreateRGBSurface(0, MINIMAP_WIDTH, MINIMAP_HEIGHT, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000)))
		return (error_message("Minimap surface coudn't create"));
	ft_bzero(ui.minimap_surf->pixels, ui.minimap_surf->pitch * MINIMAP_HEIGHT);
	return (1);
}

int		user_interface(t_doom *doom)
{
	draw_minimap(doom);
}