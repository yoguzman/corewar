/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:44:10 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/02 19:19:56 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libft.h"

void	live(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	ld(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	st(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	add(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	sub(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	ft_and(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	ft_or(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	ft_xor(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	zjmp(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	ldi(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	sti(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	ft_fork(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	lld(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	lldi(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	ft_lfork(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	aff(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

int	check_params(unsigned char const parameter_type[3], unsigned char parameter_count,
				 int *val_arg)
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
	char mask;
	int ret;
	int i;

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
					 instr->op_tab[instr->opcode].parameter_count, instr->val_arg) == -1)
		return (-1);
	return (0);
}

void	la_balade(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int tojump;
	int i;

	tojump = 0;
	i = 0;
	while (i < 3)
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


void	exec_instr(t_corewar *vm, t_instr *instr, t_proc *proc, uint64_t *i)
{
	ft_putstr("\nCycle actuel = ");
	ft_putnbr(vm->mh->count);
	ft_putstr(" id process = ");
	ft_putnbr(proc->reg[0]);
	ft_putstr(" code instr = ");
	ft_putnbr(vm->arena[proc->pc]);
	ft_putstr(" cycle_to_exec : ");
	ft_putnbr(proc->cycles_to_exec - vm->mh->count);

	instr->opcode = vm->arena[proc->pc] - 1;
	++(proc->pc);
	if (instr->opcode > 15)
	{
		++(*i);
		++(proc->cycles_to_exec);
		return ;
	}
	if (instr->op_tab[instr->opcode].parameter_count != 1)
		get_data(vm, proc, instr);
	else
		get_one_arg(vm, proc, instr);
	instr->tab_instr[instr->opcode](vm, proc, instr);
	instr->opcode = vm->arena[proc->pc] - 1;
	if (instr->opcode <= 15)
	{
		proc->cycles_to_exec = instr->op_tab[instr->opcode].cycles_to_exec + vm->mh->count;
	ft_putstr(" nouveau ");
	ft_putstr(" code instr = ");
	ft_putnbr(vm->arena[proc->pc]);
	ft_putstr(" cycle_to_exec : ");
	ft_putnbr(proc->cycles_to_exec - vm->mh->count);
		heapify(vm->mh, *i);
	}
	++(*i);
}
