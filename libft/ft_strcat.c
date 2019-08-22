/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:49:51 by apavlov           #+#    #+#             */
/*   Updated: 2018/10/29 15:03:38 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *restrict s1, const char *restrict s2)
{
	int		i;
	int		k;

	i = 0;
	while (s1[i])
		i++;
	k = -1;
	while (s2[++k])
		s1[i + k] = s2[k];
	s1[i + k] = '\0';
	return (s1);
}
