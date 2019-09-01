/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_write_sprites.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:13:42 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/31 19:38:35 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	write_sprites2(t_doom *doom, int i)
{
	if (doom->map.sprites[i].num_sheet == 0)
		create_gribok(doom, i);
	if (doom->map.sprites[i].num_sheet == 1 ||
		doom->map.sprites[i].num_sheet == 7 ||
		doom->map.sprites[i].num_sheet == 2)
		create_pickup(doom, i);
	else if (doom->map.sprites[i].num_sheet == 3)
		create_key1(doom, i);
	else if (doom->map.sprites[i].num_sheet == 4)
		create_win(doom, i);
	else if (doom->map.sprites[i].num_sheet == 9)
		create_npc(doom, i);
	else if (doom->map.sprites[i].num_sheet == 11 ||
		doom->map.sprites[i].num_sheet == 15)
		create_tree(doom, i);
}

void	write_sprites(t_doom *doom)
{
	int		i;

	i = -1;
	while (++i < (int)doom->map.num_sprites)
	{
		if (doom->map.sprites[i].num_sheet == 5)
			create_big_mob(doom, i);
		else if (doom->map.sprites[i].num_sheet == 6)
			create_small_mob(doom, i);
		else if (doom->map.sprites[i].num_sheet == 8)
			create_boss_mob(doom, i);
		else
			write_sprites2(doom, i);
	}
}
