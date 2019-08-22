/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:07:06 by apavlov           #+#    #+#             */
/*   Updated: 2018/10/26 18:20:40 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_white_spaces(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

static size_t	get_k(char const *s)
{
	size_t	i;

	i = ft_strlen(s) - 1;
	while (is_white_spaces(s[i]) && i != 0)
		i--;
	return (i + 1);
}

static size_t	get_i(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] && is_white_spaces(s[i]))
		i++;
	return (i);
}

char			*ft_strtrim(char const *s)
{
	char	*new;
	size_t	i;
	size_t	k;
	size_t	j;

	if (s)
	{
		i = get_i(s);
		k = get_k(s);
		if (k < i)
			k = i;
		new = (char *)malloc(sizeof(char) * (k - i + 1));
		if (!new)
			return (0);
		j = 0;
		while (j < k - i)
		{
			new[j] = s[i + j];
			j++;
		}
		new[j] = '\0';
		return (new);
	}
	else
		return (0);
}
