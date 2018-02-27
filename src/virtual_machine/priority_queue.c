/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:45:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/27 17:10:42 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "vm.h"

/*
** Processes are initially spawned in descending order
*/

t_mh	*init_heap(t_player player_table[MAX_PLAYERS])
{
	t_mh	*mh;
	int32_t	i;

	if (!(mh = (t_mh *)malloc(sizeof(*mh)))
			|| !(mh->tab = (t_proc **)malloc(sizeof(void *) * 4)))
		return (NULL);
	mh->size = 4;
	i = 4;
	while (i-- != 0)
	{
		if (player_table[i].code != NULL)
			mh->tab[mh->pos++] = spawn_process(PT(i).load_address, i);
	}
	return (mh);
}

void	insert(t_mh *mh, t_proc *entry)
{
	uint32_t	i;
	uint32_t	parent;
	t_proc		**parent;

	if (mh->pos == mh->size)
	{
		mh->size <<= 1;
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
	if (left - mh->tab < mh->size && CTE(*left) < CTE(*parent)
			|| (CTE(*left) == CTE(*parent) && PID(*left) < PID(*parent)))
		smallest = left;
	else
		smallest = i;
	if (right - mh->tab < mh->size && CTE(*right) < CTE(*smallest)
			|| (CTE(*right) == CTE(*smallest) && PID(*right) < PID(*smallest)))
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
		mh->tab[0] = mh->tab[--(mh->pos)];
		heapify(mh, 0);
	}
	else
		free(mh->tab);
}
