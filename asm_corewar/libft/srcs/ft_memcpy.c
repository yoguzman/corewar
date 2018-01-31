/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:47:01 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:38:04 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void				*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*byte_dest;
	const char		*byte_src;
	unsigned int	count;

	count = 0;
	byte_dest = dest;
	byte_src = src;
	while (count < n)
	{
		byte_dest[count] = byte_src[count];
		count++;
	}
	return (dest);
}
