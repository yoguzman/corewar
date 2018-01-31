/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:46:38 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:37:56 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void						*ft_memchr(const void *s, int c, size_t n)
{
	size_t					count;
	unsigned char			*byte_s;
	unsigned char			un_char_c;

	un_char_c = (unsigned char)c;
	count = 0;
	byte_s = (unsigned char*)s;
	while (count < n)
	{
		if (byte_s[count] == un_char_c)
			return (&(byte_s[count]));
		count++;
	}
	return (NULL);
}
