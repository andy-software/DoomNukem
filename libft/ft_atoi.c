/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 11:56:54 by apavlov           #+#    #+#             */
/*   Updated: 2018/09/10 21:08:10 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	lenght_of_output(const char *str)
{
	size_t	lenght;
	int		i;

	i = -1;
	lenght = 0;
	while (*str && ((*str >= '\t' && *str <= '\r') || *str == ' '))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (str[++i] >= '0' && str[i] <= '9')
		lenght++;
	return (lenght);
}

int				ft_atoi(const char *str)
{
	int			minus;
	int			i;
	int			res;

	minus = 0;
	i = 0;
	res = 0;
	while (*str && ((*str >= '\t' && *str <= '\r') || *str == ' '))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			minus = 1;
	if (lenght_of_output(str) > 19 && !minus)
		return (-1);
	else if (lenght_of_output(str) > 19 && minus)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		res = (int)(res * 10 + (str[i++] - '0'));
	if (minus)
		return (-1 * res);
	return (res);
}
