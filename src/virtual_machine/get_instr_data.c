/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instr_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:24:23 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/09 17:52:13 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libft.h"

void	get_param(t_corewar *vm, t_proc *lol, t_instr *instr,
					int i)
{
	int	j;

	j = 0;
	instr->param[i] = 0;
	while (j < instr->val_arg[i])
	{
		instr->param[i] += vm->arena[lol->pc];
		lol->pc = (lol->pc + 1) % MEM_SIZE;
		++j;
		if (j < instr->val_arg[i])
			instr->param[i] <<= 8;
	}
}

void	get_one_arg(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	if (instr->opcode == 0)
		instr->val_arg[0] = 4;
	else
		instr->val_arg[0] = 2;

	get_param(vm, lol, instr, 0);
}

int		get_data(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int i = 0;
	unsigned char tamer;

	if (get_octet(vm->arena[lol->pc], instr) == -1)
	{
		la_balade(lol, instr);
		return (-1);
	}
	tamer = replace_cod_oct(vm->arena[lol->pc], instr->opcode);
	ft_bzero(instr->val_arg, 12);
	get_octet(tamer, instr);
	lol->pc = (lol->pc + 1) % MEM_SIZE;
	while (i < instr->op_tab[instr->opcode].parameter_count)
	{
		get_param(vm, lol, instr, i);
		i++;
	}
	return (0);
}
