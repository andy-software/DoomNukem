/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 19:38:04 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/23 19:38:04 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		find_count_and_width_of_slice(t_render *r)
{
	int		count_slice;
	int		len;

	len = r->end_x - r->begin_x;
	count_slice = 0;
	while (len >= count_slice * MIN_SLICE_WIDTH && \
								count_slice < MAX_THREADS_IN_RENDER)
		count_slice++;
	r->width_slice = (float)len / count_slice;
	r->count_slice = count_slice;
	return (1);
}

int		fill_the_params(t_render *r, t_thread *t)
{
	int		i;

	i = 0;
	while (i < r->count_slice)
	{
		t[i].id = i;
		t[i].begin_x = i * r->width_slice + r->begin_x;
		t[i].end_x = (i + 1) * r->width_slice + r->begin_x;
		t[i].cc = r->ceil_cal;
		t[i].fc = r->floor_cal;
		t[i].r = r;
		i++;
	}
	t[r->count_slice - 1].end_x = r->end_x;
	return (1);
}
