/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 16:15:57 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/14 19:02:50 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "vm.h"

void	swap_process(t_proc **a, t_proc **b)
{
	t_proc	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_proc	*spawn_process(uint64_t load_address, uint8_t player_id,
		uint64_t *total_proc)
{
	t_proc	*new;

	if (!(new = (t_proc *)malloc(sizeof(*new))))
		return (NULL);
	ft_bzero(new, sizeof(*new));
	new->pc = load_address;
	new->reg[0] = -1U - player_id;
	new->pid = *total_proc;
	++*total_proc;
	return (new);
}

void	init_child(t_corewar *vm, t_proc *lol, t_proc *child, t_instr *instr)
{
	ft_memcpy(child, lol, sizeof(*lol));
	child->pid = vm->total_proc++;
	child->cycles_to_exec = vm->cycle_count + 1;
	if ((vm->arena[child->pc] - 1) <= 15)
		child->cycles_to_exec =
			instr->op_tab[vm->arena[child->pc] - 1].cycles_to_exec
			+ vm->cycle_count;
	insert(vm->mh, child);
	++vm->nb_processes;
}
