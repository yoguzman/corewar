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
