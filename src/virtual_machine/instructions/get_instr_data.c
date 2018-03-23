/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instr_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:24:23 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/23 13:35:18 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libft.h"

int			get_param(t_corewar *vm, t_proc *lol, t_inv *inv,
					int i)
{
	int		j;

	j = 1;
	inv->param[i] = vm->arena[lol->pc];
	lol->pc = (lol->pc + 1) % MEM_SIZE;
	while (j < inv->val_arg[i])
	{
		++j;
		inv->param[i] <<= 8;
		inv->param[i] += vm->arena[lol->pc];
		lol->pc = (lol->pc + 1) % MEM_SIZE;
	}
	if (inv->val_arg[i] == 1 && (inv->param[i] - 1) > 15)
		return (-1);
	if (inv->val_arg[i] == 2)
		inv->param[i] = (int16_t)inv->param[i];
	return (0);
}

int			get_one_arg(t_corewar *vm, t_proc *lol, t_inv *inv)
{
	int		ret;

	if (inv->opcode == 0)
		inv->val_arg[0] = 4;
	else
		inv->val_arg[0] = 2;
	ret = get_param(vm, lol, inv, 0);
	return (ret);
}

int			get_data(t_corewar *vm, t_proc *lol, t_inv *inv, t_instr *ins)
{
	int		i;
	uint8_t tamer;
	int		save;

	save = lol->pc;
	if (get_octet(vm->arena[lol->pc], inv, ins) == -1)
	{
		la_balade(lol, ins, inv);
		return (-1);
	}
	tamer = replace_cod_oct(vm->arena[lol->pc], inv->opcode, ins->op_tab);
	ft_bzero(inv->val_arg, 3);
	get_octet(tamer, inv, ins);
	lol->pc = (lol->pc + 1) % MEM_SIZE;
	i = -1;
	while (++i < ins->op_tab[inv->opcode].parameter_count)
	{
		if (get_param(vm, lol, inv, i) == -1)
			return (-1);
	}
	get_octet(vm->arena[save], inv, ins);
	return (0);
}
