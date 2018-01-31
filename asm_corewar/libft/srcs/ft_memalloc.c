/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:46:23 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:37:48 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		*ft_memalloc(size_t size)
{
	char	*ptr;
	size_t	count;

	count = 0;
	if ((ptr = (char*)malloc(size * sizeof(char))) == NULL)
		return (NULL);
	while (count < size)
	{
		ptr[count] = 0;
		count++;
	}
	return (ptr);
}
