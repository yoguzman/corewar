/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 14:22:57 by adauchy           #+#    #+#             */
/*   Updated: 2018/03/13 20:07:33 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "vm.h"

void			loop_instr(t_corewar *vm, t_mh *mh, t_instr *instr)
{
	t_proc	*proc;

	if (mh->tab[0]->cycles_to_exec - vm->cycle_count > 0)
		return ;
	while (mh->pos > 0 && mh->tab[0]->cycles_to_exec - vm->cycle_count == 0)
	{
		proc = pop_min(mh);
		exec_instr(vm, instr, proc);
		insert(mh, proc);
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
				printf("It is now cycle %u nb_proc %llu\n", vm->cycle_count + 1, vm->nb_processes);
			++(vm->cycle_count);
			--(vm->cycle_to_die);

			check_cycle_to_die(vm);
			if (vm->mh->pos == 0)
				break ;

			loop_instr(vm, vm->mh, &instr);

			visual_option_last(vm);

		}
	}
	return (0);
}
