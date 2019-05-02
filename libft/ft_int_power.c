/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:21:04 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/06 17:24:29 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_int_power(long long int num, long long int power)
{
	long long int res;

	res = 1;
	if (power == 0)
		return (res);
	while (power--)
		res *= num;
	return (res);
}
