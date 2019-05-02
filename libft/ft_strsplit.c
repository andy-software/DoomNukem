/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:22:13 by apavlov           #+#    #+#             */
/*   Updated: 2018/10/26 19:30:05 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char delim)
{
	size_t	i;
	int		word;
	size_t	count;

	i = 0;
	word = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != delim && !word)
		{
			count++;
			word = 1;
		}
		else if (s[i] == delim && word)
			word = 0;
		i++;
	}
	return (count);
}

static char		*make_it_shorter(size_t *i, size_t *k, char c, const char *s)
{
	while (s[*i] == c && s[*i])
		(*i)++;
	*k = 0;
	while (s[(*i) + (*k)] != c && s[(*i) + (*k)])
		(*k)++;
	return ((char*)malloc(sizeof(char) * (*k + 1)));
}

char			**ft_strsplit(char const *s, char c)
{
	char	**new;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	count;

	if (!s)
		return (0);
	if (!(new = (char**)malloc(sizeof(char*) * (count_words(s, c) + 1))))
		return (0);
	i = 0;
	j = 0;
	count = count_words(s, c);
	while (j < count)
	{
		if (!(new[j] = make_it_shorter(&i, &k, c, s)))
			return (0);
		k = -1;
		while (s[i + ++k] != c && s[i + k])
			new[j][k] = s[i + k];
		new[j++][k] = '\0';
		i += k;
	}
	new[j] = 0;
	return (new);
}
