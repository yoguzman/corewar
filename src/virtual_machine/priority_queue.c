/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:45:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/13 20:02:34 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "vm.h"

/*
** Processes are initially spawned in descending order
*/

static void	*fail_alloc(t_mh *mh)
{
	uint64_t	i;

	if (mh->tab)
	{
		i = 0;
		while (i < mh->pos)
		{
			free(mh->tab[i]);
			++i;
		}
		free(mh->tab);
	}
	free(mh);
	return (NULL);
}

t_mh	*init_heap(t_player player_table[MAX_PLAYERS], uint64_t *total_proc,
		t_corewar *vm, t_instr *instr)
{
	t_mh	*mh;
	t_proc	*process;
	int32_t	i;

	if (!(mh = (t_mh *)malloc(sizeof(*mh))))
		return (NULL);
	ft_bzero(mh, sizeof(*mh));
	if (!(mh->tab = (t_proc **)malloc(sizeof(void *) * START_HEAP_SIZE)))
		return (fail_alloc(mh));
	mh->size = START_HEAP_SIZE;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (player_table[i].code != NULL)
		{
			if (!(process = spawn_process(player_table[i].load_address, i,
							total_proc)))
				return (fail_alloc(mh));
			if (vm->arena[process->pc] - 1 <= 15)
				process->cycles_to_exec =
					instr->op_tab[vm->arena[process->pc] - 1].cycles_to_exec;
			insert(mh, process);
		}
		++i;
	}
	return (mh);
}

void		insert(t_mh *mh, t_proc *entry)
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
	while (i != 0
			&& (CTE(*(parent = mh->tab + PARENT(i))) > CTE(entry)
			|| (CTE(*parent) == CTE(entry) && PID(entry) > PID(*parent))))
	{
		mh->tab[i] = *parent;
		i = PARENT(i);
	}
	mh->tab[i] = entry;
}

void		heapify(t_mh *mh, uint32_t i)
{
	t_proc	**smallest;
	t_proc	**left;
	t_proc	**right;
	t_proc	**parent;

	left = mh->tab + LCHILD(i);
	right = mh->tab + RCHILD(i);
	parent = mh->tab + i;
	if (LCHILD(i) < (long)mh->pos
			&& (CTE(*left) < CTE(*parent)
			|| (CTE(*left) == CTE(*parent) && PID(*left) > PID(*parent))))
		smallest = left;
	else
		smallest = parent;
	if (RCHILD(i) < (long)mh->pos
			&& (CTE(*right) < CTE(*smallest)
			|| (CTE(*right) == CTE(*smallest) && PID(*right) > PID(*smallest))))
		smallest = right;
	if (smallest - mh->tab != i)
	{
		swap_process(parent, smallest);
		heapify(mh, smallest - mh->tab);
	}
}

void		delete_any(t_mh *mh, uint32_t i)
{
	if (mh->pos)
	{
		free(mh->tab[i]);
		mh->tab[i] = mh->tab[--(mh->pos)];
		heapify(mh, i);
	}
	else
		free(mh->tab);
}

t_proc		*pop_min(t_mh *mh)
{
	t_proc	*p;

	p = mh->tab[0];
	mh->tab[0] = mh->tab[--(mh->pos)];
	heapify(mh, 0);
	return (p);
}
