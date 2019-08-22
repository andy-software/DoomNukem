/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:30:58 by apavlov           #+#    #+#             */
/*   Updated: 2018/10/29 16:18:59 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_lenght_for_string(int n)
{
	int	len;

	len = 0;
	if (n < 0 && n != -2147483648)
	{
		n = -n;
		len++;
	}
	else if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	power(int n, int power)
{
	int	res;

	res = 1;
	while (power-- > 0)
		res *= n;
	return (res);
}

static void	bad_numbers(char *str, int *num, int *i)
{
	if (*num == -2147483648)
	{
		str[(*i)++] = '-';
		str[(*i)++] = '2';
		*num = 147483648;
	}
	else if (*num < 0)
	{
		*num = -(*num);
		str[(*i)++] = '-';
	}
	else if (*num == 0)
		str[(*i)++] = '0';
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		len;

	len = get_lenght_for_string(n);
	str = ft_strnew((size_t)len);
	if (str)
	{
		i = 0;
		bad_numbers(str, &n, &i);
		while (i < len)
		{
			str[i] = n / power(10, len - i - 1) + '0';
			n %= power(10, len - i - 1);
			i++;
		}
	}
	else
		return (NULL);
	return (str);
}
