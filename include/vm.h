/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 00:38:24 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/25 20:15:22 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stddef.h>
# include <inttypes.h>
# include <limits.h>
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
# define PT(x)	player_table[x]
# define CTE(x) x->cycles_to_exec
# define DIGITS "0123456789abcdef"
# define OPT_STR "dvn"
# define LCHILD(x) ((x << 1) + 1)
# define RCHILD(x) ((x << 1) + 2)
# define PARENT(x) ((x - 1) >> 1)

/*
** 2.Typedefs
*/

/*
** 2 ints are used to terminate the program name and the comment
*/

typedef enum	e_limits
{
	DUMP_DEFAULT = 80000,
	HEADER_SIZE = 4 * sizeof(int32_t) + PROG_NAME_LENGTH + COMMENT_LENGTH
}				t_limits;

typedef	struct	s_player
{
	t_header	header;
	uint8_t		*code;
	uint32_t	load_address;
}				t_player;

typedef struct	s_process	t_proc;

struct			s_process
{
# if REG_SIZE == 1
	uint8_t		reg[REG_NUMBER];

# elif REG_SIZE == 2
	uint16_t	reg[REG_NUMBER];

# elif REG_SIZE == 4
	uint32_t	reg[REG_NUMBER];

# else
	uint64_t	reg[REG_NUMBER];

# endif

# if MEM_SIZE >= 0 && MEM_SIZE <= UCHAR_MAX
	uint8_t		pc;

# elif MEM_SIZE > UCHAR_MAX && MEM_SIZE <= USHRT_MAX
	uint16_t	pc;

# elif MEM_SIZE > USHRT_MAX && MEM_SIZE <= UINT_MAX
	uint32_t	pc;

# else
	uint64_t	pc;

# endif

	uint8_t		carry;
	uint8_t		player_id;
	uint16_t	cycles_to_exec;
	uint16_t	lives;
};

typedef struct	s_min_heap
{
	t_proc		**tab;
	uint64_t	size;
	uint32_t	pos;
}				t_mh;

typedef struct	s_corewar
{
	t_player	player_table[MAX_PLAYERS];
	uint8_t		arena[MEM_SIZE];
	int32_t		player_id;
	uint32_t	players;
	uint32_t	dump_limit;
	t_mh		*mh;
}				t_corewar;

/* 
** 3.Definitions
*/

/* Engine */

int32_t		engine(t_corewar *vm);

/* Initialisation */

void		parse_argv(const char *argv[], t_corewar *vm);
const char	**load_champion(const char *argv[], t_corewar *vm);
void		load_champions_in_arena(t_corewar *vm);

/* Output */

void		print_usage(void);
void		print_error_and_exit(const char *msg);
void		clean_print_err_exit(const char *msg,
		t_player player_table[MAX_PLAYERS]);
void		print_mem(void *mem, uint64_t mem_size);
void		print_players(t_player player_table[MAX_PLAYERS]);
void		dump_arena(uint8_t arena[MEM_SIZE]);
void		print_processes(t_mh *mh);

/* Utils */

int			ft_isdigitstr(const char *s);
void		switch_endianness(void *mem, uint64_t mem_size);
int			get_empty_slot(t_player player_table[MAX_PLAYERS]);

/* Data clearance */

void		clear_data(t_corewar *vm);
void		free_champions(t_player player_table[MAX_PLAYERS]);
void		free_processes(t_mh *mh);
void		free_min_heap(t_mh **mh);

/* Instructions */

/* priority_queue.c */

t_mh		*init_heap(t_player player_table[MAX_PLAYERS]);
void		insert(t_mh *mh, t_proc *entry);
void		heapify(t_mh *mh, uint32_t i);
void		delete_min(t_mh *mh);

/* process.c */

void		swap_process(t_proc **a, t_proc **b);
t_proc		*spawn_process(uint64_t load_address, uint8_t player_id);
void		kill_process(t_mh *mh, uint32_t index);	

#endif
