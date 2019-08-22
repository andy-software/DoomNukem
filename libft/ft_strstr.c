/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:44:32 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/02 16:34:40 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (!needle[i])
		return ((char *)(haystack));
	while (haystack[i])
	{
		k = 0;
		while (needle[k])
		{
			if (haystack[i + k] != needle[k])
				break ;
			k++;
		}
		if (!needle[k])
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}
