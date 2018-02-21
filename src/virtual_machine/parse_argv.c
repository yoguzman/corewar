/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 01:01:17 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/21 06:20:01 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "vm.h"

static const char	**save_dump_limit(const char *argv[], t_corewar *vm)
{
	vm->dump_limit = ft_atoi(argv[1]);
	if (vm->dump_limit > INT_MAX)
	{
		/*ft_printf("Corewar: Error: %s isn't a valid dump limit, \
				set to default value %u cycles\n", dump_limit, DUMP_DEFAULT);*/
		vm->dump_limit = DUMP_DEFAULT;
	}
	return (&argv[2]);
}

static const char	**init_visual_mode(const char *argv[], t_corewar *vm)
{
	(void)argv;
	(void)vm;
	return (&argv[1]);
}

static const char	**set_champion_number(const char *argv[], t_corewar *vm)
{
	if (!ft_isdigitstr(argv[1]))
		return (&argv[1]);
	vm->pid = ft_atoi(argv[1]);
	if (vm->pid > MAX_PLAYERS - 1)
		vm->pid = vm->players;
	return (&argv[2]);
}

void				parse_argv(const char *argv[], t_corewar *vm)
{
	const char	*arg;
	const char	*opt;
	const char	**(*exec_opt[3])(const char *[], t_corewar *);

	exec_opt[0] = save_dump_limit;
	exec_opt[1] = init_visual_mode; 
	exec_opt[2] = set_champion_number;
	while (argv != NULL)
	{
		arg = *argv;
		if (*arg == '-')
		{
			if (ft_strlen(arg) == 2
				&& (opt = ft_strchr(OPT_STR, arg[1])) != NULL)
				argv = exec_opt[opt - OPT_STR](argv, vm);
			else
				print_error_and_exit(E0);
		}
		else
			argv = load_champion(argv, vm);
	}
}
