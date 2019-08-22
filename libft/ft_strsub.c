/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:41:30 by apavlov           #+#    #+#             */
/*   Updated: 2018/10/26 18:05:15 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (!s)
		return (0);
	new = ft_strnew(len);
	if (new)
	{
		i = 0;
		while (s[start + i] && i < len)
		{
			new[i] = s[start + i];
			i++;
		}
	}
	else
		return (NULL);
	return (new);
}
