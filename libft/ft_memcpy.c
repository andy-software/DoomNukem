/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:03:12 by apavlov           #+#    #+#             */
/*   Updated: 2018/10/29 14:11:02 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*restrict dst, const void *restrict src, size_t n)
{
	size_t			i;
	unsigned char	*tmp;
	unsigned char	*tmp_src;

	i = 0;
	tmp = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	while (i < n)
	{
		tmp[i] = tmp_src[i];
		i++;
	}
	return (dst);
}
