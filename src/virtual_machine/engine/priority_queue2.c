/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 20:22:10 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/16 20:25:11 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

void		bubble_up(t_mh *mh, uint32_t index, t_proc *to_del)
{
	t_proc	**parent;

	while (index != 0
			&& (CTE(*(parent = mh->tab + PARENT(index))) > CTE(to_del)
			|| (CTE(*parent) == CTE(to_del) && PID(to_del) > PID(*parent))))
	{
		mh->tab[index] = *parent;
		index = PARENT(index);
	}
	mh->tab[index] = to_del;
}
