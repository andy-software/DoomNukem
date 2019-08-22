/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_bubble_int_array.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:45:54 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/07 14:07:49 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap(int *a, int *b)
{
	int buff;

	buff = *a;
	*a = *b;
	*b = buff;
}

void		ft_sort_bubble_int_array(int **array, size_t size,\
								int (*cmp)(int, int))
{
	size_t i;
	size_t k;

	if (!*array || !cmp)
		return ;
	i = -1;
	while (++i < size)
	{
		k = -1;
		while (++k < size)
			if (cmp((*array)[i], (*array)[k]) > 0)
				swap((*array) + i, (*array) + k);
	}
}
