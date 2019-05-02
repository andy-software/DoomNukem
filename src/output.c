/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 14:10:00 by apavlov           #+#    #+#             */
/*   Updated: 2019/03/23 14:10:01 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			print_usage(void)
{
	ft_putstr("usage: ./doom-nukem {edit, new, play} {map_name}\n");
	ft_putstr("One day this will run with OpenCL\n");
	return (0);
}

int			error_message(char *message)
{
	ft_putstr(message);
	ft_putchar('\n');
	return (0);
}
