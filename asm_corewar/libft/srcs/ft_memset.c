/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:53:35 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:38:15 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void				*ft_memset(void *s, int c, size_t n)
{
	int				count;
	unsigned char	*str;
	unsigned char	un_char_c;

	un_char_c = (unsigned char)c;
	count = 0;
	str = (unsigned char*)s;
	while (count < (int)n)
	{
		str[count] = c;
		count++;
	}
	return (str);
}
