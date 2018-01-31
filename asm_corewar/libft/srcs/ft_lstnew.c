/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:45:42 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:37:43 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	size_t	n;

	n = 0;
	if ((new = (t_list*)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content &&
			(new->content = (char*)malloc(content_size * sizeof(char))) == NULL)
		return (NULL);
	while (content && n < content_size)
	{
		((char*)new->content)[n] = ((char*)content)[n];
		n++;
	}
	new->content_size = content_size;
	new->next = NULL;
	if (!content)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	return (new);
}
