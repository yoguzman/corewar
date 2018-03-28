/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:47:33 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/28 12:57:12 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "op.h"
#include "vm.h"

static const t_op		g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, {0}},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, {1, 0}},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, {0, 1}},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, {0, 0, 0}},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, {0, 0, 0}},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, {1, 1, 0}},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, {1, 1, 0}},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, {1, 1, 0}},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, {0}},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, {2, 0, 0}},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, {0, 2, 0}},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, {0}},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, {1, 0}},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, {1, 1, 0}},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, {0}},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, {0}},
	{0, 0, {0}, 0, 0, 0, 0, 0, {0, 0, 0}}
};

void	init_tab_instr(void (*tab_instr[16])(t_corewar *vm,
			t_proc *lol, t_instr *instr))
{
	tab_instr[0] = &live;
	tab_instr[1] = &ld;
	tab_instr[2] = &st;
	tab_instr[3] = &add;
	tab_instr[4] = &sub;
	tab_instr[5] = &ft_and;
	tab_instr[6] = &ft_or;
	tab_instr[7] = &ft_xor;
	tab_instr[8] = &zjmp;
	tab_instr[9] = &ldi;
	tab_instr[10] = &sti;
	tab_instr[11] = &ft_fork;
	tab_instr[12] = &lld;
	tab_instr[13] = &lldi;
	tab_instr[14] = &ft_lfork;
	tab_instr[15] = &aff;
}

int		init_instr(t_instr *instr, t_corewar *vm)
{
	init_op_tab(g_op_tab, instr);
	init_tab_instr(instr->tab_instr);
	vm->mh = init_heap(vm->player_table, &(vm->total_proc), vm, instr);
	if (!vm->mh)
		exit(EXIT_FAILURE);
	vm->cycle_to_die_max = CYCLE_TO_DIE;
	vm->cycle_to_die = vm->cycle_to_die_max;
	vm->paused = 0;
	vm->max_check = MAX_CHECKS;
	return (0);
}

void	init_op_tab(const t_op g_op_tab[17], t_instr *instr)
{
	instr->op_tab = g_op_tab;
}
