/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_st_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:25:36 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/28 10:01:41 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libft.h"

void		ld(t_corewar *vm, t_proc *p, t_instr *instr)
{
	int	jump;
	int	i;

	(void)instr;
	if (p->inv.param[1] != 1)
	{
		if (p->inv.val_arg[0] == T_DIR)
			p->reg[p->inv.param[1] - 1] = p->inv.param[0];
		else
		{
			jump = (p->inv.save_pc + ((short)p->inv.param[0] % IDX_MOD));
			i = -1;
			p->reg[p->inv.param[1] - 1] = 0;
			while (++i < 4)
				p->reg[p->inv.param[1] - 1] |=
					vm->arena[((uint32_t)jump + i) % MEM_SIZE] << SHIFTBYTE(i);
		}
		p->carry = p->reg[p->inv.param[1] - 1] == 0;
	}
	if (!vm->visual)
		ft_printf("P%5u | ld %d r%d\n",
				p->pid,
				p->reg[p->inv.param[1] - 1],
				p->inv.param[1]);
}

void		ldi(t_corewar *vm, t_proc *p, t_instr *instr)
{
	int	jump;
	int	i;

	if (p->inv.val_arg[0] == T_IND)
	{
		jump = (p->inv.save_pc + ((short)p->inv.param[0] % IDX_MOD));
		i = -1;
		p->inv.param[0] = 0;
		while (++i < 4)
		{
			p->inv.param[0] +=
				vm->arena[((uint32_t)jump + i) % MEM_SIZE] << SHIFTBYTE(i);
		}
	}
	if (p->inv.param[2] != 1)
	{
		jump = p->inv.save_pc
			+ ((reg_test(p, instr, 0) + reg_test(p, instr, 1)) % IDX_MOD);
		i = -1;
		p->reg[p->inv.param[2] - 1] = 0;
		while (++i < 4)
			p->reg[p->inv.param[2] - 1] |=
				vm->arena[((uint32_t)jump + i) % MEM_SIZE] << SHIFTBYTE(i);
	}
	ldi_text_output(vm, p, jump);
}

void		st(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;
	int	i;

	(void)instr;
	if (lol->inv.val_arg[1] == T_REG && lol->inv.param[1] != 1)
		lol->reg[lol->inv.param[1] - 1] = lol->reg[lol->inv.param[0] - 1];
	else
	{
		i = -1;
		offset = (lol->inv.save_pc + ((short)lol->inv.param[1] % IDX_MOD));
		while (++i < 4)
		{
			vm->arena[((uint32_t)offset + i) % MEM_SIZE] =
				(lol->reg[lol->inv.param[0] - 1] >> SHIFTBYTE(i)) & 0xFF;
		}
		if (vm->visual == 1)
			print_4b_in_arena((uint32_t)offset % MEM_SIZE, vm->arena, lol, i);
	}
	if (!vm->visual)
		ft_printf("P%5u | st r%d %d\n",
				lol->pid,
				lol->inv.param[0],
				lol->inv.val_arg[1] == T_REG ? lol->reg[lol->inv.param[1] - 1] :
				lol->inv.param[1]);
}

void		sti(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int to_jump;
	int offset;
	int	i;

	if (lol->inv.val_arg[1] == 4)
	{
		offset = (lol->inv.save_pc + ((short)lol->inv.param[1] % IDX_MOD));
		i = -1;
		lol->inv.param[1] = 0;
		while (++i < 4)
		{
			lol->inv.param[1] +=
				vm->arena[((uint32_t)offset + i) % MEM_SIZE] << SHIFTBYTE(i);
		}
	}
	to_jump = reg_test(lol, instr, 1) + reg_test(lol, instr, 2);
	to_jump = (lol->inv.save_pc + ((int)to_jump % IDX_MOD));
	i = -1;
	while (++i < 4)
		vm->arena[((uint32_t)to_jump + i) % MEM_SIZE] =
			(lol->reg[lol->inv.param[0] - 1] >> SHIFTBYTE(i)) & 0xFF;
	if (vm->visual == 1)
		print_4b_in_arena((uint32_t)to_jump % MEM_SIZE, vm->arena, lol, i);
	if (!vm->visual)
		sti_text_output(lol, to_jump);
}
