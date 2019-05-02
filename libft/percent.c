/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:43:41 by apavlov           #+#    #+#             */
/*   Updated: 2019/01/09 11:45:18 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	percent(int start, int end, int current)
{
	int	placement;
	int	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / ((float)distance)));
}
