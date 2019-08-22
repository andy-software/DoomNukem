/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:26:47 by apavlov           #+#    #+#             */
/*   Updated: 2018/10/26 17:58:06 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*new;
	unsigned int	i;

	if (!s)
		return (0);
	new = ft_strnew(ft_strlen(s));
	if (!new)
		return (0);
	i = 0;
	while (s[i])
	{
		new[i] = f(s[i]);
		i++;
	}
	return (new);
}
