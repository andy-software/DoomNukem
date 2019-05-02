/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:09:58 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/02 19:42:54 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src,\
					int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;
	unsigned char	*tmp_src;
	int				boo;

	i = 0;
	tmp = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	boo = 0;
	while (i < n && !boo)
	{
		tmp[i] = tmp_src[i];
		if (tmp_src[i] == (unsigned char)c)
			boo = 1;
		i++;
	}
	if (!boo)
		return (0);
	return (dst + i);
}
