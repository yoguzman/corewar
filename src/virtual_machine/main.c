/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 00:42:57 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/28 14:31:06 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

static int		init_vm(const char *argv[], t_corewar *vm)
{
	ft_bzero(vm, sizeof(*vm));
	vm->visual = 2;
	vm->total_proc = 1;
	vm->load_address = -1;
	vm->players = 0;
	vm->cycles_sec = 50;
	vm->cycle_count = 0;
	if (!(vm->arena = (unsigned char *)malloc(MEM_SIZE))
			|| !(vm->print_data = (char *)malloc(MEM_SIZE)))
		exit(EXIT_FAILURE);
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(vm->print_data, MEM_SIZE);
	ft_bzero(vm->player_table, sizeof(t_player) * MAX_PLAYERS);
	vm->paused = 1;
	vm->player_id = -1;
	vm->player_table[0].load_address = -1;
	vm->player_table[1].load_address = -1;
	vm->player_table[2].load_address = -1;
	vm->player_table[3].load_address = -1;
	parse_argv(argv + 1, vm);
	if (vm->visual == 0 || vm->visual == 2)
		print_players(vm->player_table);
	return (0);
}

void			init_print_data(void)
{
	curs_set(0);
	nodelay(initscr(), TRUE);
	start_color();
	init_color(42, 420, 420, 420);
	init_pair(42, 42, 42);
	init_pair(1, 42, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_GREEN);
	init_pair(8, COLOR_BLACK, COLOR_BLUE);
	init_pair(9, COLOR_BLACK, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_CYAN);
	init_pair(11, COLOR_WHITE, 42);
}

int				main(int argc, const char *argv[])
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
		if (vm.visual == 1)
			init_print_data();
		engine(&vm);
		clear_data(&vm);
	}
	return (0);
}
