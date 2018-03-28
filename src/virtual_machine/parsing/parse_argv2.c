/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:59:59 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/21 19:05:05 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

const char	**save_dump_limit(const char *argv[], t_corewar *vm)
{
	if (argv[1] == NULL || !ft_isdigitstr(argv[1]))
		return (&argv[1]);
	vm->dump_limit = ft_atoi(argv[1]);
	if (vm->dump_limit > INT_MAX)
	{
		ft_printf("Warning: Dump cycle > %d, set to %d\n", INT_MAX,
				DUMP_DEFAULT);
		vm->dump_limit = DUMP_DEFAULT;
	}
	return (&argv[2]);
}
