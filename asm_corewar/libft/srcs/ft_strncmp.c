/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:54:46 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:40:23 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			count;
	int				diff;
	unsigned char	*uns1;
	unsigned char	*uns2;

	uns1 = (unsigned char*)s1;
	uns2 = (unsigned char*)s2;
	count = 0;
	while (uns1[count] && uns2[count] && count < n)
	{
		diff = uns1[count] - uns2[count];
		if (diff != 0)
			return (diff);
		count++;
	}
	if (count == n)
		return (0);
	return (uns1[count] - uns2[count]);
}
