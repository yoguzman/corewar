/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 00:38:24 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/07 18:14:37 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <curses.h>
# include <unistd.h>
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

/*
** Error messages
*/

# define ERR_STR "Corewar: Error: "
# define E0 "Unrecognized option"
# define E1 "Invalid player's magic"
# define E2 "Prog_size is superior to MAX_CHAMP_SIZE"
# define E3 "Invalid file extension"
# define E4 "Too many players"

/*
** Misc.
*/

# define THIS_PLAYER vm->player_table[vm->player_id]
# define PT(x)	player_table[x]
# define CTE(x) (x)->cycles_to_exec
# define PID(x) (x)->pid
# define DIGITS "0123456789abcdef"
# define OPT_STR "dvna"

/*
** Calculations
*/

# define LCHILD(x) ((x << 1) + 1)
# define RCHILD(x) ((x << 1) + 2)
# define PARENT(x) ((x - 1) >> 1)
# define SWP32A(nb) ((nb & 0xff000000) >> 24) | ((nb >> 0x00ff0000) >> 8)
# define SWP32B(nb) ((nb & 0x0000ff00) << 8) | (nb << 24)
# define SWAP32(nb) SWP32A(nb) | SWP32B(nb)
# define SWAP16(nb) ((nb & 0xff) >> 8) | (nb << 8)

/*
** 2.Typedefs
*/

/*
** 2 ints are used to terminate the program name and the comment
*/

typedef enum	e_limits
{
	OPTIONS = 4,
	DUMP_DEFAULT = 80000,
	START_HEAP_SIZE = 10000,
	HEADER_SIZE = 4 * sizeof(int32_t) + PROG_NAME_LENGTH + COMMENT_LENGTH
}				t_limits;

typedef	struct	s_player
{
	t_header	header;
	uint8_t		*code;
	uint32_t	load_address;
	int			last_live;
	int			current_live;
	int			last_breakdown;
	int			current_breakdown;
	char		die;
}				t_player;

typedef struct	s_process
{
	uint32_t	reg[REG_NUMBER];
	uint32_t	pc;
	uint8_t		carry;
	int			current_live;
	uint8_t		player_id;
	uint16_t	cycles_to_exec;
	uint32_t	pid;
}				t_proc;

typedef struct	s_min_heap
{
	t_proc		**tab;
	uint64_t	size;
	uint64_t	pos;
	uint64_t	count;
}				t_mh;

typedef struct	s_corewar
{
	int			paused;
	int			cycles_sec;
	uint32_t	cycle_count;
	int			nb_processes;
	int			cycle_to_die;
	int			cycle_to_die_max;
	char		*print_data;
	t_player	player_table[MAX_PLAYERS];
	uint8_t		*arena;
	int32_t		player_id;
	uint32_t	players;
	uint32_t	dump_limit;
	t_mh		*mh;
	int			visual;
	uint64_t	total_proc;
}				t_corewar;

typedef struct			s_instr
{
	void				(*tab_instr[17])(t_corewar *vm, t_proc *lol, struct s_instr *instr);
	int					val_arg[3];
	unsigned char		opcode;
	unsigned long long	param[3];
	const t_op			*op_tab;
}						t_instr;

/*
** 3.Definitions
*/

/*
** Engine
*/

int32_t		engine(t_corewar *vm);
void		print_ncurses(t_corewar *vm);
void		print_breakdown(t_corewar *vm);

/*
** Initialisation
*/

void		parse_argv(const char *argv[], t_corewar *vm);
const char	**load_champion(const char *argv[], t_corewar *vm);
int			load_champions_in_arena(t_corewar *vm);
void		init_op_tab(const t_op g_op_tab[17], t_instr *instr);
int			init_instr(t_instr *instr, t_corewar *vm);

/*
** Output
*/

void		print_usage(void);
void		print_error_and_exit(const char *msg);
void		clean_print_err_exit(const char *msg,
		t_player player_table[MAX_PLAYERS]);
void		print_mem(void *mem, uint64_t mem_size);
void		print_players(t_player player_table[MAX_PLAYERS]);
void		dump_arena(uint8_t arena[MEM_SIZE]);
void		print_processes(t_mh *mh);

/*
** Utils
*/

int			ft_isdigitstr(const char *s);
void		switch_endianness(void *mem, uint64_t mem_size);
int			get_empty_slot(t_player player_table[MAX_PLAYERS]);

/*
** Data clearance
*/

void		clear_data(t_corewar *vm);
void		free_champions(t_player player_table[MAX_PLAYERS]);
void		free_processes(t_mh *mh);
void		free_min_heap(t_mh **mh);

/* Check live et check cycle to die */

void		check_cycle_to_die(t_corewar *vm);

/* reset */

void		reset_pc(uint32_t pc);

/* Instructions */

int			get_octet(char octet, t_instr *instr);
void		la_balade(t_proc *lol, t_instr *instr);
int			get_data(t_corewar *vm, t_proc *lol, t_instr *instr);
void		exec_instr(t_corewar *vm, t_instr *instr, t_proc *proc, uint64_t *i);
void		live(t_corewar *vm, t_proc *lol, t_instr *instr);
void		ld(t_corewar *vm, t_proc *lol, t_instr *instr);
void		st(t_corewar *vm, t_proc *lol, t_instr *instr);
void		add(t_corewar *vm, t_proc *lol, t_instr *instr);
void		sub(t_corewar *vm, t_proc *lol, t_instr *instr);
void		ft_and(t_corewar *vm, t_proc *lol, t_instr *instr);
void		ft_or(t_corewar *vm, t_proc *lol, t_instr *instr);
void		ft_xor(t_corewar *vm, t_proc *lol, t_instr *instr);
void		zjmp(t_corewar *vm, t_proc *lol, t_instr *instr);
void		ldi(t_corewar *vm, t_proc *lol, t_instr *instr);
void		sti(t_corewar *vm, t_proc *lol, t_instr *instr);
void		ft_fork(t_corewar *vm, t_proc *lol, t_instr *instr);
void		lld(t_corewar *vm, t_proc *lol, t_instr *instr);
void		lldi(t_corewar *vm, t_proc *lol, t_instr *instr);
void		ft_lfork(t_corewar *vm, t_proc *lol, t_instr *instr);
void		aff(t_corewar *vm, t_proc *lol, t_instr *instr);
void		get_one_arg(t_corewar *vm, t_proc *lol, t_instr *instr);

/*
** priority_queue.c
*/

t_mh		*init_heap(t_player player_table[MAX_PLAYERS],
		uint64_t *total_proc, t_corewar *vm, t_instr *instr);
void		insert(t_mh *mh, t_proc *entry);
void		heapify(t_mh *mh, uint32_t i);
void		delete_any(t_mh *mh, uint32_t i);

/*
** process.c
*/

void		swap_process(t_proc **a, t_proc **b);
t_proc		*spawn_process(uint64_t load_address, uint8_t player_id,
		uint64_t *total_proc);
void		kill_process(t_mh *mh, uint32_t index);

#endif
