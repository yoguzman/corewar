/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:59:05 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/14 18:50:09 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libft.h"

void	ft_and(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		reg_test(lol, instr, 0) & reg_test(lol, instr, 1);
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
	if (!vm->visual)
		ft_printf("P\t%u | and %.*s%d %.*s%d r%d\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2]);
}

void	ft_or(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		reg_test(lol, instr, 0) | reg_test(lol, instr, 1);
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
	if (!vm->visual)
		ft_printf("P\t%u | or %.*s%d %.*s%d r%d\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2]);
}

void	ft_xor(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		reg_test(lol, instr, 0) ^ reg_test(lol, instr, 1);
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
	if (!vm->visual)
		ft_printf("P\t%u | xor %.*s%d %.*s%d r%d\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2]);
}

void	add(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		lol->reg[instr->param[0] - 1] + lol->reg[instr->param[1] - 1];
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
	if (!vm->visual)
		ft_printf("P\t%u | add %.*s%d %.*s%d r%d\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2]);
}

void	sub(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		lol->reg[instr->param[0] - 1] - lol->reg[instr->param[1] - 1];
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
	if (!vm->visual)
		ft_printf("P\t%u | sub %.*s%d %.*s%d r%d\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2]);
}
