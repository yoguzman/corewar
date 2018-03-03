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

void			loop_instr(t_corewar *vm, t_mh *mh, t_instr *instr)
{
	uint64_t	i;

	if (mh->tab[0]->cycles_to_exec - mh->count > 0)
		return ;
	i = 0;
	while (mh->tab[i]->cycles_to_exec - mh->count == 0)
		exec_instr(vm, instr, mh->tab[i], &i);
}

void		visual_option(t_corewar *vm)
{
	if (vm->visual == 1)
		print_ncurses(vm);
	if (vm->dump_limit > 0 && vm->dump_limit == vm->cycle_count)
	{
		dump_arena(vm->arena);
		clear_data(vm);
		exit(EXIT_SUCCESS);
	}
}

int			engine(t_corewar *vm)
{
	t_instr	instr;

	init_instr(&instr, vm);
	while (vm->mh->pos > 0)
	{
		ft_putnbr(vm->cycle_count);
		ft_putchar(' ');
		ft_putnbr(vm->cycle_to_die);
		ft_putchar('\n');
		++(vm->cycle_count);
		--(vm->cycle_to_die);
		++(vm->mh->count);

		check_cycle_to_die(vm);

		loop_instr(vm, vm->mh, &instr);


		visual_option(vm);
	}
	getch();
	return (0);
}
