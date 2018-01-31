/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:42:07 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:37:39 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first;
	t_list	*prev;
	t_list	*new;

	prev = NULL;
	first = NULL;
	while (lst)
	{
		if ((new = f(lst)) == NULL)
			return (NULL);
		if (prev)
			prev->next = new;
		if (!first)
			first = new;
		prev = new;
		lst = lst->next;
	}
	return (first);
}
