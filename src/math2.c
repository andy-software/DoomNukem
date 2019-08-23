/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 18:04:19 by myuliia           #+#    #+#             */
/*   Updated: 2019/08/23 18:08:11 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

float		fpercent(float start, float end, float current)
{
	float	placement;
	float	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

float		v2dlenght(float vx, float vy)
{
	return (sqrt(vx * vx + vy * vy));
}

float		line_len(t_vertex start, t_vertex end)
{
	t_vertex	d;

	d.x = end.x - start.x;
	d.y = end.y - start.y;
	return (sqrt(d.x * d.x + d.y * d.y));
}
