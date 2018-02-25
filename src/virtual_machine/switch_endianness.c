/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_endianness.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:43:48 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/25 20:22:24 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	switch_endianness(void *mem, uint64_t mem_size)
{
	uint8_t	*a;
	uint8_t	*b;
	uint8_t	swap;

	a = (uint8_t *)mem;
	b = (uint8_t *)mem + mem_size;
	while (a < --b)
	{
		swap = *a;
		*a = *b;
		*b = swap;
		++a;
	}
}
