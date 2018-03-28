/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:14:05 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/28 14:31:43 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

void		fork_update_window(t_proc *lol, t_corewar *vm)
{
	attron(COLOR_PAIR((-1U - lol->reg[0]) + 2 + 5));
	mvprintw((lol->pc / 64) + 2, (lol->pc % 64) * 3 + 3, "%.2x",
			vm->arena[lol->pc]);
	attroff(COLOR_PAIR((-1U - lol->reg[0]) + 2 + 5));
	attron(COLOR_PAIR(6));
	mvprintw(9, 199 + 12, "%-10d", vm->mh->pos);
	attroff(COLOR_PAIR(6));
}

void		exec_instr_update_window(t_proc *proc, t_corewar *vm, char add,
		int value)
{
	if ((-1U - proc->reg[0]) > 4)
		attron(COLOR_PAIR(1 + (add == 2 ? 0 : 10)));
	else
		attron(COLOR_PAIR((-1U - proc->reg[0]) + add));
	mvprintw((value / 64) + 2, (value % 64) * 3 + 3, "%.2x",
			vm->arena[value]);
	if ((-1U - proc->reg[0]) > 4)
		attron(COLOR_PAIR(1 + (add == 2 ? 0 : 10)));
	else
		attroff(COLOR_PAIR((-1U - proc->reg[0]) + add));
}

void		print_4b_in_arena(uint32_t offset, uint8_t *arena, t_proc *lol,
		int cnt)
{
	attron(COLOR_PAIR((-1U - lol->reg[0]) + 2));
	while (cnt-- > 0)
	{
		mvprintw((offset / 64) + 2, (offset % 64) * 3 + 3, "%.2x",
				arena[offset]);
		offset = (offset + 1) % MEM_SIZE;
	}
	attroff(COLOR_PAIR((-1U - lol->reg[0]) + 2));
}

void		text_output_instr(t_corewar *vm, const char *instr_name, t_proc *p)
{
	if (!vm->visual)
	{
		ft_printf("P%5u | %s %d %d r%d\n",
				p->pid,
				instr_name,
				(p->inv.val_arg[0] == T_REG ? p->reg[p->inv.param[0] - 1] :
				p->inv.param[0]),
				(p->inv.val_arg[1] == T_REG ? p->reg[p->inv.param[1] - 1] :
				p->inv.param[1]),
				p->inv.param[2]);
	}
}

void		print_live_ncurses(t_corewar *vm, int pos, uint32_t player_nb)
{
	if (vm->visual == 1)
	{
		mvprintw(pos + 2, 201,
				"Lives in current period :       %-5d",
				vm->player_table[player_nb].current_live);
		mvprintw(pos + 1, 201,
				"Last live                       %d", vm->cycle_count);
	}
}
