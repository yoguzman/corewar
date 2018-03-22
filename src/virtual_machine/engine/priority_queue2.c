/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 20:22:10 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/19 18:54:19 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

void		bubble_up(t_mh *mh, uint32_t index, t_proc *entry)
{
	t_proc	**parent;

	while (index != 0
			&& (CTE(*(parent = mh->tab + PARENT(index))) > CTE(entry)
			|| (CTE(*parent) == CTE(entry) && PID(entry) > PID(*parent))))
	{
		mh->tab[index] = *parent;
		index = PARENT(index);
	}
	mh->tab[index] = entry;
}
