/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 13:52:48 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/03 15:48:22 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	void	*c_content;

	new = (t_list*)malloc(sizeof(t_list));
	if (!new)
		return (0);
	if (content)
	{
		c_content = ft_memalloc(content_size);
		c_content = ft_memcpy(c_content, content, content_size);
	}
	else
		c_content = 0;
	new->content = c_content;
	if (!content)
		new->content_size = 0;
	else
		new->content_size = content_size;
	new->next = 0;
	return (new);
}
