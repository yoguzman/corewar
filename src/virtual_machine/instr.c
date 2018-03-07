/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:44:10 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/07 19:32:19 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libft.h"

void	live(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	/*
  //depuis le lol-pc - l instruction ?
  if (lol->carry == 1)
    lol->pc = lol->pc + (instr->param[0] % IDX_MOD);
  */
}

void	ld(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	lol->reg[instr->param[1]] += 42;
    lol->carry = 1;
}

void	st(t_corewar *vm, t_proc *lol, t_instr *instr)
{
  /* si param[1] == REG
     lol->reg[instr->param[1]] = lol->reg[instr->param[0]];;
     else
    ecrit a lol->reg[instr->param[0]]; a lol->pcc + instr->pram[1] % IDX MOD
  if (to_load)
  lol->carry = 1 */
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

void	ft_and(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	lol->reg[instr->param[2]] = instr->param[0] & instr->param[1];
	lol->carry = 1;
}

void	ft_or(t_corewar *vm, t_proc *lol, t_instr *instr)
{
  lol->reg[instr->param[2]] = instr->param[0] | instr->param[1];
}

void	ft_xor(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	lol->reg[instr->param[2]] = instr->param[0] ^ instr->param[1];
	lol->carry = 1;

}

void	zjmp(t_corewar *vm, t_proc *lol, t_instr *instr)
{
    if (lol->carry == 1)
        lol->pc = lol->pc + (instr->param[0] % IDX_MOD);
}

void	ldi(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	sti(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int pc = 0;
	int to_jump = 0;

	if (instr->val_arg[1] == T_DIR)
		to_jump += instr->param[1];
	else
		to_jump += lol->reg[instr->param[1]];
	if (instr->val_arg[2] == T_DIR)
		to_jump += instr->param[2];
	else
		to_jump += lol->reg[instr->param[2]];
	pc += to_jump + 14;
	reset_pc(pc);
	vm->arena[pc++] = ((char) (lol->reg[instr->param[0]] & 0xFF000000) >> 24);
	vm->arena[pc++] = ((char) (lol->reg[instr->param[0]] & 0x00FF0000) >> 16);
    vm->arena[pc++] = ((char) (lol->reg[instr->param[0]] & 0x0000FF00) >> 8);
    vm->arena[pc++] = ((char) (lol->reg[instr->param[0]] & 0x000000FF));

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

void	la_balade(t_proc *lol, t_instr *instr)
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
	//ft_putstr("\nCycle actuel = ");
	//ft_putnbr(vm->mh->count);
	//ft_putstr(" id process = ");
	//ft_putnbr(proc->reg[0]);
	//ft_putstr(" code instr = ");
	//ft_putnbr(vm->arena[proc->pc]);
	//ft_putstr(" cycle_to_exec : ");
	//ft_putnbr(proc->cycles_to_exec - vm->mh->count);
	instr->opcode = vm->arena[proc->pc] - 1;
	++(proc->pc); /* proc->pc = (proc->pc + 1) % MEM_SIZE; */
	reset_pc(proc->pc);
	if (instr->opcode <= 15)
	{
		printf("instr = %s\n", instr->op_tab[instr->opcode].name);
		if (instr->op_tab[instr->opcode].parameter_count != 1)
			get_data(vm, proc, instr);
		else
			get_one_arg(vm, proc, instr);
		reset_pc(proc->pc);
		instr->tab_instr[instr->opcode](vm, proc, instr);
		printf("%s > GOOD\n", instr->op_tab[instr->opcode].name);
	}
	instr->opcode = vm->arena[proc->pc] - 1;
	if (instr->opcode <= 15)
	{
		proc->cycles_to_exec = instr->op_tab[instr->opcode].cycles_to_exec + vm->mh->count;
		//	ft_putstr(" nouveau ");
		//ft_putstr(" code instr = ");
		//ft_putnbr(vm->arena[proc->pc]);
		//ft_putstr(" cycle_to_exec : ");
		//ft_putnbr(proc->cycles_to_exec - vm->mh->count);
		//ft_putchar('\n');
	}
	else
		proc->cycles_to_exec += 1;
	++(*i);
}
