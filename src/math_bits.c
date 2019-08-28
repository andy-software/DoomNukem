/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:57:23 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/23 18:00:08 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			reverse_bits(int b)
{
	return ((b * 0x0202020202ULL & 0x010884422010ULL) % 0x3ff);
}

int			line_point_int(int start, int end, int p)
{
	return (start + (end - start) * p / 100);
}

Uint32		get_color_value_int(Uint32 start, Uint32 end, int perc)
{
	int		r;
	int		g;
	int		b;

	r = line_point_int((start >> 16) & 0xFF, (end >> 16) & 0xFF, perc);
	g = line_point_int((start >> 8) & 0xFF, (end >> 8) & 0xFF, perc);
	b = line_point_int(start & 0xFF, end & 0xFF, perc);
	return ((r << 16) | (g << 8) | b);
}

Uint32		get_color_value(Uint32 start, Uint32 end, float perc)
{
	int		r;
	int		g;
	int		b;

	r = line_point((start >> 16) & 0xFF, (end >> 16) & 0xFF, perc);
	g = line_point((start >> 8) & 0xFF, (end >> 8) & 0xFF, perc);
	b = line_point(start & 0xFF, end & 0xFF, perc);
	return ((r << 16) | (g << 8) | b);
}
