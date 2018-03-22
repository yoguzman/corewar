/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:59:05 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/22 19:01:58 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libft.h"

void	ft_and(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	i;
	int	j;
	int	jump;

	j = 0;
	while (j < 2)
	{
		if (lol->inv.val_arg[j] == 4)
		{
			jump = (lol->inv.save_pc + ((short)lol->inv.param[j] % IDX_MOD));
			i = -1;
			lol->inv.param[j] = 0;
			while (++i < 4)
				lol->inv.param[j] |=
					vm->arena[((uint32_t)jump + i) % MEM_SIZE] << SHIFTBYTE(i);
		}
		++j;
	}
	text_output_instr(vm, "and", lol);
	if (lol->inv.param[2] != 1)
	{
		lol->reg[lol->inv.param[2] - 1] =
			reg_test(lol, instr, 0) & reg_test(lol, instr, 1);
	}
	lol->carry = (reg_test(lol, instr, 0) & reg_test(lol, instr, 1)) == 0;
}

void	ft_or(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	j;
	int	i;
	int	jump;

	j = 0;
	while (j < 2)
	{
		if (lol->inv.val_arg[j] == 4)
		{
			jump = (lol->inv.save_pc + ((short)lol->inv.param[j] % IDX_MOD));
			i = -1;
			lol->inv.param[j] = 0;
			while (++i < 4)
				lol->inv.param[j] |=
					vm->arena[((uint32_t)jump + i) % MEM_SIZE] << SHIFTBYTE(i);
		}
		++j;
	}
	text_output_instr(vm, "or", lol);
	if (lol->inv.param[2] != 1)
	{
		lol->reg[lol->inv.param[2] - 1] =
			reg_test(lol, instr, 0) | reg_test(lol, instr, 1);
	}
	lol->carry = (reg_test(lol, instr, 0) & reg_test(lol, instr, 1)) == 0;
}

void	ft_xor(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	j;
	int	i;
	int	jump;

	j = 0;
	while (j < 2)
	{
		if (lol->inv.val_arg[j] == 4)
		{
			jump = (lol->inv.save_pc + ((short)lol->inv.param[j] % IDX_MOD));
			i = -1;
			lol->inv.param[j] = 0;
			while (++i < 4)
				lol->inv.param[j] |=
					vm->arena[((uint32_t)jump + i) % MEM_SIZE] << SHIFTBYTE(i);
		}
		++j;
	}
	text_output_instr(vm, "xor", lol);
	if (lol->inv.param[2] != 1)
	{
		lol->reg[lol->inv.param[2] - 1] =
			reg_test(lol, instr, 0) ^ reg_test(lol, instr, 1);
	}
	lol->carry = (reg_test(lol, instr, 0) & reg_test(lol, instr, 1)) == 0;
}

void	add(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	(void)instr;
	if (lol->inv.param[2] != 1)
	{
		lol->reg[lol->inv.param[2] - 1] =
			lol->reg[lol->inv.param[0] - 1] + lol->reg[lol->inv.param[1] - 1];
	}
	lol->carry = lol->reg[lol->inv.param[0] - 1] -
		lol->reg[lol->inv.param[1] - 1] == 0;
	if (!vm->visual)
		ft_printf("P\t%u | add %d %d r%d\n",
				lol->pid,
				lol->inv.param[0],
				lol->inv.param[1],
				lol->reg[lol->inv.param[2] - 1]);
}

void	sub(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	(void)instr;
	if (lol->inv.param[2] != 1)
	{
		lol->reg[lol->inv.param[2] - 1] =
			lol->reg[lol->inv.param[0] - 1] - lol->reg[lol->inv.param[1] - 1];
		lol->carry = lol->reg[lol->inv.param[2] - 1] == 0;
	}
	lol->carry = lol->reg[lol->inv.param[0] - 1] -
		lol->reg[lol->inv.param[1] - 1] == 0;
	if (!vm->visual)
		ft_printf("P\t%u | sub %d %d r%d\n",
				lol->pid,
				lol->inv.param[0],
				lol->inv.param[1],
				lol->inv.param[2]);
}
