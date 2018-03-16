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

int		get_octet(char octet, t_inv *inv, t_instr *instr)
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
		inv->val_arg[i] = ret;
		i--;
	}
	if (check_params(instr->op_tab[inv->opcode].parameter_types,
				instr->op_tab[inv->opcode].parameter_count,
				inv->val_arg) == -1)
		return (-1);
	return (0);
}

void	la_balade(t_proc *lol, t_instr *instr, t_inv *inv)
{
	int tojump;
	int i;

	i = 0;
	while (i < instr->op_tab[inv->opcode].parameter_count)
	{
		tojump = 0;
		if (inv->val_arg[i] == T_REG)
			tojump = 1;
		else if (inv->val_arg[i] == T_DIR)
			tojump = (instr->op_tab[inv->opcode].uses_index == 1 ? 2 : 4);
		else if (inv->val_arg[i] == T_IND)
			tojump = 2;
		lol->pc += tojump;
		i++;
	}
	lol->pc += 1;
}

void	fill_ins_proc(t_corewar *vm, t_instr *ins, t_proc *proc)
{
	proc->inv.opcode = vm->arena[proc->pc] - 1;
	proc->inv.save_pc = proc->pc;
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	if (proc->inv.opcode <= 15)
		proc->cycles_to_exec = ins->op_tab[proc->inv.opcode].cycles_to_exec
			+ vm->cycle_count;
	else
		proc->cycles_to_exec += 1;
}

void	exec_instr(t_corewar *vm, t_instr *ins, t_proc *proc)
{
	if (vm->visual == 1)
		exec_instr_update_window(proc, vm, 2, proc->inv.save_pc);
	proc->inv.ret = 0;
	if (proc->inv.opcode <= 15)
	{
		if (ins->op_tab[proc->inv.opcode].parameter_count != 1 || proc->inv.opcode == 15)
			proc->inv.ret = get_data(vm, proc, &(proc->inv), ins);
		else
			proc->inv.ret = get_one_arg(vm, proc, &(proc->inv));
	}
	if (proc->inv.opcode <= 15 && proc->inv.ret == 0)
		ins->tab_instr[proc->inv.opcode](vm, proc, ins);
	if (vm->visual == 1)
		exec_instr_update_window(proc, vm, 7, proc->pc);
	fill_ins_proc(vm, ins, proc);
}
