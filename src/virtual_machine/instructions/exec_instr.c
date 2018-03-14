/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:44:10 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/14 20:13:43 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libft.h"

int		check_params(unsigned char const parameter_type[3],
		unsigned char parameter_count, uint8_t *val_arg)
{
	int i;

	i = 0;
	while (i < parameter_count)
	{
		if ((parameter_type[i] & val_arg[i]) == 0)
			return (-1);
		i++;
	}
	if (i < 2)
		if (val_arg[2] != 0)
			return (-1);
	return (0);
}

int		get_octet(char octet, t_instr *instr)
{
	char	mask;
	int		ret;
	int		i;

	i = 2;
	mask = 3;
	while (i >= 0)
	{
		octet = octet >> 2;
		ret = octet & mask;
		if (ret == 3)
			ret = ret + 1;
		instr->val_arg[i] = ret;
		i--;
	}
	if (check_params(instr->op_tab[instr->opcode].parameter_types,
				instr->op_tab[instr->opcode].parameter_count,
				instr->val_arg) == -1)
		return (-1);
	return (0);
}

void	la_balade(t_proc *lol, t_instr *instr)
{
	int tojump;
	int i;

	tojump = 0;
	i = 0;
	while (i < instr->op_tab[instr->opcode].parameter_count)
	{
		if (instr->val_arg[i] == T_REG)
			lol->pc += T_REG;
		else if (instr->val_arg[i] == T_DIR)
			lol->pc += DIR_SIZE;
		else if (instr->val_arg[i] == T_IND)
			lol->pc += IND_SIZE;
		i++;
	}
	lol->pc++;
}

void	exec_instr(t_corewar *vm, t_instr *ins, t_proc *proc)
{
	int	ret;

	ret = 0;
	if (vm->visual == 1)
		exec_instr_update_window(proc, vm);
	ins->opcode = vm->arena[proc->pc] - 1;
	ins->save_pc = proc->pc;
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	if (ins->opcode <= 15)
	{
		if (ins->op_tab[ins->opcode].parameter_count != 1 || ins->opcode == 15)
			ret = get_data(vm, proc, ins);
		else
			get_one_arg(vm, proc, ins);
		if (ret != -1)
			ins->tab_instr[ins->opcode](vm, proc, ins);
	}
	ins->opcode = vm->arena[proc->pc] - 1;
	if (ins->opcode <= 15)
		proc->cycles_to_exec = ins->op_tab[ins->opcode].cycles_to_exec
			+ vm->cycle_count;
	else
		proc->cycles_to_exec += 1;
	if (vm->visual == 1)
		exec_instr_update_window(proc, vm);
}
