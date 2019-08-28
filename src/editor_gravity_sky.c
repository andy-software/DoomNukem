/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gravity_sky.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 13:27:44 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/28 17:48:43 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	info_gravity(t_doom *doom)
{
	ft_putstr("  gravity: ");
	if (doom->map.gravity < 0)
	{
		ft_putstr("-");
		ft_putnbr(doom->map.gravity);
		ft_putstr(",");
		ft_putnbr(doom->map.gravity * -10);
		ft_putnbr((int)(doom->map.gravity * -100) % 10);
	}
	else
	{
		ft_putnbr(doom->map.gravity);
		ft_putstr(",");
		ft_putnbr(doom->map.gravity * 10);
		ft_putnbr((int)(doom->map.gravity * 100) % 10);
	}
	ft_putstr(" \n");
}

void	editor_sky_gravity(t_doom *doom, const Uint8 *state)
{
	if (doom->ev.key.keysym.sym == SDLK_g)
	{
		if (doom->map.gravity > -0.1 && \
			(state[SDL_SCANCODE_TAB]))
		{
			doom->map.gravity -= 0.01;
			info_gravity(doom);
		}
		else if (!(state[SDL_SCANCODE_TAB]) && \
			doom->map.gravity < 0.1)
		{
			doom->map.gravity += 0.01;
			info_gravity(doom);
		}
	}
	else if (doom->ev.key.keysym.sym == SDLK_y)
	{
		doom->map.sky_num++;
		if (doom->map.sky_num == 5)
			doom->map.sky_num = 0;
	}
}

void	find_z_pnt(t_doom *d, t_painting *p)
{
	d->map.paint[IMGS[3].exist - 1].v1.z = \
	(get_z(d->map.sectors[DEFL.sec1].floor_plane, p->v1.x, p->v1.y)) + 30;
	d->map.paint[IMGS[3].exist - 1].v2.z = \
	d->map.paint[IMGS[3].exist - 1].v1.z - 20;
}
