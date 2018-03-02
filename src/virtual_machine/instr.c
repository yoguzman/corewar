/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:44:10 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/02 19:09:18 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libft.h"
static const  t_op op_tab[17] =  {
        {"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
        {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
        {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
        {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
        {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
        {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
                "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
        {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
                "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
        {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
                "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
        {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
        {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
                "load index", 1, 1},
        {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
                "store index", 1, 1},
        {"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
        {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
        {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
                "long load index", 1, 1},
        {"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
        {"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
        {0, 0, {0}, 0, 0, 0, 0, 0}
};

void	zjmp(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	ld(t_corewar *vm, t_proc *lol, t_instr *instr)
{

}

void	init_tab_instr(void (*tab_instr[16])(t_corewar *vm,
											 t_proc *lol, t_instr *instr))
{
//	tab_instr[0] = &live;
	tab_instr[1] = &ld;
	tab_instr[8] = &zjmp;
}


int	check_params(unsigned char *parameter_type, unsigned char parameter_count,
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


void	mabite(t_corewar *vm)
{
	t_proc		lol;
	t_instr		instr;

	init_op_tab(op_tab, &instr);
	ft_putstr("AFHADFGJSDHFGSDJHFGSDJHFV");
	ft_putstr(instr.op_tab[0].name);
	ft_putstr("lol");
	lol.pc = 0;
	init_tab_instr(instr.tab_instr);
	instr.opcode = vm->arena[lol.pc] - 1;
	lol.pc++;
	ft_putstr("\nopcode = ");
	ft_putnbr(instr.opcode + 1);
	ft_putchar('\n');
	//get_data(vm, &lol, &instr);
}
