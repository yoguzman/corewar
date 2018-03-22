/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 21:33:05 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/21 19:08:48 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

uint32_t	get_load_address(t_corewar *vm, int32_t load_address,
		uint32_t prog_size)
{
	uint32_t	i;

	i = 0;
	while (i < prog_size)
	{
		if (vm->arena[(i + load_address) % MEM_SIZE] != 0)
		{
			load_address = (load_address + i + (MEM_SIZE / vm->players))
				% MEM_SIZE;
			i = 0;
			continue ;
		}
		++i;
	}
	return (load_address);
}

int			count_players(const char *argv[])
{
	int		count;

	count = 0;
	while (*argv != NULL)
	{
		if ((*argv)[0] != '-' && count < MAX_PLAYERS && !ft_isdigitstr(*argv))
			++count;
		++argv;
	}
	return (count);
}

void		safe_memcpy(void *dest, const void *src, size_t n, uint32_t start)
{
	char	*buff;
	char	*buff1;
	size_t	i;

	buff = (char *)src;
	buff1 = (char *)dest;
	i = 0;
	while (i < n)
	{
		buff1[(i + start) % MEM_SIZE] = buff[i];
		++i;
	}
}
