/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 15:21:16 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/06 19:56:28 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*new_start;

	if (!lst)
		return (0);
	new = ft_lstnew(f(lst)->content, f(lst)->content_size);
	if (!new)
		return (0);
	new_start = new;
	while (lst->next)
	{
		lst = lst->next;
		new->next = ft_lstnew(f(lst)->content, f(lst)->content_size);
		new = new->next;
		if (!new)
			return (new_start);
	}
	return (new_start);
}
