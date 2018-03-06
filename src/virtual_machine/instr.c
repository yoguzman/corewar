/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:44:10 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/06 14:53:42 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libft.h"


/* penser a incrementer vm->total_proc a la creation de process, penser a
   incrmenter proc->current_live et player->current_live a chaque live

*/



void	live(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	zjmp(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	//depuis le lol-pc - l instruction ?
	if (lol->carry == 1)
		lol->pc = lol->pc + (instr->param[0] % IDX_MOD);
}


void	sti(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int pc = lol->pc - 1 + instr->param[1] + instr->param[2];
  	vm->arena[pc] = ((char) (instr->param[0] && 0xFF000000) >> 24);
	vm->arena[pc++] = ((char) (instr->param[0] && 0x00FF0000) >> 16);
	vm->arena[pc++] = ((char) (instr->param[0] && 0x0000FF00) >> 8);
	vm->arena[pc++] = ((char) (instr->param[0] && 0x000000FF));
}

void	aff(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	lfork(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	lld(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	lldi(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	ldi(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	st(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	ld(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	lol->reg[instr->param[1]] = instr->param[0];
    lol->carry = 1;
}

void	add(t_corewar *vm, t_proc *lol, t_instr *instr)
{

	lol->reg[instr->param[2]] = lol->reg[instr->param[0]] + lol->reg[instr->param[1]];
    lol->carry = 1;
}


void	sub(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	lol->reg[instr->param[2]] = lol->reg[instr->param[0]] - lol->reg[instr->param[1]];
    lol->carry = 1;
}


void	and(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	lol->reg[instr->param[2]] = instr->param[0] & instr->param[1];
    lol->carry = 1;
}

void	or(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	instr->param[0] | instr->param[1];
	lol->reg[instr->param[2]] = instr->param[0] | instr->param[1];
}

void	xor(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	lol->reg[instr->param[2]] = instr->param[0] ^ instr->param[1];
	lol->carry = 1;
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
	instr->opcode = vm->arena[proc->pc] - 1;
	/*
	ft_putstr("ancien ");
	ft_putstr("id : ");
	ft_putnbr(proc->reg[0]);
	ft_putstr(" ");
	ft_putstr("instr : ");
	ft_putnbr(instr->opcode);
	ft_putstr(" ");
	ft_putstr("cycle exec : ");
	ft_putnbr(proc->cycles_to_exec);
	ft_putstr("\n"); */
	++(proc->pc);
	if (instr->opcode > 15)
	{
		++(*i);
		return ;
	}
	if (instr->op_tab[instr->opcode].parameter_count != 1)
		get_data(vm, proc, instr);
	else
		get_one_arg(vm, proc, instr);
	printf("\nopcode = %d | so instr > %s\n", instr->opcode, instr->op_tab[instr->opcode].name);
	instr->tab_instr[instr->opcode](vm, proc, instr);
	instr->opcode = vm->arena[proc->pc] - 1;
	if (instr->opcode <= 15)
	{
		proc->cycles_to_exec = instr->op_tab[instr->opcode].cycles_to_exec + vm->mh->count;
		heapify(vm->mh, *i);
	}
/*	ft_putstr("nouveau ");
	ft_putstr("id : ");
	ft_putnbr(proc->reg[0]);
	ft_putstr(" ");
	ft_putstr("instr : ");
	ft_putnbr(instr->opcode);
	ft_putstr(" ");
	ft_putstr("cycle exec : ");
	ft_putnbr(proc->cycles_to_exec);
	ft_putstr("\n"); */
	++(*i);
}
