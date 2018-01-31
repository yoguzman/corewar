/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_unicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 22:57:02 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/22 18:56:21 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			write_one_unicode(char *buffer, int pos, char tab[4], int len)
{
	int		count;

	count = 0;
	while (count < len)
	{
		buffer[pos + count] = tab[count];
		count++;
	}
	return (len);
}

void		write_unicode(char *buffer, int *str, int size, int *n)
{
	int		m;
	char	tab[4];
	int		len;
	int		count;

	m = 0;
	count = 0;
	while (count < size)
	{
		len = convert_unicode(str[m], tab);
		count += write_one_unicode(buffer, *n + count, tab,
			(size - count < len ? size - count : len));
		m += 1;
	}
	*n += count;
}
