/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 14:22:57 by adauchy           #+#    #+#             */
/*   Updated: 2018/03/28 10:39:46 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "vm.h"

void		caca(uint32_t *cycle, t_corewar *vm, int *count, int *wins)
{
	*cycle = vm->player_table[*count].last_live_nd;
	*wins = *count;
}

void		print_winner(t_corewar *vm)
{
	int			count;
	int			wins;
	uint32_t	cycle;
	uint32_t	pid;
	int			save;

	count = -1;
	wins = -1;
	cycle = 0;
	pid = 0;
	while (++count < MAX_PLAYERS)
	{
		if (vm->player_table[count].code != NULL && (save = count) != -1)
			if (cycle < vm->player_table[count].last_live_nd ||
				(cycle == vm->player_table[count].last_live_nd &&
				pid < vm->player_table[count].pidll_nd))
			{
				caca(&cycle, vm, &count, &wins);
				pid = vm->player_table[count].pidll_nd;
			}
	}
	if (wins == -1)
		wins = save;
	print_winner_msg(vm, wins);
}

void		loop_instr(t_corewar *vm, t_mh *mh, t_instr *instr)
{
	t_proc		proc;
	uint64_t	i;

	if (mh->tab[0].cycles_to_exec - vm->cycle_count > 0)
		return ;
	while (mh->pos > 0 && mh->tab[0].cycles_to_exec - vm->cycle_count == 0)
	{
		proc = pop_min(mh);
		exec_instr(vm, instr, &proc);
		insert(mh, proc);
	}
	i = 0;
	if (vm->visual == 1)
		while (i < vm->mh->pos)
		{
			exec_instr_update_window(mh->tab + i, vm, 7,
					mh->tab[i].inv.save_pc);
			++i;
		}
}

void		visual_option_last(t_corewar *vm)
{
	if (vm->visual == 1)
	{
		attron(COLOR_PAIR(6));
		mvprintw(7, 199 + 8, "%d", vm->cycle_count);
		usleep(vm->cycles_sec);
		vm->one_cycle = 0;
		attroff(COLOR_PAIR(6));
	}
	if (vm->dump_limit > 0 && vm->dump_limit == vm->cycle_count)
	{
		dump_arena(vm->arena);
		clear_data(vm);
		exit(EXIT_SUCCESS);
	}
}

int			engine(t_corewar *vm)
{
	t_instr	instr;

	init_instr(&instr, vm);
	if (vm->visual == 1)
		print_ncurses(vm);
	while (vm->mh->pos > 0)
	{
		if (vm->visual == 1)
			key_action(vm);
		if (vm->paused == 0 || vm->one_cycle == 1)
		{
			if (!vm->visual)
				ft_printf("It is now cycle %u\n",
						vm->cycle_count + 1, vm->nb_processes);
			++(vm->cycle_count);
			--(vm->cycle_to_die);
			if (vm->mh->pos == 0)
				break ;
			loop_instr(vm, vm->mh, &instr);
			check_cycle_to_die(vm);
			visual_option_last(vm);
		}
	}
	print_winner(vm);
	return (0);
}
