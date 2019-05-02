/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:10:18 by apavlov           #+#    #+#             */
/*   Updated: 2018/10/26 20:25:09 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new;
	size_t	i;

	new = (char*)malloc(size + 1);
	if (new)
	{
		i = 0;
		while (i < size + 1)
			new[i++] = 0;
		return (new);
	}
	else
		return (NULL);
}
