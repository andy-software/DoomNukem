/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:50:54 by mmasyush          #+#    #+#             */
/*   Updated: 2019/07/24 11:50:55 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void    show_pause(t_doom *d)
{  
    int opt;
    int x;
    int y;
    int i;
    opt = 2; 
    char    *title[2] = {"Exit", "Restart"}; // Y the freak it cant use opt as counter?!
    SDL_Surface *menus[opt];
    int select[2] = {0, 0}; 
    SDL_Color color[2] = {{255, 255, 255, 0}, {0, 0, 0, 0}};

    menus[0] = TTF_RenderText_Solid(d->texture.fonts[MENU_FONT].text_font, title[0], color[0]);
    menus[1] = TTF_RenderText_Solid(d->texture.fonts[MENU_FONT].text_font, title[1], color[0]);
    SDL_Rect pos[opt];

    pos[0].x = WIN_WIDTH / 2 - menus[0]->w / 2;
    pos[0].y = WIN_HEIGHT / 2 - menus[0]->h;
    pos[1].x = WIN_WIDTH / 2 - menus[1]->w / 2;
    pos[1].y = WIN_HEIGHT / 2 + menus[1]->h;
    pos[0].w = WIN_WIDTH / 6;
    pos[0].h = WIN_HEIGHT / 6;
    pos[1].w = WIN_WIDTH / 6;
    pos[1].h = WIN_HEIGHT / 6;
    

    SDL_FillRect(d->sdl.surface, 0, 0xff0000);

    x = d->ev.motion.x;
    y = d->ev.motion.y;
    i = -1;
    if (d->ev.type == SDL_MOUSEMOTION)
    {
        while (++i < opt)
        {
            printf("%d\n", pos[i].h);
            if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
            {
                if (select[i] == 0)
                {
                    select[i] = 1;
                    SDL_FreeSurface(menus[i]);
                    menus[i] = TTF_RenderText_Solid(d->texture.fonts[MENU_FONT].text_font, title[i], color[1]);
                }
            }
            else
            {
                select[i] = 0;
                SDL_FreeSurface(menus[i]);
                menus[i] = TTF_RenderText_Solid(d->texture.fonts[MENU_FONT].text_font, title[i], color[0]);
            } 
        }
    }
    else if (d->ev.type == SDL_MOUSEBUTTONDOWN)
    {
        while (++i < opt)
        {
            if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
            {
                while (++i < opt)
                    SDL_FreeSurface(menus[i]);
            }
            break;
        }
    }
    else if (d->ev.type == SDL_KEYDOWN && d->ev.key.keysym.sym == PAUSE)
    {
        while (++i < opt)
            SDL_FreeSurface(menus[i]);
    }
    i = -1;
    while (++i < opt)
    SDL_BlitSurface(menus[i], NULL, d->sdl.surface, &pos[i]);
}
