/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:44:10 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/13 17:04:18 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libft.h"

void	live(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	uint32_t	player_nb;

	player_nb = -1U - instr->param[0].i + 1;
	if (player_nb <= MAX_PLAYERS)
	{
		++vm->player_table[player_nb - 1].current_live;
		if (vm->visual == 1)
			;
	}
	++lol->current_live;
	if (!vm->visual)
		printf("P\t%u | live %lld\n", lol->pid, instr->param[0]);
}

void	ld(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;

	if (instr->val_arg[0] == T_DIR)
		lol->reg[instr->param[1].i - 1] = instr->param[0].i;
	else
	{
		offset = (instr->save_pc + (instr->param[0].si % IDX_MOD)) % MEM_SIZE;
		lol->reg[instr->param[1].i - 1] = vm->arena[offset];
		offset = (offset + 1) % MEM_SIZE;
		lol->reg[instr->param[1].i - 1] |= vm->arena[offset] << 8;
		offset = (offset + 1) % MEM_SIZE;
		lol->reg[instr->param[1].i - 1] |= vm->arena[offset] << 16;
		offset = (offset + 1) % MEM_SIZE;
		lol->reg[instr->param[1].i - 1] |= vm->arena[offset] << 24;
	}
	lol->carry = lol->reg[instr->param[1] - 1] == 0;
	if (!vm->visual)
		printf("P\t%u | ld %.*s%lld r%lld carry = %d r = %ud\n", lol->pid,
				(instr->val_arg[0] == T_DIR ? 1 : 0), "%", instr->param[0],
				instr->param[1], lol->carry, lol->reg[instr->param[1] - 1]);
}

void	st(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;

	if (instr->val_arg[1] == T_REG)
		lol->reg[instr->param[1] - 1] = lol->reg[instr->param[0].i - 1];
	else
	{
		attron(COLOR_PAIR(lol->reg[0] + 2));
		offset = (instr->save_pc + (instr->param[1] % IDX_MOD)) % MEM_SIZE;
		vm->arena[offset] =
			((char)(lol->reg[instr->param[0] - 1] & 0xFF000000) >> 24);
		mvprintw((offset / 64) + 2, (offset % 64) * 3 + 3, "%.2x",
				vm->arena[offset]);
		offset = (offset + 1) % MEM_SIZE;
		vm->arena[offset] =
			((char)(lol->reg[instr->param[0] - 1] & 0xFF0000) >> 16);
		mvprintw((offset / 64) + 2, (offset % 64) * 3 + 3, "%.2x",
				vm->arena[offset]);
		offset = (offset + 1) % MEM_SIZE;
		vm->arena[offset] =
			((char)(lol->reg[instr->param[0] - 1] & 0xFF00) >> 8);
		mvprintw((offset / 64) + 2, (offset % 64) * 3 + 3, "%.2x",
				vm->arena[offset]);
		offset = (offset + 1) % MEM_SIZE;
		vm->arena[offset] =
			((char)(lol->reg[instr->param[0] - 1] & 0xFF));
		mvprintw((offset / 64) + 2, (offset % 64) * 3 + 3, "%.2x",
				vm->arena[offset]);
		attroff(COLOR_PAIR(lol->reg[0] + 2));
	}
	lol->carry = lol->reg[instr->param[0] - 1] == 0;
	if (!vm->visual)
		printf("P\t%u | st r%lld %.*s%lld\n", lol->pid, instr->param[0],
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[1]);
}

