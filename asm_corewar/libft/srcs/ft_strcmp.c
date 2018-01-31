/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:54:15 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:39:30 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int					ft_strcmp(const char *s1, const char *s2)
{
	int				n;
	int				diff;
	unsigned char	*uns1;
	unsigned char	*uns2;

	n = 0;
	uns1 = (unsigned char*)s1;
	uns2 = (unsigned char*)s2;
	while (uns1[n] != '\0' && uns2[n] != '\0')
	{
		diff = uns1[n] - uns2[n];
		if (diff != 0)
			return (diff);
		n++;
	}
	return (uns1[n] - uns2[n]);
}
