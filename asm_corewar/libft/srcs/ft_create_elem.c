/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 20:16:21 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 03:25:52 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list			*ft_create_elem(void *data)
{
	t_list		*elem;

	if ((elem = malloc(sizeof(t_list))) == NULL)
	{
		ft_put_err("malloc failed");
		return (NULL);
	}
	elem->content = data;
	elem->next = NULL;
	return (elem);
}
