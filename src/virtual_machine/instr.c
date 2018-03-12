/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:44:10 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/09 19:43:20 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libft.h"

void	live(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	if (instr->param[0] < MAX_PLAYERS)
	{
		++vm->player_table[instr->param[0]].current_live;
		if (vm->visual == 1)
			;
	}
	++lol->current_live;
}

void	ld(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;

	offset = (instr->save_pc + (instr->param[0] % IDX_MOD)) % MEM_SIZE;
	lol->reg[instr->param[1] - 1] = vm->arena[offset] << 24;
	offset = (offset + 1) % MEM_SIZE;
	lol->reg[instr->param[1] - 1] |= vm->arena[offset] << 16;
	offset = (offset + 1) % MEM_SIZE;
	lol->reg[instr->param[1] - 1] |= vm->arena[offset] << 8;
	offset = (offset + 1) % MEM_SIZE;
	lol->reg[instr->param[1] - 1] |= vm->arena[offset];
    lol->carry = lol->reg[instr->param[1] - 1] == 0;
}

void	st(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;

	if (instr->val_arg[1] == T_REG)
		lol->reg[instr->param[1] - 1] = lol->reg[instr->param[0] - 1];
	else
	{
		offset = (instr->save_pc + (instr->param[1] % IDX_MOD)) % MEM_SIZE;
		vm->arena[offset] =
			((char)(lol->reg[instr->param[0] - 1] & 0xFF000000) >> 24);
		offset = (offset + 1) % MEM_SIZE;
		vm->arena[offset] =
			((char)(lol->reg[instr->param[0] - 1] & 0xFF0000) >> 16);
		offset = (offset + 1) % MEM_SIZE;
		vm->arena[offset] =
			((char)(lol->reg[instr->param[0] - 1] & 0xFF00) >> 8);
		offset = (offset + 1) % MEM_SIZE;
		vm->arena[offset] =
			((char)(lol->reg[instr->param[0] - 1] & 0xFF));
	}
}

void	add(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		lol->reg[instr->param[0] - 1] + lol->reg[instr->param[1] - 1];
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
}

void	sub(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		lol->reg[instr->param[0] - 1] - lol->reg[instr->param[1] - 1];
    lol->carry = lol->reg[instr->param[2] - 1] == 0;
}

int		reg_test(t_proc *lol, t_instr *instr, uint8_t i)
{
	return (instr->val_arg[i] == T_REG ?
			lol->reg[instr->param[i] - 1] : instr->param[i]);
}

void	ft_and(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		reg_test(lol, instr, 0) & reg_test(lol, instr, 1);
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
}

void	ft_or(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		reg_test(lol, instr, 0) | reg_test(lol, instr, 1);
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
}

void	ft_xor(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		reg_test(lol, instr, 0) ^ reg_test(lol, instr, 1);
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
}

void	zjmp(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
    if (lol->carry == 1)
        lol->pc = lol->pc + (instr->param[0] % IDX_MOD);
}

void	ldi(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;

	offset = (instr->save_pc
		+ ((reg_test(lol, instr, 0) + reg_test(lol, instr, 1)) % IDX_MOD))
		% MEM_SIZE;
	lol->reg[instr->param[2] - 1] = vm->arena[offset] << 24;
	offset = (offset + 1) % MEM_SIZE;
	lol->reg[instr->param[2] - 1] |= vm->arena[offset] << 16;
	offset = (offset + 1) % MEM_SIZE;
	lol->reg[instr->param[2] - 1] |= vm->arena[offset] << 8;
	offset = (offset + 1) % MEM_SIZE;
	lol->reg[instr->param[2] - 1] |= vm->arena[offset];
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
}

void	sti(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int to_jump;
	
	to_jump = reg_test(lol, instr, 1);
	to_jump += reg_test(lol, instr, 2);
	to_jump = (instr->save_pc + (to_jump % IDX_MOD)) % MEM_SIZE;
	vm->arena[to_jump] =
		((char)(lol->reg[instr->param[0] - 1] & 0xFF000000) >> 24);
	to_jump = (to_jump + 1) % MEM_SIZE;
	vm->arena[to_jump] =
		((char)(lol->reg[instr->param[0] - 1] & 0x00FF0000) >> 16);
	to_jump = (to_jump + 1) % MEM_SIZE;
	vm->arena[to_jump] =
		((char)(lol->reg[instr->param[0] - 1] & 0x0000FF00) >> 8);
	to_jump = (to_jump + 1) % MEM_SIZE;
	vm->arena[to_jump] =
		((char)(lol->reg[instr->param[0] - 1] & 0x000000FF));
}

void	ft_fork(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	t_proc	*child;

	if (!(child = spawn_process(instr->save_pc + (instr->param[0] % IDX_MOD) % MEM_SIZE, lol->reg[0], &(vm->total_proc))))
		exit(EXIT_FAILURE);
	child->cycles_to_exec = vm->cycle_count + 1;
	if ((vm->arena[child->pc] - 1) <= 15)
		child->cycles_to_exec = instr->op_tab[vm->arena[child->pc - 1]].cycles_to_exec + vm->cycle_count;
	insert(vm->mh, child);
	if (vm->visual == 1)
	{
		attron(COLOR_PAIR(lol->reg[0] + 2 + 5));
		mvprintw((child->pc / 64) + 2, (child->pc % 64) * 3 + 3, "%.2x", vm->arena[child->pc]);
		attroff(COLOR_PAIR(lol->reg[0] + 2 + 5));
		attron(COLOR_PAIR(6));
		mvprintw(9, 199 + 12, "%d", vm->total_proc);
		attroff(COLOR_PAIR(6));
	}
}

