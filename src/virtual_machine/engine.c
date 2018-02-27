/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 14:22:57 by adauchy           #+#    #+#             */
/*   Updated: 2018/02/27 16:41:24 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
/*
int			engine(t_corewar *vm)
{
	* Remplir la liste chainee des process
	while (TOUT LE MONDE EST VIVANT)
	{
		
		 * cycle_to_die--
		 * SI cycle_to_die == 0
		    verification de la vivance des champions
			 Si NBR_LIVE est atteint
               CYCLE_TO_DIE -= CYCLE_DELTA
			cycle_to_dye = CYCLE_TO_DIE
		 * cycle++
		 * On va dans chaque proc
		 * on decremente les cycles_to_exec
		 * SI le cycle_to_exec arrive a son terme
		    EXECUTION instruction
		 Si NCURSES ACTIVE
		     NCURSES
		 Si (DUMP ACTIVE ET cycles = dump_limit)
		    dump et EXIT
	} 
	AFFICHER LE PODIUM	
	return (0);
}*/

int			engine(t_corewar *vm)
{
	(void)vm;
	int		count;

	count = 0;
	while (count < 1)
	{
		print_ncurses(vm);
		count += 1;
	}
	getch();
	endwin();
	return (0);
}
