/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 00:38:24 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/23 03:46:15 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stddef.h>
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
# define U_2 "\t-d N\t\t:	Dump memory after N cycles then exit\n"
# define U_5 "\t-n N\t\t:	Set the next champion's id (1..4)\n"
# define U_6 "### VISUAL MODE ###############################################\n"
# define U_3 "\t-v\t\t:	Enter visual mode\n"
# define U_4 "\t--hidden\t:	Hidden memory layout\n"
# define USAGE U_1 U_2 U_5 U_6 U_3 U_4

/* Error messages */

# define ERR_STR "Corewar: Error: "
# define E0 "Unrecognized option"
# define E1 "Invalid player's magic"
# define E2 "Prog_size is superior to MAX_CHAMP_SIZE"
# define E3 "Invalid file extension"
# define E4 "Too many players"

/* Misc. */

# define THIS_PLAYER vm->player_table[vm->player_id]
# define DIGITS "0123456789abcdef"
# define OPT_STR "dvn"

/*
** 2.Typedefs
*/

/* 4 * sizeof(int) = magic, prog_size & 2 ints at the end of prog_name and
** comment
*/

typedef enum	e_limits
{
	DUMP_DEFAULT = 80000,
	HEADER_SIZE = 4 * sizeof(int) + PROG_NAME_LENGTH + COMMENT_LENGTH
}				t_limits;

typedef	struct	s_player
{
	t_header		header;
	unsigned char	*code;
	unsigned int	load_index;
}				t_player;

typedef struct	s_process
{
	unsigned char		registers[REG_NUMBER][REG_SIZE];
	unsigned char		pc[REG_SIZE];
	unsigned int		carry;
	unsigned int		cycles_to_exec;
	unsigned int		live_count;
	unsigned int		player_id;
	struct s_process	*next;
}				t_process;

typedef struct	s_corewar
{
	t_player		player_table[MAX_PLAYERS];
	unsigned char	arena[MEM_SIZE];
	int				player_id;
	unsigned int	players;
	unsigned int	dump_limit;
	t_process		*processes;	
}				t_corewar;

/* 
** 3.Definitions
*/

/* Core */

void		parse_argv(const char *argv[], t_corewar *vm);
const char	**load_champion(const char *argv[], t_corewar *vm);
void		load_champions_in_arena(t_corewar *vm);

/* Output */

void		print_usage(void);
void		print_error_and_exit(const char *msg);
void		clean_print_err_exit(const char *msg,
		t_player player_table[MAX_PLAYERS]);
void		print_mem(void *mem, size_t mem_size);
void		print_players(t_player player_table[MAX_PLAYERS]);
void		dump_arena(unsigned char arena[MEM_SIZE]);

/* Utils */

int			ft_isdigitstr(const char *s);
void		update_player_count(t_corewar *vm);
void		switch_endianness(void *mem, size_t mem_size);
int			get_empty_slot(t_player player_table[MAX_PLAYERS]);

/* Data clearance */

void		clear_data(t_corewar *vm);
void		free_champions(t_player player_table[MAX_PLAYERS]);

/* Instructions */

#endif
