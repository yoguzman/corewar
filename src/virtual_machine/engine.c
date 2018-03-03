/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 14:22:57 by adauchy           #+#    #+#             */
/*   Updated: 2018/02/28 20:03:13 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
/*
int32_t			engine(t_corewar *vm)
{
	print_processes(vm->mh = init_heap(vm->player_table));
	while (TOUT LE MONDE NEST PAS DANS LA MORT)
	{

		cycle_to_die--
		SI cycle_to_die == 0
			verification de la vivance des champions
		Si NBR_LIVE est atteint
			CYCLE_TO_DIE -= CYCLE_DELTA
		cycle_to_dye = CYCLE_TO_DIE
		cycle++
		On va dans chaque proc
			SI nous ne sommes pas sur une instructions connu
				incrementer le pc de 1 octets
			SI on arrive sur une instruction
				set cycles_to_exec
			SI on est sur une instruction
				on decremente les cycles_to_exec
			SI le cycle_to_exec arrive a son terme
		    	EXECUTION instruction
				incrementer le pc du nombre d octet de linstruction
		Si NCURSES ACTIVE
			NCURSES
		Si (DUMP ACTIVE ET cycles = dump_limit)
			dump et EXIT
	}
	AFFICHER LE PODIUM
}
*/

int			engine(t_corewar *vm)
{
	int tamer = 0;
	init_op_tab(g_op_tab, &instr);
	while (42)
	{
		++(vm->cycle_count);
		--(vm->cycle_to_die);



		/* fonction check_cycle_to_die */
		if (vm->cycle_to_die == 0)
		{
			//ret = check_live_player(); // a creer (check les lives et les resets a 0)
			//check_live_process(); // a creer(check les lives et les resets a 0)
			//if (ret >= NBR_LIVE) // a creer
			//	vm->cycle_to_die_max -= CYCLE_DELTA;
			vm->cycle_to_die = vm->cycle_to_die_max;
		}
		/* fonction end */

		/* fonction exec_instr */
		if (tamer == 0)
		{
			mabite(vm);
			tamer++;
		}
		/* fonction end */

		/* fonction visual_option */
		if (vm->visual == 1)
			print_ncurses(vm);
		if (vm->dump_limit > 0 && vm->dump_limit == vm->cycle_count)
		{
			dump_arena(vm->arena);
			clear_data(vm);
			exit(EXIT_SUCCESS);
		}
		/* fonction end */

	}
	getch();
	return (0);
}
