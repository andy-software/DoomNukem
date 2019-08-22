/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:14:12 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/02 16:21:26 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*cpy_s1;
	unsigned char	*cpy_s2;

	i = 0;
	cpy_s1 = (unsigned char *)s1;
	cpy_s2 = (unsigned char *)s2;
	while (cpy_s1[i] == cpy_s2[i] && i < n && cpy_s1[i])
		i++;
	if (i == n || (!cpy_s1[i] && !cpy_s2[i]))
		return (0);
	return (cpy_s1[i] - cpy_s2[i]);
}
