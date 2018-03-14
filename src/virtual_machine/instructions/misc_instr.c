/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:19:10 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/14 20:08:43 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "op.h"
#include "vm.h"
#include "libft.h"

void	live(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	uint32_t	player_nb;

	player_nb = -1U - instr->param[0];
	if (player_nb < MAX_PLAYERS)
	{
		++vm->player_table[player_nb].current_live;
		if (vm->visual == 1)
			;
	}
	++lol->current_live;
	if (!vm->visual)
		ft_printf("P\t%u | live %d\n", lol->pid, instr->param[0]);
}

int		reg_test(t_proc *lol, t_instr *instr, uint8_t i)
{
	if (instr->val_arg[i] == T_REG)
		return (lol->reg[instr->param[i] - 1]);
	return (instr->param[i]);
}

void	ft_fork(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	t_proc	*child;

	if (!(child = (t_proc *)malloc(sizeof(*child))))
	{
		perror("Corewar :");
		free_min_heap(&vm->mh);
		exit(EXIT_FAILURE);
	}
	init_child(vm, lol, child, instr);
	child->pc = (instr->save_pc + ((short)instr->param[0] % IDX_MOD))
		% MEM_SIZE;
	if (vm->visual == 1)
		fork_update_window(lol, vm);
	if (!vm->visual)
		ft_printf("P\t%u | fork %d (%d)\n", lol->pid, instr->param[0],
				(instr->save_pc + ((short)instr->param[0] % IDX_MOD))
				% MEM_SIZE);
}

void	zjmp(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	if (lol->carry == 1)
	{
		lol->pc = (instr->save_pc + ((short)instr->param[0] % IDX_MOD))
			% MEM_SIZE;
	}
	if (!vm->visual)
		ft_printf("P\t%u | zjmp %d (%s)\n", lol->pid, instr->param[0],
				(lol->carry == 1 ? "OK" : "FAILED"));
}

void	aff(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	ft_putchar(lol->reg[instr->param[0] - 1] % 256);
	if (!vm->visual)
		ft_printf("P\t%u | aff r%d (%c)\n", lol->pid, instr->param[0],
				lol->reg[instr->param[0] - 1] % 256);
}
