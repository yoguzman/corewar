/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:45:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/28 10:21:08 by abeauvoi         ###   ########.fr       */
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
	int32_t	i;

	if (!(mh = (t_mh *)malloc(sizeof(*mh))))
		return (fail_alloc(&mh));
	ft_bzero(mh, sizeof(*mh));
	mh->size = START_HEAP_SIZE;
	if (!(mh->tab = (t_proc *)malloc(sizeof(*mh->tab) * mh->size)))
		return (fail_alloc(&mh));
	ft_bzero(mh->tab, sizeof(t_proc) * mh->size);
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (player_table[i].code != NULL)
		{
			spawn_process(player_table[i].load_address, i, total_proc,
					mh->tab + mh->pos);
			fill_ins_proc(vm, instr, mh->tab + mh->pos);
			bubble_up(mh, mh->pos++);
		}
	}
	return (mh);
}

void		insert(t_mh *mh, t_proc entry)
{
	if (mh->pos == mh->size)
	{
		mh->size = (3 * mh->size) >> 1;
		if (!(mh->tab = realloc(mh->tab, sizeof(t_proc) * mh->size)))
		{
			perror("Corewar :");
			free_min_heap(&mh);
			exit(EXIT_FAILURE);
		}
		ft_bzero(mh->tab + mh->pos, sizeof(t_proc) * (mh->size - mh->pos));
	}
	mh->tab[mh->pos] = entry;
	bubble_up(mh, mh->pos++);
}

void		heapify(t_mh *mh, uint32_t i)
{
	t_proc		lchild;
	t_proc		rchild;
	t_proc		root;
	uint32_t	smallest;

	lchild = mh->tab[LCHILD(i)];
	rchild = mh->tab[RCHILD(i)];
	root = mh->tab[i];
	if (LCHILD(i) < (long)mh->pos
			&& (CTE(lchild) < CTE(root)
			|| (CTE(lchild) == CTE(root) && PID(lchild) > PID(root))))
		smallest = LCHILD(i);
	else
		smallest = i;
	if (RCHILD(i) < (long)mh->pos
			&& (CTE(rchild) < CTE(mh->tab[smallest])
			|| (CTE(rchild) == CTE(mh->tab[smallest])
				&& PID(rchild) > PID(mh->tab[smallest]))))
		smallest = RCHILD(i);
	if (smallest != i)
	{
		swap_process(mh->tab + i, mh->tab + smallest);
		heapify(mh, smallest);
	}
}

void		delete_any(t_mh *mh, uint32_t i)
{
	if (mh->pos)
	{
		mh->tab[i] = mh->tab[--(mh->pos)];
		if (mh->pos == i || mh->pos <= 1)
			return ;
		if (PARENT((int)i) >= 0
				&& (CTE(mh->tab[i]) < CTE(mh->tab[PARENT(i)])
					|| (CTE(mh->tab[i]) == CTE(mh->tab[PARENT(i)])
						&& PID(mh->tab[i]) > PID(mh->tab[PARENT(i)]))))
			bubble_up(mh, i);
		else
			heapify(mh, i);
	}
	else
		free(mh->tab);
}

t_proc		pop_min(t_mh *mh)
{
	t_proc	p;

	p = mh->tab[0];
	mh->tab[0] = mh->tab[--(mh->pos)];
	heapify(mh, 0);
	return (p);
}
