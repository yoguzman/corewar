/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 00:42:57 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/27 17:23:39 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include <stdio.h>

static int	init_vm(const char *argv[], t_corewar *vm)
{
	vm->players = 0;
	vm->cycles_sec = 50;
	vm->cycle_count = 0;
	if (!(vm->arena = (unsigned char*)malloc(MEM_SIZE)))
		return (-1);
	if (!(vm->print_data = (char*)malloc(MEM_SIZE)))
		return (-1);
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(vm->print_data, MEM_SIZE);
	ft_bzero(vm->player_table, sizeof(vm->player_table));
	vm->paused = 1;
	vm->player_id = -1;
	parse_argv(argv + 1, vm);
//	print_players(vm->player_table);
	update_player_count(vm);
	if (load_champions_in_arena(vm) == -1)
		return (-1);
//	dump_arena(vm->arena);
	vm->nb_processes = vm->players + 1;
	return (0);
}

void		init_print_data(t_corewar *vm)
{
	size_t		n;

	initscr();
	curs_set(0);
	start_color();
	init_color(42, 420, 420, 420);
	init_pair(42, 42, 42);
	init_pair(1, 42, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);
	n = 0;
	while (n < vm->players)
	{
		vm->player_table[n].current_live = 20;
		vm->player_table[n].last_live = 12;
		n += 1;
	}

}

int			main(int argc, const char *argv[])
{
	t_corewar	vm;

	if (argc == 1 || (argc == 2 && (!ft_strcmp(argv[1], "-u")
				|| !ft_strcmp(argv[1], "-usage")
				|| !ft_strcmp(argv[1], "-h")
				|| !ft_strcmp(argv[1], "-help"))))
		print_usage();
	else
	{
		if (init_vm(argv, &vm) == -1)
			return (-1);
		init_print_data(&vm);
		engine(&vm);
		clear_data(&vm);
	}
	return (0);
}
