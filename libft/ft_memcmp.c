/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:26:37 by apavlov           #+#    #+#             */
/*   Updated: 2018/10/29 14:32:06 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp;
	unsigned char	*tmp_src;

	i = 0;
	tmp = (unsigned char *)s1;
	tmp_src = (unsigned char *)s2;
	while (i < n)
	{
		if (tmp[i] != tmp_src[i])
			return (tmp[i] - tmp_src[i]);
		i++;
	}
	return (0);
}
