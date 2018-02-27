/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:45:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/25 20:13:45 by abeauvoi         ###   ########.fr       */
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

	if (mh->pos == mh->size)
	{
		mh->size <<= 1;
		if (!(mh->tab = realloc(mh->tab, sizeof(void *) * mh->size)))
			return ;
		ft_bzero(&mh->tab[mh->pos], mh->pos);
	}
	i = mh->pos++;
	parent = PARENT(i);
	while (i != 0 && CTE(mh->tab[parent]) > CTE(entry))
	{
		mh->tab[i] = mh->tab[parent];
		i = PARENT(i);
		parent = PARENT(i);
	}
	mh->tab[i] = entry;
}

void	heapify(t_mh *mh, uint32_t i)
{
	uint32_t	smallest;
	uint32_t	left;
	uint32_t	right;

	left = LCHILD(i);
	right = RCHILD(i);
	smallest = left < mh->size
		&& CTE(mh->tab[left]) < CTE(mh->tab[i]) ? left : i;
	if (right < mh->size && CTE(mh->tab[right]) < CTE(mh->tab[smallest]))
		smallest = right;
	if (smallest != i)
	{
		swap_process(&(mh->tab[i]), &(mh->tab[smallest]));
		heapify(mh, smallest);
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
