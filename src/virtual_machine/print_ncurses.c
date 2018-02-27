/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ncurses.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 00:37:10 by adauchy           #+#    #+#             */
/*   Updated: 2018/02/27 17:39:34 by adauchy          ###   ########.fr       */
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
	if (vm->paused)
		mvprintw(2, 199, "** PAUSED **");
	else
		mvprintw(2, 199, "** RUNNING **");
	mvprintw(4, 199, "Cycles/second limit : %d", vm->cycles_sec);
	mvprintw(7, 199, "Cycle : %d", vm->cycle_count);
	mvprintw(9, 199, "Processes : %d", vm->nb_processes);
	print_players_data(vm);
	print_breakdown(vm);
	attron(COLOR_PAIR(6));
	mvprintw(33, 199, "CYCLE_TO_DIE : %d", 42);
	mvprintw(35, 199, "CYCLE_DELTA : %d", 42);
	mvprintw(37, 199, "NBR_LIVE : %d", 42);
	mvprintw(39, 199, "MAX_CHECKS : %d", 42);
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
	print_arena(vm->arena, vm->print_data);
	print_panel(vm);
	refresh();
}
