/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instr_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:24:23 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/02 19:25:12 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libft.h"

void	get_reg(t_corewar *vm, t_proc *lol, t_instr *instr,
				int i)
{
	instr->param[i] = vm->arena[lol->pc];
	lol->pc += T_REG;
}

void	get_ind(t_corewar *vm, t_proc *lol, t_instr *instr, int i)
{
	//TOFILL
	lol->pc += IND_SIZE;
}

void	get_dir(t_corewar *vm, t_proc *lol, t_instr *instr, int i)
{
// KOMEN ON FE
	lol->pc += DIR_SIZE;
}

int		get_data(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int i = 0;

	if (get_octet(vm->arena[lol->pc], instr) == -1)
	{
		la_balade(vm , lol, instr);
		return (0);
	}
	lol->pc++; //PCK ON A RECUP LOCTET DE CODAGE
	while (i < instr->op_tab[instr->opcode].parameter_count)
	{
		if (instr->val_arg[i] == T_REG)
			get_reg(vm, lol, instr, i);
		else if (instr->val_arg[i] == T_DIR)
			get_dir(vm, lol, instr, i);
		else if (instr->val_arg[i] == T_IND)
			get_ind(vm, lol, instr, i);
		i++;
	}
	instr->tab_instr[instr->opcode](vm, lol, instr);
	return (0);
}
