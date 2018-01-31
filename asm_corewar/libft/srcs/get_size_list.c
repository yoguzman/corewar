/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:48:14 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 05:07:58 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		get_size_list(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		list = list->next;
		count += 1;
	}
	return (count);
}
