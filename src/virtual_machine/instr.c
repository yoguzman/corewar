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

void	zjmp(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	ld(t_corewar *vm, t_proc *lol, t_instr *instr)
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
    {
		printf(">>>>>>>%s\n", instr->op_tab[instr->opcode].name);
		printf("FAIL IN CHECK_PARAMS\n");
		return (-1);
	}
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


void	mabite(t_corewar *vm, t_instr *instr)
{
	t_proc		lol;

	lol.pc = 0;
	instr->opcode = vm->arena[lol.pc] - 1;
	lol.pc++;
	ft_putstr("\nopcode = ");
	ft_putnbr(instr->opcode + 1);
	ft_putchar('\n');
	get_data(vm, &lol, instr);
}
