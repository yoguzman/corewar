/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 23:04:45 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/21 18:10:02 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

unsigned int	get_size_nb(long long nb)
{
	unsigned long long	un_nb;
	long long			div;
	int					size;
	int					minus;

	div = 1;
	size = 1;
	minus = 0;
	un_nb = nb;
	if (nb < 0 && (minus = 1))
		un_nb = -nb;
	while (un_nb / div >= 10)
	{
		div *= 10;
		size += 1;
	}
	if (minus)
		return (size + 1);
	return (size);
}
