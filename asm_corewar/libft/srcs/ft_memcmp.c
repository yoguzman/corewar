/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:49:21 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:38:00 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int		count;
	const unsigned char	*byte_s1;
	const unsigned char	*byte_s2;
	int					diff;

	count = 0;
	byte_s1 = s1;
	byte_s2 = s2;
	while (count < n)
	{
		diff = byte_s1[count] - byte_s2[count];
		if (diff != 0)
			return (diff);
		count++;
	}
	return (0);
}
