/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:45:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/19 19:24:13 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "vm.h"

/*
** Processes are initially spawned in descending order
*/

t_mh		*init_heap(t_player player_table[MAX_PLAYERS], uint64_t *total_proc,
		t_corewar *vm, t_instr *instr)
{
	t_mh	*mh;
	t_proc	*process;
	int32_t	i;

	if (!(mh = (t_mh *)malloc(sizeof(*mh))))
		return (fail_alloc(&mh));
	ft_bzero(mh, sizeof(*mh));
	mh->size = START_HEAP_SIZE;
	if (!(mh->tab = (t_proc **)malloc(sizeof(void *) * mh->size)))
		return (fail_alloc(&mh));
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (player_table[i].code != NULL)
		{
			if (!(process = spawn_process(player_table[i].load_address, i,
							total_proc)))
				return (fail_alloc(&mh));
			fill_ins_proc(vm, instr, process);
			insert(mh, process);
		}
	}
	return (mh);
}

void		insert(t_mh *mh, t_proc *entry)
{
	if (mh->pos == mh->size)
	{
		mh->size = (3 * mh->size) >> 1;
		if (!(mh->tab = realloc(mh->tab, sizeof(void *) * mh->size)))
		{
			perror("Corewar :");
			free_min_heap(&mh);
			exit(EXIT_FAILURE);
		}
		ft_bzero(mh->tab + mh->pos, sizeof(void *) * (mh->size - mh->pos));
	}
	bubble_up(mh, mh->pos, entry);
	++mh->pos;
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
	t_proc	*ptr1;
	t_proc	*ptr2;
	int		p;

	if (mh->pos)
	{
		free(mh->tab[i]);
		if (--(mh->pos) == 0)
			return ;
		mh->tab[i] = mh->tab[mh->pos];
		if ((p = PARENT((int)i)) < 0)
		{
			heapify(mh, 0);
			return ;
		}
		ptr1 = mh->tab[p];
		ptr2 = mh->tab[i];
		if (i > 0 && (CTE(ptr1) > CTE(ptr2)
					|| (CTE(ptr1) == CTE(ptr2) && PID(ptr1) < PID(ptr2))))
			bubble_up(mh, i, ptr2);
		else
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
