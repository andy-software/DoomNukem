/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:37:24 by apavlov           #+#    #+#             */
/*   Updated: 2018/10/29 14:46:40 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	if (len)
	{
		i = 0;
		if (ft_strlen(src) >= len)
		{
			while (i < len)
			{
				dst[i] = src[i];
				i++;
			}
		}
		else
		{
			while (i < ft_strlen(src))
			{
				dst[i] = src[i];
				i++;
			}
			while (i < len)
				dst[i++] = '\0';
		}
	}
	return (dst);
}
