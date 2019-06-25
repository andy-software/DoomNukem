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

static void	cpy_the_rest(unsigned long *wdst, unsigned long *wsrc, size_t n)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	int				i;
	int				m;

	cdst = (unsigned char*)wdst;
	csrc = (unsigned char*)wsrc;
	i = -1;
	m = n % sizeof(long);
	while (++i < m)
		*(cdst++) = *(csrc++);
}

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	int				i;
	int				m;
	unsigned long	*wdst;
	unsigned long	*wsrc;

	wdst = (unsigned long*)dst;
	wsrc = (unsigned long*)src;
	i = -1;
	m = n / sizeof(long);
	while (++i < m)
		*(wdst++) = *(wsrc++);
	cpy_the_rest(wdst, wsrc, n);
	return (dst);
}
