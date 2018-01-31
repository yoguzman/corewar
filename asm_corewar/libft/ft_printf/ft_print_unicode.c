/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unicode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 12:11:29 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/22 20:49:42 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			get_size_unicode(wchar_t c)
{
	int		max;

	max = 0xFFFF;
	if (c > max)
		return (4);
	if (c > (max >>= 5))
		return (3);
	if (c > (max >>= 4))
		return (2);
	return (1);
}

int			convert_unicode(wchar_t c, char tab[4])
{
	int		max;
	int		n;
	char	mask;
	int		nb_bytes;

	max = 0xFFFF;
	n = 4;
	mask = -0x80;
	nb_bytes = 1;
	while (--n > 0)
	{
		if (max == 1 || (c > max && (max = 1)))
		{
			tab[n] = (char)c;
			tab[n] &= (char)0x3F;
			tab[n] |= (char)-0x80;
			c >>= 6;
			mask /= 2;
			nb_bytes++;
		}
		max >>= ((n == 3) ? 5 : 4);
	}
	tab[0] = (char)c;
	tab[0] |= ((mask == -0x80) ? (char)0 : (char)mask);
	return (nb_bytes);
}

int			ft_put_unicode(wchar_t car)
{
	char			tab[4];

	write(1, tab, convert_unicode(car, tab));
	return (1);
}

int			ft_print_unicode(wchar_t *string)
{
	int				car;

	car = 0;
	while (*string)
	{
		ft_put_unicode(*string);
		car++;
		string++;
	}
	return (car);
}
