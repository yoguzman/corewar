/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:55:05 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:40:53 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	n;
	char	*ret;

	n = 0;
	if (s == NULL || start >= ft_strlen(s) ||
		start + len > ft_strlen(s))
		return (NULL);
	if ((ret = (char*)malloc((len + 1) * sizeof(char))) == NULL)
		return (NULL);
	while (n < len)
	{
		ret[n] = s[n + start];
		n++;
	}
	ret[n] = '\0';
	return (ret);
}
