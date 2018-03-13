/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 16:15:57 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/06 18:09:50 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "vm.h"

void	swap_process(t_proc **a, t_proc **b)
{
	t_proc	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_proc	*spawn_process(uint64_t load_address, uint8_t player_id,
		uint64_t *total_proc)
{
	t_proc	*new;

	if (!(new = (t_proc *)malloc(sizeof(*new))))
		return (NULL);
	ft_bzero(new, sizeof(*new));
	new->pc = load_address;
	new->reg[0] = UINT_MAX;
	new->reg[0] -= player_id;
	new->pid = *total_proc;
	++*total_proc;
	return (new);
}

void	kill_process(t_mh *mh, uint32_t index)
{
	free(mh->tab[index]);
	mh->tab[index] = NULL;
}

void	print_processes(t_mh *mh)
{
	uint32_t	i;

	i = 0;
	while (i < mh->pos)
	{
		printf("Process #%u: Owned by player %u\n", i, mh->tab[i]->reg[0] + 1);
		++i;
	}
}
