/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_endianness.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:43:48 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/22 19:15:14 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	switch_endianness(void *mem, size_t mem_size)
{
	unsigned char	*a;
	unsigned char	*b;
	unsigned char	swap;

	a = (unsigned char *)mem;
	b = (unsigned char *)mem + mem_size;
	while (a < --b)
	{
		swap = *a;
		*a = *b;
		*b = swap;
		++a;
	}
}
