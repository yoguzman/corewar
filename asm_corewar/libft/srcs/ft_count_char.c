/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:42:15 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:36:48 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int			ft_count_char(char *s, char c)
{
	int		n;
	int		count;

	count = 0;
	n = 0;
	if (!s)
		return (-1);
	while (s[n])
	{
		if (s[n] == c)
			count++;
		n++;
	}
	return (count);
}
