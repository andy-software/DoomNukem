/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_ft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 20:56:30 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/12 16:04:13 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	ft_error(int nb)
{
	if (nb == 1)
		ft_putstr("Error\n");
	if (nb == 2)
		ft_putstr("\x1B[31mWrong file or to many sectors\x1B[0m\n");
	exit(0);
}

void	ft_put_text(char *str, int nb, char *str1)
{
	ft_putstr(str);
	ft_putnbr(nb);
	ft_putstr(str1);
}

void	ft_draw_pixel(t_doom *doom, int x, int y, int color)
{
	int index;

	if (x < (WIN_WIDTH - 400) ||
	doom->editor.interface.is_drawing_interface == 1)
	{
		index = doom->editor.sdl.surface->pitch * y +
		x * doom->editor.sdl.surface->format->BytesPerPixel;
		*(unsigned *)(doom->editor.sdl.surface->pixels + index) = color;
	}
}

void	ft_null_items(t_doom *doom, int i, int num)
{
	doom->editor.images[i].im_x[num] = 700 + (i * 100);
	doom->editor.images[i].im_y[num] = 20;
}

void	ft_check_key(t_doom *doom, SDL_Event *event)
{
	int key;

	key = event->key.keysym.sym;
	if (ESC)
		doom->game.quit = 1;
}
