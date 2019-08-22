/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 14:10:52 by apavlov           #+#    #+#             */
/*   Updated: 2018/11/03 15:49:02 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;

	if (!*alst || !alst)
		return ;
	while (*alst)
	{
		next = (*alst)->next;
		ft_lstdelone(alst, del);
		(*alst) = next;
	}
	ft_memdel((void**)alst);
}
