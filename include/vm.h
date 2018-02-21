/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 00:38:24 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/21 17:36:15 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"

/*
** Sections :
** -=-=-=-=-=-
** 1.Macros
** 2.Typedefs
** 3.Definitions
*/

/*
** 1.Macros
*/

# define U_1 "Usage: ./corewar [-d N | -v --hidden] [-n N <champ1.cor> ] ...\n"
# define U_2 "\t-d N\t\t:	Dump memory after N cycles then exits\n"
# define U_5 "\t-n N\t\t:	Set the next champion's id (0..3)\n"
# define U_6 "### VISUAL MODE ###############################################\n"
# define U_3 "\t-v\t\t:	Enter visual mode\n"
# define U_4 "\t--hidden\t:	Hidden memory layout\n"
# define USAGE U_1 U_2 U_5 U_6 U_3 U_4
# define OPT_STR "dvn"
# define ERR_STR "Corewar: Error:"
# define E0 "Unrecognized option"
# define E1 "Invalid player's magic"
# define E2 "Prog_size is >= to MAX_CHAMP_SIZE"
# define THIS_PLAYER vm->player_table[vm->pid]
# define DIGITS "0123456789ABCDEF"

/*
** 2.Typedefs
*/

typedef enum	e_limits
{
	DUMP_DEFAULT = 80000,
	HEADER_SIZE = 2 * sizeof(int) + PROG_NAME_LENGTH + COMMENT_LENGTH
}				t_limits;

typedef	struct	s_champ
{
	t_header		header;
	unsigned char	*code;
}				t_champ;

typedef struct	s_corewar
{
	t_champ			player_table[MAX_PLAYERS - 1];
	unsigned char	arena[MEM_SIZE];
	int				pid;
	unsigned int	players;
	unsigned int	dump_limit;
}				t_corewar;

/* 
** 3.Definitions
*/

/* Core */

void		parse_argv(const char *argv[], t_corewar *vm);
const char	**load_champion(const char *argv[], t_corewar *vm);

/* Output */

void	print_usage(void);
void	print_error_and_exit(const char *msg);

/* Utils */

int		ft_isdigitstr(const char *s);
void	update_player_count(t_corewar *vm);

#endif
