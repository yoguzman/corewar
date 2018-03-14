/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ncurses.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 00:37:10 by adauchy           #+#    #+#             */
/*   Updated: 2018/03/14 20:10:08 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

void		print_arena(unsigned char *arena, char *color)
{
	int		n;
	int		m;
	int		pos;

	attron(COLOR_PAIR(0));
	n = 0;
	pos = 2;
	while (n < MEM_SIZE)
	{
		m = 0;
		while (m < 64)
		{
			if (!color[n + m])
				attron(A_BOLD);
			attron(COLOR_PAIR(color[n + m] + 1));
			mvprintw(pos, (m * 3) + 3, "%.2x", arena[n + m]);
			attroff(A_BOLD);
			m += 1;
		}
		n += 64;
		pos += 1;
	}
	attroff(COLOR_PAIR(0));
}

void		print_players_data(t_corewar *vm)
{
	size_t	count;
	size_t	pos;

	count = 0;
	pos = 11;
	while (count < vm->players)
	{
		attron(COLOR_PAIR(6));
		mvprintw(pos, 199, "Player -%d :", count + 1);
		attron(COLOR_PAIR(count + 2));
		mvprintw(pos, 211, "%s", vm->player_table[count].header.prog_name);
		attron(COLOR_PAIR(6));
		mvprintw(pos + 1, 201, "Last live                       %d", 0);
		mvprintw(pos + 2, 201, "Lives in current period :       %d", 0);
		pos += 4;
		count += 1;
	}
}

void		print_panel(t_corewar *vm)
{
	attron(A_BOLD);
	attron(COLOR_PAIR(6));
	mvprintw(2, 199, "** PAUSED **");
	mvprintw(4, 199, "Cycles/second limit : %d", vm->cycles_sec);
	mvprintw(7, 199, "Cycle : %d", vm->cycle_count);
	mvprintw(9, 199, "Processes : %d", vm->total_proc);
	print_players_data(vm);
	attron(COLOR_PAIR(6));
	mvprintw(33, 199, "CYCLE_TO_DIE : %d", vm->cycle_to_die_max);
	mvprintw(35, 199, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvprintw(37, 199, "NBR_LIVE : %d", NBR_LIVE);
	mvprintw(39, 199, "MAX_CHECKS : %d", MAX_CHECKS);
	attroff(A_BOLD);
}

void		print_ncurses(t_corewar *vm)
{
	clear();
	attron(COLOR_PAIR(42));
	mvhline(0, 0, ' ', 253);
	mvhline(67, 0, ' ', 253);
	mvvline(0, 0, ' ', 68);
	mvvline(0, 196, ' ', 68);
	mvvline(0, 253, ' ', 68);
	attroff(COLOR_PAIR(42));
	print_panel(vm);
	print_arena(vm->arena, vm->print_data);
	refresh();
	noecho();
	vm->paused = 1;
	vm->cycles_sec = 1000000 / 50;
	vm->dec_sec = 50;
	vm->one_cycle = 0;
}

void		print_4b_in_arena(int offset, uint8_t *arena, t_proc *lol, int cnt)
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
