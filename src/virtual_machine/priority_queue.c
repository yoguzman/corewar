/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:45:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/01 17:37:48 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "vm.h"

/*
** Processes are initially spawned in descending order
*/

t_mh	*init_heap(t_player player_table[MAX_PLAYERS], uint64_t *total_proc, t_corewar *vm, t_instr *instr)
{
	t_mh	*mh;
	int32_t	i;

	if (!(mh = (t_mh *)malloc(sizeof(*mh))))
		return (NULL);
	ft_bzero(mh, sizeof(*mh));
	if (!(mh->tab = (t_proc **)malloc(sizeof(void *) * 4)))
		return (NULL);
	mh->size = START_HEAP_SIZE;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (player_table[i].code != NULL)
		{
			mh->tab[mh->pos] = spawn_process(player_table[i].load_address, i,
					total_proc);
			if (vm->arena[mh->tab[mh->pos]->pc] - 1 <= 15)
				mh->tab[mh->pos]->cycles_to_exec = instr->op_tab[vm->arena[mh->tab[mh->pos]->pc] - 1].cycles_to_exec;
			heapify(mh, mh->pos);
			++mh->pos;
		}
		++i;
	}
	return (mh);
}

void	insert(t_mh *mh, t_proc *entry)
{
	uint32_t	i;
	t_proc		**parent;

	if (mh->pos == mh->size)
	{
		mh->size = (3 * mh->size) >> 1;
		if (!(mh->tab = realloc(mh->tab, sizeof(void *) * mh->size)))
			return ;
		ft_bzero(mh->tab + mh->pos, sizeof(void *) * mh->pos);
	}
	i = mh->pos++;
	while (i != 0 && CTE(*(parent = mh->tab + PARENT(i))) > CTE(entry))
	{
		mh->tab[i] = *parent;
		i = PARENT(i);
	}
	mh->tab[i] = entry;
}

void	heapify(t_mh *mh, uint32_t i)
{
	t_proc	**smallest;
	t_proc	**left;
	t_proc	**right;
	t_proc	**parent;

	left = mh->tab + LCHILD(i);
	right = mh->tab + RCHILD(i);
	parent = mh->tab + i;
	if (LCHILD(i) < mh->pos && left - mh->tab < (long)mh->size
			&& (CTE(*left) < CTE(*parent)
			|| (CTE(*left) == CTE(*parent) && PID(*left) > PID(*parent))))
		smallest = left;
	else
		smallest = parent;
	if (RCHILD(i) < mh->pos && right - mh->tab < (long)mh->size
			&& (CTE(*right) < CTE(*smallest)
			|| (CTE(*right) == CTE(*smallest) && PID(*right) > PID(*smallest))))
		smallest = right;
	if (smallest - mh->tab != i)
	{
		swap_process(parent, smallest);
		heapify(mh, smallest - mh->tab);
	}
}

void	delete_min(t_mh *mh)
{
	if (mh->pos)
	{
		free(mh->tab[0]);
		mh->tab[0] = mh->tab[--(mh->pos)];
		heapify(mh, 0);
	}
	else
		free(mh->tab);
}

void	delete_any(t_mh *mh, uint32_t i)
{
	if (mh->pos)
	{
		//free(mh->tab[i]);
		mh->tab[i] = mh->tab[--(mh->pos)];
		heapify(mh, i);
	}
	else
		free(mh->tab);
}
