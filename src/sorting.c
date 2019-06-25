/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:53:26 by apavlov           #+#    #+#             */
/*   Updated: 2019/06/15 16:53:26 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	swap_two_sprites(t_sprite	*a, t_sprite	*b)
{
	t_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int			sprite_sort(t_sprite *arr_spr, int len) //intersection sort
{
	int		i;
	int		j;
	t_sprite	key;

	i = 0;
	while (++i < len)
	{
		key = arr_spr[i];
		j = i;
		while (j > 0 && key.coord.y > (arr_spr + j - 1)->coord.y)
		{
			swap_two_sprites(arr_spr + j, arr_spr + j - 1);
			j--;
		}
		*(arr_spr + j) = key;
	}
	return (1);
}
