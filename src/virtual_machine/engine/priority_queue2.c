/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 20:22:10 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/24 22:47:03 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		bubble_up(t_mh *mh, uint32_t index)
{
	uint32_t	parent;
	t_proc		tmp;

	tmp = mh->tab[index];
	while (index != 0
			&& (CTE(mh->tab[(parent = PARENT(index))]) > CTE(tmp)
			|| (CTE(mh->tab[parent]) == CTE(tmp)
				&& PID(mh->tab[parent]) < PID(tmp))))
	{
		mh->tab[index] = mh->tab[parent];
		index = PARENT(index);
	}
	mh->tab[index] = tmp;
}
