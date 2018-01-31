/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 20:28:39 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 03:19:52 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void			ft_list_push_back(t_list **begin_list, void *data)
{
	t_list		*tmp;

	tmp = *begin_list;
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp == NULL)
		*begin_list = ft_create_elem(data);
	else
		tmp->next = ft_create_elem(data);
}
