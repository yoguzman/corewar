/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 21:19:05 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:40:03 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t				ft_strlcat(char *dest, const char *src, size_t size)
{
	int				len_dest;
	int				len_src;
	int				n;

	n = 0;
	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	n = 0;
	while (n + len_dest < (int)size - 1 && src[n])
	{
		dest[len_dest + n] = src[n];
		n++;
	}
	if (n + len_dest == (int)size - 1 || !src[n])
		dest[len_dest + n] = '\0';
	if ((int)size <= len_dest)
		return (len_src + size);
	return (len_dest + len_src);
}
