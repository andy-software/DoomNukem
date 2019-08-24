/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureload2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 18:40:44 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/24 17:39:49 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	load_gun1(t_texture *t, Uint32 format)
{
	t->gun1[0] = load_tex("./materials/textures/ui/gun1/1.png", format);
	t->gun1[1] = load_tex("./materials/textures/ui/gun1/2.png", format);
	t->gun1[2] = load_tex("./materials/textures/ui/gun1/2.png", format);
	t->gun1[3] = load_tex("./materials/textures/ui/gun1/3.png", format);
	t->gun1[4] = load_tex("./materials/textures/ui/gun1/4.png", format);
	t->gun1[5] = load_tex("./materials/textures/ui/gun1/5.png", format);
	t->gun1[6] = load_tex("./materials/textures/ui/gun1/6.png", format);
	t->gun1[7] = load_tex("./materials/textures/ui/gun1/7.png", format);
	t->gun1[8] = load_tex("./materials/textures/ui/gun1/8.png", format);
	t->gun1[9] = load_tex("./materials/textures/ui/gun1/9.png", format);
	t->gun1[10] = load_tex("./materials/textures/ui/gun1/10.png", format);
	t->gun1[11] = load_tex("./materials/textures/ui/gun1/11.png", format);
	t->gun1[12] = load_tex("./materials/textures/ui/gun1/12.png", format);
	t->gun1[13] = load_tex("./materials/textures/ui/gun1/13.png", format);
	t->gun1[14] = load_tex("./materials/textures/ui/gun1/14.png", format);
	t->gun1[15] = load_tex("./materials/textures/ui/gun1/15.png", format);
	t->gun1[16] = load_tex("./materials/textures/ui/gun1/16.png", format);
	t->gun1[17] = load_tex("./materials/textures/ui/gun1/17.png", format);
}

void	load_gun2(t_texture *t, Uint32 format)
{
	t->gun2[0] = load_tex("./materials/textures/ui/gun2/1.png", format);
	t->gun2[1] = load_tex("./materials/textures/ui/gun2/2.png", format);
	t->gun2[2] = load_tex("./materials/textures/ui/gun2/3.png", format);
	t->gun2[3] = load_tex("./materials/textures/ui/gun2/4.png", format);
	t->gun2[4] = load_tex("./materials/textures/ui/gun2/5.png", format);
	t->gun2[5] = load_tex("./materials/textures/ui/gun2/6.png", format);
	t->gun2[6] = load_tex("./materials/textures/ui/gun2/7.png", format);
	t->gun2[7] = load_tex("./materials/textures/ui/gun2/8.png", format);
	t->gun2[8] = load_tex("./materials/textures/ui/gun2/9.png", format);
	t->gun2[9] = load_tex("./materials/textures/ui/gun2/10.png", format);
	t->gun2[10] = load_tex("./materials/textures/ui/gun2/1.1.png", format);
	t->gun2[11] = load_tex("./materials/textures/ui/gun2/1.2.png", format);
	t->gun2[12] = load_tex("./materials/textures/ui/gun2/1.3.png", format);
	t->gun2[13] = load_tex("./materials/textures/ui/gun2/1.4.png", format);
	t->gun2[14] = load_tex("./materials/textures/ui/gun2/2.1.png", format);
	t->gun2[15] = load_tex("./materials/textures/ui/gun2/2.2.png", format);
	t->gun2[16] = load_tex("./materials/textures/ui/gun2/2.3.png", format);
	t->gun2[17] = load_tex("./materials/textures/ui/gun2/2.4.png", format);
}

