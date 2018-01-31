/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_nb_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 20:20:42 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/18 20:21:13 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

unsigned int	get_size_nb_base(unsigned long long nb, char *base)
{
	unsigned long long	div;
	unsigned long long	len_base;
	unsigned int		size;

	div = 1;
	size = 1;
	len_base = ft_strlen(base);
	while (nb / div >= len_base)
	{
		div *= len_base;
		size += 1;
	}
	return (size);
}
