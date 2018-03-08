/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instr_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:24:23 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/08 13:27:53 by jcoutare         ###   ########.fr       */
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
		if (j != 0)
			instr->param[i] <<= 8;
		instr->param[i] += vm->arena[lol->pc];
		++lol->pc;
		++j;
	}
}

void	get_one_arg(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	instr->val_arg[0] = instr->op_tab[instr->opcode].parameter_types[instr->opcode];
	get_param(vm, lol, instr, 0);
}

int		get_data(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int i = 0;
	unsigned char tamer;

	tamer = replace_cod_oct(vm->arena[lol->pc], instr->opcode);
	if (get_octet(tamer, instr) == -1)
	{
		la_balade(lol, instr);
		return (0);
	}
	lol->pc++;
	while (i < instr->op_tab[instr->opcode].parameter_count)
	{
		get_param(vm, lol, instr, i);
		i++;
	}
	return (0);
}
