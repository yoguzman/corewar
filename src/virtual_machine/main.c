/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 00:42:57 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/24 20:11:46 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

static void	init_vm(const char *argv[], t_corewar *vm)
{
	ft_bzero(vm, sizeof(*vm));
	vm->player_id = -1;
	parse_argv(argv + 1, vm);
	print_players(vm->player_table);
	load_champions_in_arena(vm);
	dump_arena(vm->arena);
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
		init_vm(argv, &vm);
		engine(&vm);
		clear_data(&vm);
	}
	return (0);
}
