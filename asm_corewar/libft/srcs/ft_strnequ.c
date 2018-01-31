/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:54:50 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:40:30 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	c;

	c = 0;
	if (s1 == NULL && s2 == NULL)
		return (1);
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (c < n && s1[c] != '\0' && s2[c] != '\0')
	{
		if (s1[c] != s2[c])
			return (0);
		c++;
	}
	if (s1[c] == s2[c] || c == n)
		return (1);
	return (0);
}
