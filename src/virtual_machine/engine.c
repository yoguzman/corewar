/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 14:22:57 by adauchy           #+#    #+#             */
/*   Updated: 2018/03/09 19:49:22 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "vm.h"

void			loop_instr(t_corewar *vm, t_mh *mh, t_instr *instr)
{
	t_proc	*proc;
//	ft_putstr("\ncycle en cours = ");
//	ft_putnbr(vm->cycle_count);
//	ft_putstr("\ncheck loop instr pid = ");
//	ft_putnbr(mh->tab[0]->pid);
//	ft_putstr(" cycle_to_exec= ");
//	ft_putnbr(mh->tab[0]->cycles_to_exec);
//	ft_putchar('\n');
	if (mh->tab[0]->cycles_to_exec - vm->cycle_count > 0)
		return ;
	while (mh->pos > 0 && mh->tab[0]->cycles_to_exec - vm->cycle_count == 0)
	{
		proc = pop_min(mh);
		exec_instr(vm, instr, proc);
		insert(mh, proc);
	}
}

void		visual_option(t_corewar *vm)
{
	if (vm->visual == 1)
		print_ncurses(vm);
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
	while (vm->mh->pos > 0)
	{
		++(vm->cycle_count);
		printf("Cycle %u\nProcesses %llu\n", vm->cycle_count, vm->total_proc);
		--(vm->cycle_to_die);

		check_cycle_to_die(vm);
		if (vm->mh->pos == 0)
			break ;

		loop_instr(vm, vm->mh, &instr);
		visual_option(vm);
	}
	getch();
	return (0);
}
