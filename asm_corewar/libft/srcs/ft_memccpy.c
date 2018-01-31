/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:53:14 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:37:52 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void				*ft_memccpy(void *dest, const void *src,
					int c, size_t n)
{
	unsigned char	*byte_dest;
	unsigned char	*byte_src;
	size_t			count;
	unsigned char	un_c;

	count = 0;
	byte_dest = (unsigned char*)dest;
	byte_src = (unsigned char*)src;
	un_c = (unsigned char)c;
	while (count < n && byte_src[count] != un_c)
	{
		byte_dest[count] = byte_src[count];
		count++;
	}
	if (count < n && byte_src[count] == un_c)
	{
		byte_dest[count] = byte_src[count];
		return (&byte_dest[count + 1]);
	}
	else
		return (NULL);
}
