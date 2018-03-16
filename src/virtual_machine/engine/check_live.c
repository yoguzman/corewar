/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:52:47 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/14 14:53:22 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		check_live_process(t_mh *mh, t_corewar *vm)
{
	uint64_t	i;

	i = 0;
	while (i < mh->pos)
	{
		if (mh->tab[i]->current_live == 0)
		{
			if (vm->visual == 1)
				exec_instr_update_window(mh->tab[i], vm, 2, mh->tab[i]->inv.save_pc);
			delete_any(mh, i);
			--vm->nb_processes;
			if (vm->visual == 1)
				mvprintw(9, 199 + 12, "%-10d", vm->nb_processes);
		}
		else
		{
			mh->tab[i]->current_live = 0;
			++i;
		}
	}
}

int			check_live_player(t_player player_table[MAX_PLAYERS])
{
	int			i;
	int			count_live;

	i = 0;
	count_live = 0;
	while (i < MAX_PLAYERS)
	{
		if (player_table[i].code != NULL && player_table[i].die == 0)
		{
			if (player_table[i].current_live == 0)
			{
				player_table[i].die = 1;
				continue ;
			}
			else
				count_live += player_table[i].current_live;
			player_table[i].current_live = 0;
		}
		++i;
	}
	return (count_live);
}

void		check_cycle_to_die(t_corewar *vm)
{
	int		ret;

	if (vm->cycle_to_die == 0)
	{
		ret = check_live_player(vm->player_table);
		check_live_process(vm->mh, vm);
		--vm->max_check;
		if (ret >= NBR_LIVE)
		{
			vm->cycle_to_die_max -= CYCLE_DELTA;
			vm->max_check = MAX_CHECKS;
		}
		if (vm->max_check == 0)
			vm->cycle_to_die_max -= CYCLE_DELTA;
		vm->cycle_to_die = vm->cycle_to_die_max;
	}
}
