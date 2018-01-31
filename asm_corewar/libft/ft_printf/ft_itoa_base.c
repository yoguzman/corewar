/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:28:40 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/19 17:16:51 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			ft_itoa_base(char *str, unsigned long long nb,
					char *base, int size)
{
	unsigned long long	div;
	unsigned long long	len_base;
	int					count;
	int					n;

	count = 0;
	len_base = ft_strlen(base);
	div = 1;
	n = 1;
	while (nb / div >= len_base)
	{
		div *= len_base;
		n += 1;
	}
	n = size - n;
	while (count < n)
		str[count++] = '0';
	while (div)
	{
		str[count] = base[nb / div % len_base];
		div /= len_base;
		count += 1;
	}
}