void	lld(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;

	offset = (instr->save_pc + instr->param[0]) % MEM_SIZE;
	lol->reg[instr->param[1] - 1] = vm->arena[offset] << 24;
	offset = (offset + 1) % MEM_SIZE;
	lol->reg[instr->param[1] - 1] |= vm->arena[offset] << 16;
	offset = (offset + 1) % MEM_SIZE;
	lol->reg[instr->param[1] - 1] |= vm->arena[offset] << 8;
	offset = (offset + 1) % MEM_SIZE;
	lol->reg[instr->param[1] - 1] |= vm->arena[offset];
	lol->carry = lol->reg[instr->param[2] - 1] == 0;

}

void	lldi(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;

	offset = (instr->save_pc + reg_test(lol, instr, 0)
			+ reg_test(lol, instr, 1)) % MEM_SIZE;
	lol->reg[instr->param[2] - 1] = vm->arena[offset] << 24;
	offset = (offset + 1) % MEM_SIZE;
	lol->reg[instr->param[2] - 1] |= vm->arena[offset] << 16;
	offset = (offset + 1) % MEM_SIZE;
	lol->reg[instr->param[2] - 1] |= vm->arena[offset] << 8;
	offset = (offset + 1) % MEM_SIZE;
	lol->reg[instr->param[2] - 1] |= vm->arena[offset];
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
}

void	ft_lfork(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	t_proc	*child;

	if (!(child = spawn_process((instr->save_pc + instr->param[0]) % MEM_SIZE, lol->reg[0], &(vm->total_proc))))
		exit(EXIT_FAILURE);
	child->cycles_to_exec = vm->cycle_count + 1;
	if ((vm->arena[child->pc] - 1) <= 15)
		child->cycles_to_exec = instr->op_tab[vm->arena[child->pc - 1]].cycles_to_exec + vm->cycle_count;
	insert(vm->mh, child);
	if (vm->visual == 1)
	{
		attron(COLOR_PAIR(lol->reg[0] + 2 + 5));
		mvprintw((lol->pc / 64) + 2, (lol->pc % 64) * 3 + 3, "%.2x", vm->arena[lol->pc]);
		attroff(COLOR_PAIR(lol->reg[0] + 2 + 5));
		attron(COLOR_PAIR(6));
		mvprintw(9, 199 + 12, "%d", vm->total_proc);
		attroff(COLOR_PAIR(6));
	}
}

void	aff(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	ft_putchar(lol->reg[instr->param[0] - 1] % 256);
}

int	check_params(unsigned char const parameter_type[3],
		unsigned char parameter_count, int *val_arg)
{
	int i;

	i = 0;
	while (i < parameter_count)
	{
		if ((parameter_type[i] | val_arg[i]) == 0)
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
				instr->op_tab[instr->opcode].parameter_count,
				instr->val_arg) == -1)
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

void	exec_instr(t_corewar *vm, t_instr *instr, t_proc *proc)
{
	//	ft_putstr("\nCycle actuel = ");
	//	ft_putnbr(vm->mh->count);
	//	ft_putstr(" id process = ");
	//	ft_putnbr(proc->reg[0]);
	//	ft_putstr(" code instr = ");
	//	ft_putnbr(vm->arena[proc->pc]);
	//	ft_putstr(" cycle_to_exec : ");
	//	ft_putnbr(proc->cycles_to_exec - vm->mh->count);

	if (vm->visual == 1)
	{
		attron(COLOR_PAIR(proc->reg[0] + 2));
		mvprintw((proc->pc / 64) + 2, (proc->pc % 64) * 3 + 3, "%.2x", vm->arena[proc->pc]);
		attroff(COLOR_PAIR(proc->reg[0] + 2));
	}

	instr->opcode = vm->arena[proc->pc] - 1;
	instr->save_pc = proc->pc;
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	if (instr->opcode <= 15)
	{
		//		printf("P\t%u | %s\n", proc->pid, instr->op_tab[instr->opcode].name);
		if (instr->op_tab[instr->opcode].parameter_count != 1 || instr->opcode == 15)
			get_data(vm, proc, instr);
		else
			get_one_arg(vm, proc, instr);
		instr->tab_instr[instr->opcode](vm, proc, instr);
		//		printf("%s > GOOD\n", instr->op_tab[instr->opcode].name);
	}
	instr->opcode = vm->arena[proc->pc] - 1;
	if (instr->opcode <= 15)
	{
		proc->cycles_to_exec = instr->op_tab[instr->opcode].cycles_to_exec
			+ vm->cycle_count;
//			ft_putstr(" nouveau ");
//		ft_putstr(" code instr = ");
//		ft_putnbr(vm->arena[proc->pc]);
//		ft_putstr(" cycle_to_exec : ");
//		ft_putnbr(proc->cycles_to_exec - vm->mh->count);
//		ft_putchar('\n');
	}
	else
		proc->cycles_to_exec += 1;

	if (vm->visual == 1)
	{
		attron(COLOR_PAIR(proc->reg[0] + 2 + 5));
		mvprintw((proc->pc / 64) + 2, (proc->pc % 64) * 3 + 3, "%.2x", vm->arena[proc->pc]);
		attroff(COLOR_PAIR(proc->reg[0] + 2 + 5));
	}
}
