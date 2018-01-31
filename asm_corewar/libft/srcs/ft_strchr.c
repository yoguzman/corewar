/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:54:10 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:39:18 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*ft_strchr(const char *s, int c)
{
	int		n;
	int		size;

	size = ft_strlen(s);
	n = 0;
	if (!s)
		return (NULL);
	while (n <= size)
	{
		if (s[n] == c)
			return ((char*)(&(s[n])));
		n++;
	}
	return (NULL);
}
