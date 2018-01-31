/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:55:03 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:40:49 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int			this_cmp(const char *needle, const char *haystack)
{
	int	n;

	n = 0;
	while (needle[n] != '\0' && haystack[n] != '\0')
	{
		if (needle[n] != haystack[n])
			return (0);
		n++;
	}
	if (!needle[n])
		return (1);
	return (0);
}

char				*ft_strstr(const char *haystack, const char *needle)
{
	int	n;

	n = 0;
	if (!*needle)
		return ((char*)haystack);
	while (haystack[n] != '\0')
	{
		if (this_cmp(needle, &(haystack[n])))
			return ((char*)(&(haystack[n])));
		n++;
	}
	return (NULL);
}
