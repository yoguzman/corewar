/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:14:05 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/14 20:01:11 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			key_action(t_corewar *vm)
{
	int		ret;

	ret = 0;
	attron(COLOR_PAIR(6));
	ret = getch();
	if (ret == ' ')
		toggle_pause(vm);
	else if (ret == ',')
		dec_speed(vm);
	else if (ret == '.')
		inc_speed(vm);
	else if (ret == 's')
		one_cycle(vm);
	attroff(COLOR_PAIR(6));
}

void			fork_update_window(t_proc *lol, t_corewar *vm)
{
	attron(COLOR_PAIR((-1U - lol->reg[0]) + 2 + 5));
	mvprintw((lol->pc / 64) + 2, (lol->pc % 64) * 3 + 3, "%.2x",
			vm->arena[lol->pc]);
	attroff(COLOR_PAIR((-1U - lol->reg[0]) + 2 + 5));
	attron(COLOR_PAIR(6));
	mvprintw(9, 199 + 12, "%-10d", vm->nb_processes);
	attroff(COLOR_PAIR(6));
}

void			exec_instr_update_window(t_proc *proc, t_corewar *vm, char add, int value)
{
	if ((-1U - proc->reg[0]) > 4)
		attron(COLOR_PAIR(1 + (add == 2 ? 0 : 10)));
	else
		attron(COLOR_PAIR((-1U - proc->reg[0]) + add));
	mvprintw((value / 64) + 2, (value % 64) * 3 + 3, "%.2x",
			vm->arena[value]);
	if ((-1U - proc->reg[0]) > 4)
		attron(COLOR_PAIR(1 + (add == 2 ? 0 : 10)));
	else
		attroff(COLOR_PAIR((-1U - proc->reg[0]) + add));
}
