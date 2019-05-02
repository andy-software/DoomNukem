/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:54 by apavlov           #+#    #+#             */
/*   Updated: 2018/10/26 16:55:44 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*cur;

	cur = b;
	i = 0;
	while (i < len)
		cur[i++] = (unsigned char)c;
	return (b);
}
