/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 20:04:52 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/27 18:27:35 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

void	free_champions(t_player player_table[MAX_PLAYERS])
{
	uint8_t	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		free(player_table[i].code);
		++i;
	}
}

void	free_processes(t_mh *mh)
{
	uint32_t	i;

	i = 0;
	while (i < mh->pos)
	{
		free(mh->tab[i]);
		++i;
	}
}

void	free_min_heap(t_mh **mh)
{
	free_processes(*mh);
	free((*mh)->tab);
	free(*mh);
	*mh = NULL;
}

void	clear_data(t_corewar *vm)
{
	free_champions(vm->player_table);
	if (vm->mh)
		free_min_heap(&(vm->mh));
	free(vm->print_data);
	free(vm->arena);
	endwin();
}
