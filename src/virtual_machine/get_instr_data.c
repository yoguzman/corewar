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

void	swap_32(unsigned long long *nb)
{
	unsigned long long	buf1;
	unsigned long long	buf2;

	buf1 = ((*nb & 0xff000000) >> 24) | ((*nb & 0x00ff0000) >> 8);
	buf2 = ((*nb & 0x0000ff00) << 8) | (*nb << 24);
	*nb = buf1 | buf2;
}

void	swap_16(unsigned long long *nb)
{
	*nb = ((*nb & 0xff) >> 8 | (*nb << 8));
}

void	get_param(t_corewar *vm, t_proc *lol, t_instr *instr,
					int i)
{
	int		j;

	j = 0;
	instr->param[i] = 0;
	while (j < instr->val_arg[i])
	{
		instr->param[i] += vm->arena[lol->pc];
		instr->param[i] <<= 8;
		++j;
	}
	if (instr->val_arg[i] == 2)
		swap_16(&(instr->param[i]));
	else if (instr->val_arg[i] == 4)
		swap_32(&(instr->param[i]));
	lol->pc += instr->val_arg[i];
}

void	get_one_arg(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	instr->val_arg[0] = instr->op_tab[instr->opcode].parameter_types[instr->opcode];
	get_param(vm, lol, instr, 0);
}

int		get_data(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int i = 0;

	if (get_octet(vm->arena[lol->pc], instr) == -1)
	{
		la_balade(vm , lol, instr);
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
