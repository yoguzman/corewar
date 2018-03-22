/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 01:01:17 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/21 19:05:05 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

static const char	**init_visual_mode(const char *argv[], t_corewar *vm)
{
	(void)argv;
	vm->visual = 1;
	return (&argv[1]);
}

static const char	**set_champion_number(const char *argv[], t_corewar *vm)
{
	if (argv[1] == NULL || !ft_isdigitstr(argv[1]))
		return (&(argv[1]));
	vm->player_id = ft_atoi(argv[1]) - 1;
	if (vm->player_id > MAX_PLAYERS - 1 || THIS_PLAYER.code != NULL)
		vm->player_id = get_empty_slot(vm->player_table);
	return (&argv[2]);
}

static const char	**set_load_address(const char *argv[], t_corewar *vm)
{
	if (argv[1] == NULL || ((vm->player_id == -1
			&& (vm->player_id = get_empty_slot(vm->player_table)) == -1)
			|| !ft_isdigitstr(argv[1])))
		return (&argv[1]);
	vm->load_address = ft_atoi(argv[1]);
	return (argv + 2);
}

static const char	**set_texte_mode(const char *argv[], t_corewar *vm)
{
	(void)argv;
	vm->visual = 0;
	return (&argv[1]);
}

void				parse_argv(const char *argv[], t_corewar *vm)
{
	const char	*arg;
	const char	*opt;
	const char	**(*exec_opt[OPTIONS])(const char *[], t_corewar *);

	exec_opt[0] = save_dump_limit;
	exec_opt[1] = init_visual_mode;
	exec_opt[2] = set_champion_number;
	exec_opt[3] = set_load_address;
	exec_opt[4] = set_texte_mode;
	vm->players = count_players(argv);
	while (*argv != NULL)
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
