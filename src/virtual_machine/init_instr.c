#include "op.h"
#include "vm.h"

static const  t_op g_op_tab[17] =  {
        {"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
        {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
        {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
        {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
        {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
        {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
                "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
        {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
                "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
        {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
                "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
        {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
        {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
                "load index", 1, 1},
        {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
                "store index", 1, 1},
        {"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
        {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
        {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
                "long load index", 1, 1},
        {"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
        {"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
        {0, 0, {0}, 0, 0, 0, 0, 0}
};

void	init_tab_instr(void (*tab_instr[16])(t_corewar *vm,
					 t_proc *lol, t_instr *instr))
{
//	tab_instr[0] = &live;
	tab_instr[1] = &ld;
	tab_instr[8] = &zjmp;
}

int		init_instr(t_instr *instr, t_corewar *vm)
{
	init_op_tab(g_op_tab, instr);
	vm->mh = init_heap(vm->player_table, &(vm->total_proc));
	init_tab_instr(instr->tab_instr);
	vm->cycle_to_die_max = CYCLE_TO_DIE;
	vm->cycle_to_die = vm->cycle_to_die_max;
	return (0);
}
