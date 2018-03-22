/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:09:09 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/21 19:57:32 by abeauvoi         ###   ########.fr       */
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

	(void)instr;
	if (lol->inv.param[1] != 1)
	{
		if (lol->inv.val_arg[0] == T_IND)
		{
			i = -1;
			offset = (lol->inv.save_pc + ((short)lol->inv.param[0] % IDX_MOD));
			lol->reg[lol->inv.param[1] - 1] = 0;
			while (++i < 4)
				lol->reg[lol->inv.param[1] - 1] |=
					vm->arena[(offset + i) % MEM_SIZE] << SHIFTBYTE(i);
		}
		else
			lol->reg[lol->inv.param[1] - 1] = lol->inv.param[0];
		lol->carry = lol->reg[lol->inv.param[1] - 1] == 0;
	}
	if (!vm->visual)
		ft_printf("P\t%u | lld %d r%d\n",
				lol->pid,
				lol->inv.param[0],
				lol->inv.param[1]);
}

void		lldi(t_corewar *vm, t_proc *p, t_instr *instr)
{
	int	jump;
	int	i;

	if (p->inv.param[2] != 1)
	{
		if (p->inv.val_arg[0] == 4)
		{
			jump = (p->inv.save_pc + ((short)p->inv.param[0] % IDX_MOD));
			i = -1;
			p->inv.param[0] = 0;
			while (++i < 4)
				p->inv.param[0] |=
					vm->arena[((uint32_t)jump + i) % MEM_SIZE] << SHIFTBYTE(i);
		}
		jump = (p->inv.save_pc + reg_test(p, instr, 0) + reg_test(p, instr, 1));
		p->reg[p->inv.param[2] - 1] = 0;
		i = -1;
		while (++i < 4)
		{
			p->reg[p->inv.param[2] - 1] |=
				vm->arena[(jump + i) % MEM_SIZE] << SHIFTBYTE(i);
		}
		p->carry = p->reg[p->inv.param[2] - 1] == 0;
	}
	text_output_instr(vm, "lldi", p);
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
	ft_memcpy(child, lol, sizeof(*lol));
	child->pc = (lol->inv.save_pc + (short)lol->inv.param[0]) % MEM_SIZE;
	init_child(vm, child, instr);
	if (vm->visual == 1)
		fork_update_window(lol, vm);
	if (!vm->visual)
		ft_printf("P\t%u | lfork %d (%d)\n",
				lol->pid,
				lol->inv.param[0],
				(lol->inv.save_pc + (lol->inv.param[0] % IDX_MOD)) % MEM_SIZE);
}
