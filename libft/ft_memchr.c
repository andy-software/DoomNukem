/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:22:14 by apavlov           #+#    #+#             */
/*   Updated: 2018/10/29 14:26:18 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s1, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)s1;
	while (i < n)
	{
		if (tmp[i] == (unsigned char)c)
			return ((void *)(s1 + i));
		i++;
	}
	return (0);
}
