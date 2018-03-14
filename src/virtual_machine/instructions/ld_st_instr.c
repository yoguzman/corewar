/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_st_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:25:36 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/14 18:52:36 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libft.h"

void	ld(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;
	int	i;

	if (instr->val_arg[0] == DIR_SIZE)
	{
		lol->reg[instr->param[1] - 1] = instr->param[0];
	}
	else
	{
		offset = (instr->save_pc + (instr->param[0] % IDX_MOD));
		i = -1;
		lol->reg[instr->param[1] - 1] = 0;
		while (++i < 4)
		{
			lol->reg[instr->param[1] - 1] |=
				vm->arena[(offset + i) % MEM_SIZE] << ((3 - i) << 3);
		}
	}
	lol->carry = lol->reg[instr->param[1] - 1] == 0;
	if (!vm->visual)
		ft_printf("P\t%u | ld %.*s%d r%d\n", lol->pid,
				(instr->val_arg[0] == T_DIR ? 1 : 0), "%", instr->param[0],
				instr->param[1]);
}

void	ldi(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;
	int	i;

	offset = instr->save_pc
		+ ((reg_test(lol, instr, 0) + reg_test(lol, instr, 1)) % IDX_MOD);
	i = -1;
	lol->reg[instr->param[2] - 1] = 0;
	while (++i < 4)
	{
		lol->reg[instr->param[2] - 1] |=
			vm->arena[(offset + i) % MEM_SIZE] << ((3 - i) << 3);
	}
	if (!vm->visual)
		ft_printf("P\t%u | ldi %.*s%d %.*s%d r%d\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2]);
}

void	st(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;
	int	i;

	if (instr->val_arg[1] == T_REG)
		lol->reg[instr->param[1] - 1] = lol->reg[instr->param[0] - 1];
	else
	{
		i = -1;
		offset = (instr->save_pc + (instr->param[1] % IDX_MOD));
		while (++i < 4)
		{
			vm->arena[(offset + i) % MEM_SIZE] =
				(lol->reg[instr->param[0] - 1] >> ((3 - i) << 3)) & 0xFF;
		}
		if (vm->visual == 1)
			print_4b_in_arena(offset, vm->arena, lol, i);
	}
	lol->carry = lol->reg[instr->param[0] - 1] == 0;
	if (!vm->visual)
		ft_printf("P\t%u | st r%d %.*s%d\n", lol->pid, instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1]);
}

void	sti(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int to_jump;
	int	i;

	to_jump = reg_test(lol, instr, 1) + reg_test(lol, instr, 2);
	to_jump = (instr->save_pc + (to_jump % IDX_MOD));
	i = -1;
	while (++i < 4)
	{
		vm->arena[(to_jump + i) % MEM_SIZE] =
			(lol->reg[instr->param[0] - 1] >> ((3 - i) << 3)) & 0xFF;
	}
	if (vm->visual == 1)
		print_4b_in_arena(to_jump, vm->arena, lol, i);
	if (!vm->visual)
		ft_printf("P\t%u | sti r%d %.*s%d %.*s%d\n", lol->pid, instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				(instr->val_arg[2] == T_REG ? 1 : 0), "r", instr->param[2]);
}
