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

void			loop_instr(t_corewar *vm, t_mh *mh, t_instr *instr)
{
	uint64_t	i;

	if (mh->tab[0]->cycles_to_exec - mh->count > 0)
		return ;
	i = 0;
	while (i < mh->pos && mh->tab[i]->cycles_to_exec - mh->count == 0)
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
		++(vm->cycle_count);
		--(vm->cycle_to_die);
		++(vm->mh->count);

		check_cycle_to_die(vm);
		if (vm->mh->pos == 0)
			break ;

		loop_instr(vm, vm->mh, &instr);


		visual_option(vm);
	}
	getch();
	return (0);
}
