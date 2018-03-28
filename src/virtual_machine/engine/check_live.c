/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:52:47 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/28 10:24:41 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static void	michel(t_corewar *vm, uint64_t i)
{
	if (!vm->visual)
		ft_printf("Process %u has been terminated (CTD %u)\n",
				vm->mh->tab[i].pid, vm->cycle_to_die_max);
	if (vm->visual == 1)
		mvprintw(9, 199 + 12, "%-10d", vm->nb_processes);
}

int			check_live_process(t_mh *mh, t_corewar *vm)
{
	uint64_t	i;
	int			ret;

	i = 0;
	ret = 0;
	while (i < mh->pos)
	{
		if (mh->tab[i].current_live == 0)
		{
			if (vm->visual == 1)
				exec_instr_update_window(mh->tab + i, vm, 2,
						mh->tab[i].inv.save_pc);
			delete_any(mh, i);
			--vm->nb_processes;
			michel(vm, i);
		}
		else
		{
			ret += mh->tab[i].current_live;
			mh->tab[i].current_live = 0;
			++i;
		}
	}
	return (ret);
}

void		check_live_player(t_corewar *vm, t_player player_table[MAX_PLAYERS])
{
	int			i;
	int			pos;

	i = 0;
	pos = 11;
	while (i < MAX_PLAYERS)
	{
		if (player_table[i].code != NULL && player_table[i].die == 0)
		{
			if (player_table[i].current_live == 0)
			{
				player_table[i].die = 1;
				continue ;
			}
		}
		player_table[i].current_live = 0;
		if (vm->visual == 1 && player_table[i].code != NULL)
		{
			mvprintw(pos + 2, 201,
					"Lives in current period :       %-5d",
					0);
			pos += 4;
		}
		++i;
	}
}

void		check_cycle_to_die(t_corewar *vm)
{
	int		ret;

	if (vm->cycle_to_die <= 0)
	{
		check_live_player(vm, vm->player_table);
		ret = check_live_process(vm->mh, vm);
		--vm->max_check;
		if (ret >= NBR_LIVE)
		{
			vm->cycle_to_die_max -= CYCLE_DELTA;
			vm->max_check = MAX_CHECKS;
		}
		if (vm->max_check == 0)
		{
			vm->cycle_to_die_max -= CYCLE_DELTA;
			vm->max_check = MAX_CHECKS;
		}
		vm->cycle_to_die = vm->cycle_to_die_max;
		if (!vm->visual)
			ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
		if (vm->visual == 1)
			mvprintw(33, 199, "CYCLE_TO_DIE : %-5d", vm->cycle_to_die_max);
	}
}
