/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 14:10:00 by apavlov           #+#    #+#             */
/*   Updated: 2019/03/23 14:10:01 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			print_usage(void)
{
	ft_putstr("usage: ./doom-nukem {edit, new, play} {map_name}\n");
	ft_putstr("One day this will run with OpenCL\n");
	return (0);
}

int			error_message(char *message)
{
	ft_putstr(message);
	ft_putchar('\n');
	return (0);
}

void		draw_fps(t_doom *d, int fps)
{
	char	str[4];
	int			i;
	SDL_Surface	*message;

	i = -1;
	while (++i < 3)
	{
		str[2 - i] = fps % 10 + 48;
		fps /= 10;
	}
	str[3] = 0;
	message = TTF_RenderText_Solid(d->texture.fonts[0].text_font, str, d->texture.fonts[0].text_color);
	SDL_BlitSurface(message, NULL, d->sdl.surface, &d->texture.fonts[0].text_rect);
	SDL_FreeSurface(message);
}