void	load_dude_win(t_texture *t, Uint32 format)
{
	t->dude[0] = load_tex("./materials/textures/ui/win/1.png", format);
	t->dude[1] = load_tex("./materials/textures/ui/win/2.png", format);
	t->dude[2] = load_tex("./materials/textures/ui/win/3.png", format);
	t->dude[3] = load_tex("./materials/textures/ui/win/4.png", format);
	t->dude[4] = load_tex("./materials/textures/ui/win/5.png", format);
	t->dude[5] = load_tex("./materials/textures/ui/win/6.png", format);
	t->dude[6] = load_tex("./materials/textures/ui/win/7.png", format);
	t->dude[7] = load_tex("./materials/textures/ui/win/8.png", format);
	t->dude[8] = load_tex("./materials/textures/ui/win/9.png", format);
	t->dude[9] = load_tex("./materials/textures/ui/win/10.png", format);
	t->dude[10] = load_tex("./materials/textures/ui/win/11.png", format);
	t->dude[11] = load_tex("./materials/textures/ui/win/12.png", format);
	t->dude[12] = load_tex("./materials/textures/ui/win/13.png", format);
	t->dude[13] = load_tex("./materials/textures/ui/win/14.png", format);
	t->dude[14] = load_tex("./materials/textures/ui/win/15.png", format);
	t->dude[15] = load_tex("./materials/textures/ui/win/16.png", format);
	t->dude[16] = load_tex("./materials/textures/ui/win/17.png", format);
	t->dude[17] = load_tex("./materials/textures/ui/win/18.png", format);
}

void	load_dude_win2(t_texture *t, Uint32 format)
{
	t->dude[18] = load_tex("./materials/textures/ui/win/19.png", format);
	t->dude[19] = load_tex("./materials/textures/ui/win/20.png", format);
	t->dude[20] = load_tex("./materials/textures/ui/win/21.png", format);
	t->dude[21] = load_tex("./materials/textures/ui/win/22.png", format);
	t->dude[22] = load_tex("./materials/textures/ui/win/23.png", format);
	t->dude[23] = load_tex("./materials/textures/ui/win/24.png", format);
	t->dude[24] = load_tex("./materials/textures/ui/win/25.png", format);
	t->dude[25] = load_tex("./materials/textures/ui/win/26.png", format);
	t->dude[26] = load_tex("./materials/textures/ui/win/27.png", format);
	t->dude[27] = load_tex("./materials/textures/ui/win/28.png", format);
	t->dude[28] = load_tex("./materials/textures/ui/win/29.png", format);
	t->dude[29] = load_tex("./materials/textures/ui/win/30.png", format);
	t->dude[30] = load_tex("./materials/textures/ui/win/31.png", format);
	t->dude[31] = load_tex("./materials/textures/ui/win/32.png", format);
	t->dude[32] = load_tex("./materials/textures/ui/win/33.png", format);
	t->dude[33] = load_tex("./materials/textures/ui/win/34.png", format);
}

int		load_ui(t_texture *t, Uint32 format, t_doom *d)
{
	t->gun1_l = 18;
	t->gun2_l = 18;
	t->dude_l = 34;
	t->pause = load_tex("./materials/textures/ui/hud/pause.jpg", format);
	t->start = load_tex("./materials/textures/ui/hud/start.jpg", format);
	t->story = load_tex("./materials/textures/ui/hud/story.png", format);
	t->lose = load_tex("./materials/textures/ui/hud/dead.jpg", format);
	load_gun1(t, format);
	load_gun2(t, format);
	load_dude_win(t, format);
	load_dude_win2(t, format);
	t->visor = load_tex("./materials/textures/ui/hud/visor.png", format);
	SDL_SetColorKey(t->visor, SDL_TRUE, \
			SDL_MapRGB(t->visor->format, 255, 255, 255));
	t->keys = load_tex("./materials/textures/ui/hud/keys_ui.png", format);
	t->len = t->gun1_l;
	resize_surf(WIN_WIDTH, WIN_HEIGHT / 1.1, t->gun1, d);
	t->len = t->gun2_l;
	resize_surf(WIN_WIDTH / 3, WIN_HEIGHT / 3, t->gun2, d);
	t->len = 1;
	resize_surf(WIN_WIDTH, WIN_HEIGHT, &t->visor, d);
	t->len = t->dude_l;
	resize_surf(WIN_WIDTH / 2, WIN_HEIGHT / 2, t->dude, d);
	return (1);
}
