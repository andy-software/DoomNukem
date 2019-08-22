/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:50:30 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/06 19:48:03 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (!haystack)
		i = (int)haystack[i];
	if (len < ft_strlen(needle))
		return (0);
	if (!needle[0] || haystack == needle)
		return ((char *)haystack);
	while (haystack[i] && len > i)
	{
		k = 0;
		while (needle[k] && len > i + k)
		{
			if (needle[k] != haystack[k + i])
				break ;
			k++;
		}
		if (!needle[k])
			return ((char*)(haystack + i));
		i++;
	}
	return (0);
}
