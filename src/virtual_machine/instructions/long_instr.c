/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:09:09 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/14 19:17:51 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "op.h"
#include "vm.h"
#include "libft.h"

void		lld(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;
	int	i;

	if (instr->val_arg[0] == T_IND)
	{
		i = 0;
		offset = (instr->save_pc + instr->param[0]);
		lol->reg[instr->param[1] - 1] = 0;
		while (i < 4)
		{
			lol->reg[instr->param[1] - 1] |=
				vm->arena[(offset + i) % MEM_SIZE] << ((3 - i) << 3);
			++i;
		}
	}
	else
		lol->reg[instr->param[1] - 1] = instr->param[0];
	lol->carry = lol->reg[instr->param[1] - 1] == 0;
	if (!vm->visual)
		ft_printf("P\t%u | lld %.*s%d r%d\n", lol->pid,
				(instr->val_arg[0] == T_DIR ? 1 : 0), "%", instr->param[0],
				instr->param[1]);
}

void		lldi(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;
	int	i;

	offset =
		(instr->save_pc + reg_test(lol, instr, 0) + reg_test(lol, instr, 1));
	lol->reg[instr->param[2] - 1] = 0;
	i = 0;
	while (i < 4)
	{
		lol->reg[instr->param[2] - 1] |=
			vm->arena[(offset + i) % MEM_SIZE] << ((3 - i) << 3);
		++i;
	}
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
	if (!vm->visual)
		ft_printf("P\t%u | di %.*s%d %.*s%d r%d\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2]);
}

void		ft_lfork(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	t_proc	*child;

	if (!(child = (t_proc *)malloc(sizeof(*child))))
	{
		perror("Corewar :");
		free_min_heap(&vm->mh);
		exit(EXIT_FAILURE);
	}
	init_child(vm, lol, child, instr);
	child->pc = (instr->save_pc + (short)instr->param[0]) % MEM_SIZE;
	if (vm->visual == 1)
		fork_update_window(lol, vm);
	if (!vm->visual)
		ft_printf("P\t%u | lfork %d (%d)\n", lol->pid, instr->param[0],
				(instr->save_pc + (instr->param[0] % IDX_MOD)) % MEM_SIZE);
}
