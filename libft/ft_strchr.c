/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:24:38 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/06 19:50:40 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = -1;
	c = (unsigned)c;
	while (s[++i] || s[i] == c)
		if (s[i] == c)
			return ((char *)(s + i));
	return (0);
}
