/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 00:42:57 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/21 18:04:31 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

static void	init_vm(t_corewar *vm)
{
	ft_bzero(vm, sizeof(*vm));
	ft_memcpy(&vm->lookup, &(unsigned char [16]){
			0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
			0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf}, sizeof (vm->lookup));
	vm->pid = -1;
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
		init_vm(&vm);
		parse_argv(&argv[1], &vm);
	}
	return (0);
}
