/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:11:11 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/02 18:38:20 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	dstlenght;
	size_t	srclenght;

	i = 0;
	dstlenght = ft_strlen(dst);
	srclenght = ft_strlen(src);
	if (dstsize <= dstlenght)
		return (srclenght + dstsize);
	while (dst[i] != '\0' && i < dstsize - 1)
		i++;
	while (*src && i < dstsize - 1)
	{
		dst[i] = *src;
		i++;
		src++;
	}
	dst[i] = '\0';
	return (dstlenght + srclenght);
}
