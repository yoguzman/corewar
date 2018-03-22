/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listpush_back_double.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 17:27:19 by yguzman           #+#    #+#             */
/*   Updated: 2018/03/14 18:34:50 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int				list_push_back_alloc_content(t_list **list, void *content,
		size_t size)
{
	t_list			*new;
	t_list			*tmp;

	if ((new = malloc(sizeof(t_list))) == NULL)
		return (-1);
	new->next = NULL;
	new->prev = NULL;
	if ((new->content = ft_memalloc(size)) == NULL)
		return (-1);
	ft_memcpy(new->content, content, size);
	new->content_size = size;
	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (0);
}

int				list_push_back(t_list **list, void *content, size_t size)
{
	t_list			*new;
	t_list			*tmp;

	if ((new = malloc(sizeof(t_list))) == NULL)
		return (-1);
	new->next = NULL;
	new->prev = NULL;
	new->content = content;
	new->content_size = size;
	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (0);
}
