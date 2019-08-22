/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:17:07 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/02 19:13:05 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*tmp;
	unsigned char	*tmp_src;

	i = -1;
	tmp = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	if (tmp > tmp_src)
	{
		while ((int)(--len) >= 0)
			tmp[len] = tmp_src[len];
	}
	else
		while (++i < len)
			tmp[i] = tmp_src[i];
	return (dst);
}
