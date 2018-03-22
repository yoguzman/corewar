/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 21:50:33 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/25 20:19:29 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "vm.h"

void	dump_arena(uint8_t arena[MEM_SIZE])
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < MEM_SIZE)
	{
		printf("0x%.4x :", i);
		j = 0;
		while (j < 63)
		{
			printf(" %.2x", arena[i + j]);
			++j;
		}
		printf(" %.2x\n", arena[i + j]);
		i += 64;
	}
}
