/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:00:07 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/06 19:52:35 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	new = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (new)
	{
		i = 0;
		while (*s1)
		{
			new[i] = *s1;
			i++;
			s1++;
		}
		while (*s2)
		{
			new[i] = *s2;
			i++;
			s2++;
		}
	}
	else
		return (NULL);
	return (new);
}