void	add(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		lol->reg[instr->param[0] - 1] + lol->reg[instr->param[1] - 1];
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
	if (!vm->visual)
		printf("P\t%u | add %.*s%lld %.*s%lld r%lld\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2]);
}

void	sub(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		lol->reg[instr->param[0] - 1] - lol->reg[instr->param[1] - 1];
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
	if (!vm->visual)
		printf("P\t%u | sub %.*s%lld %.*s%lld r%lld\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2]);
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
	if (!vm->visual)
		printf("P\t%u | and %.*s%lld %.*s%lld r%lld\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2]);
}

void	ft_or(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		reg_test(lol, instr, 0) | reg_test(lol, instr, 1);
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
	if (!vm->visual)
		printf("P\t%u | or %.*s%lld %.*s%lld r%lld\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2]);
}

void	ft_xor(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	lol->reg[instr->param[2] - 1] =
		reg_test(lol, instr, 0) ^ reg_test(lol, instr, 1);
	lol->carry = lol->reg[instr->param[2] - 1] == 0;
	if (!vm->visual)
		printf("P\t%u | xor %.*s%lld %.*s%lld r%lld\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2]);
}

void	zjmp(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	if (lol->carry == 1)
	{
		//		lol->pc = lol->pc + (instr->param[0] % IDX_MOD);
		lol->pc = (instr->save_pc + (instr->param[0] % IDX_MOD)) % MEM_SIZE;
	}
	if (!vm->visual)
		printf("P\t%u | zjmp %lld (%s)\n", lol->pid, instr->param[0],
				(lol->carry == 1 ? "OK" : "FAILED"));
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
	if (!vm->visual)
		printf("P\t%u | ldi %.*s%lld %.*s%lld r%lld valeurs %d\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2], offset);
}

void	sti(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int to_jump;

	to_jump = reg_test(lol, instr, 1);
	to_jump += reg_test(lol, instr, 2);
	to_jump = (instr->save_pc + (to_jump % IDX_MOD)) % MEM_SIZE;
	attron(COLOR_PAIR(lol->reg[0] + 2));
	vm->arena[to_jump] =
		((char)(lol->reg[instr->param[0] - 1] & 0xFF000000) >> 24);
	mvprintw((to_jump / 64) + 2, (to_jump % 64) * 3 + 3, "%.2x",
			vm->arena[to_jump]);
	to_jump = (to_jump + 1) % MEM_SIZE;
	vm->arena[to_jump] =
		((char)(lol->reg[instr->param[0] - 1] & 0x00FF0000) >> 16);
	mvprintw((to_jump / 64) + 2, (to_jump % 64) * 3 + 3, "%.2x",
			vm->arena[to_jump]);
	to_jump = (to_jump + 1) % MEM_SIZE;
	vm->arena[to_jump] =
		((char)(lol->reg[instr->param[0] - 1] & 0x0000FF00) >> 8);
	mvprintw((to_jump / 64) + 2, (to_jump % 64) * 3 + 3, "%.2x",
			vm->arena[to_jump]);
	to_jump = (to_jump + 1) % MEM_SIZE;
	vm->arena[to_jump] =
		((char)(lol->reg[instr->param[0] - 1] & 0x000000FF));
	mvprintw((to_jump / 64) + 2, (to_jump % 64) * 3 + 3, "%.2x",
			vm->arena[to_jump]);
	attroff(COLOR_PAIR(lol->reg[0] + 2));
	lol->carry = lol->reg[instr->param[0] - 1] == 0;
	if (!vm->visual)
		printf("P\t%u | sti r%lld %.*s%lld %.*s%lld\n", lol->pid, instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				(instr->val_arg[2] == T_REG ? 1 : 0), "r", instr->param[2]);
}

void	ft_fork(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	t_proc	*child;
	if (!(child = (t_proc *)malloc(sizeof(*child))))

		exit(EXIT_FAILURE);
	//	if (!(child = spawn_process(instr->save_pc + (instr->param[0] % IDX_MOD) % MEM_SIZE, lol->reg[0], &(vm->total_proc))))
	//		exit(EXIT_FAILURE);
	ft_memcpy(child, lol, sizeof(*lol));
	child->pc = (instr->save_pc + (instr->param[0] % IDX_MOD)) % MEM_SIZE;
	child->pid = vm->total_proc++;
	child->cycles_to_exec = vm->cycle_count + 1;
	if ((vm->arena[child->pc] - 1) <= 15 && vm->arena[child->pc] - 1 >= 0)
		child->cycles_to_exec =
			instr->op_tab[vm->arena[child->pc] - 1].cycles_to_exec
			+ vm->cycle_count;
	insert(vm->mh, child);
	++vm->nb_processes;
	if (vm->visual == 1)
	{
		attron(COLOR_PAIR(lol->reg[0] + 2 + 5));
		mvprintw((child->pc / 64) + 2, (child->pc % 64) * 3 + 3, "%.2x",
				vm->arena[child->pc]);
		attroff(COLOR_PAIR(lol->reg[0] + 2 + 5));
		attron(COLOR_PAIR(6));
		mvprintw(9, 199 + 12, "%d", vm->nb_processes);
		attroff(COLOR_PAIR(6));
	}
	if (!vm->visual)
		printf("P\t%u | fork %lld (%lld) cycle_to_exec = %d pid = %u, pc = %u case = %d\n", lol->pid, instr->param[0],
				(instr->save_pc + (instr->param[0] % IDX_MOD)) % MEM_SIZE, child->cycles_to_exec, child->pid, child->pc, vm->arena[child->pc] - 1);
}

void	lld(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	int	offset;

	if (instr->val_arg[0] == T_IND)
	{
		offset = (instr->save_pc + instr->param[0]) % MEM_SIZE;
		lol->reg[instr->param[1] - 1] = vm->arena[offset] << 24;
		offset = (offset + 1) % MEM_SIZE;
		lol->reg[instr->param[1] - 1] |= vm->arena[offset] << 16;
		offset = (offset + 1) % MEM_SIZE;
		lol->reg[instr->param[1] - 1] |= vm->arena[offset] << 8;
		offset = (offset + 1) % MEM_SIZE;
		lol->reg[instr->param[1] - 1] |= vm->arena[offset];
	}
	else
		lol->reg[instr->param[1] - 1] = instr->param[0];
	lol->carry = lol->reg[instr->param[1] - 1] == 0;
	if (!vm->visual)
		printf("P\t%u | lld %.*s%lld r%lld\n", lol->pid,
				(instr->val_arg[0] == T_DIR ? 1 : 0), "%", instr->param[0],
				instr->param[1]);

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
	if (!vm->visual)
		printf("P\t%u | lldi %.*s%lld %.*s%lld r%lld\n", lol->pid,
				(instr->val_arg[0] == T_REG ? 1 : 0), "r", instr->param[0],
				(instr->val_arg[1] == T_REG ? 1 : 0), "r", instr->param[1],
				instr->param[2]);
}

void	ft_lfork(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	t_proc	*child;

	if (!(child = (t_proc *)malloc(sizeof(*child))))
		exit(EXIT_FAILURE);
	//	if (!(child = spawn_process((instr->save_pc + instr->param[0]) % MEM_SIZE, lol->reg[0], &(vm->total_proc))))
	//		exit(EXIT_FAILURE);
	ft_memcpy(child, lol, sizeof(*lol));
	child->pc = (instr->save_pc + instr->param[0]) % MEM_SIZE;
	child->pid = vm->total_proc++;
	child->cycles_to_exec = vm->cycle_count + 1;
	if ((vm->arena[child->pc] - 1) <= 15)
		child->cycles_to_exec =
			instr->op_tab[vm->arena[child->pc - 1]].cycles_to_exec
			+ vm->cycle_count;
	insert(vm->mh, child);
	++vm->nb_processes;
	if (vm->visual == 1)
	{
		attron(COLOR_PAIR(lol->reg[0] + 2 + 5));
		mvprintw((lol->pc / 64) + 2, (lol->pc % 64) * 3 + 3, "%.2x",
				vm->arena[lol->pc]);
		attroff(COLOR_PAIR(lol->reg[0] + 2 + 5));
		attron(COLOR_PAIR(6));
		mvprintw(9, 199 + 12, "%d", vm->nb_processes);
		attroff(COLOR_PAIR(6));
	}
	if (!vm->visual)
		printf("P\t%u | lfork %lld (%lld)\n", lol->pid, instr->param[0],
				(instr->save_pc + (instr->param[0] % IDX_MOD)) % MEM_SIZE);
}

void	aff(t_corewar *vm, t_proc *lol, t_instr *instr)
{
	(void)vm;
	ft_putchar(lol->reg[instr->param[0] - 1] % 256);
	if (!vm->visual)
		printf("P\t%u | aff r%lld (%c)\n", lol->pid, instr->param[0],
				lol->reg[instr->param[0] - 1] % 256);
}

int	check_params(unsigned char const parameter_type[3],
		unsigned char parameter_count, int *val_arg)
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
	while (i < instr->op_tab[instr->opcode].parameter_count)
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
	int	ret;

	ret = 0;
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
			ret = get_data(vm, proc, instr);
		else
			get_one_arg(vm, proc, instr);
		if (ret != -1)
			instr->tab_instr[instr->opcode](vm, proc, instr);
		//		printf("%s > GOOD\n", instr->op_tab[instr->opcode].name);
	}
	instr->opcode = vm->arena[proc->pc] - 1;
	if (instr->opcode <= 15)
	{
		proc->cycles_to_exec = instr->op_tab[instr->opcode].cycles_to_exec
			+ vm->cycle_count;
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
