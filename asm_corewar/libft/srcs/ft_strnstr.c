/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:54:55 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:40:38 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int			this_cmp_len(const char *big, const char *little, int len)
{
	int	n;

	n = 0;
	if (len < (int)ft_strlen(little))
		return (0);
	while (big[n] != '\0' && little[n] != '\0' && n < len)
	{
		if (big[n] != little[n])
			return (0);
		n++;
	}
	return (1);
}

char				*ft_strnstr(const char *big, const char *little,
			size_t len)
{
	size_t	n;

	n = 0;
	while (big[n] != '\0' && n < len)
	{
		if (this_cmp_len(&(big[n]), little, len - n))
			return ((char*)(&(big[n])));
		n++;
	}
	return (NULL);
}
