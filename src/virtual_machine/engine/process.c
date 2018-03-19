/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 16:15:57 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/19 18:47:27 by abeauvoi         ###   ########.fr       */
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
	ft_putnbr(new->reg[0]);
	new->pid = *total_proc;
	++*total_proc;
	return (new);
}

void	init_child(t_corewar *vm, t_proc *child, t_instr *instr)
{
	child->pid = vm->total_proc++;
	fill_ins_proc(vm, instr, child);
	insert(vm->mh, child);
	++vm->nb_processes;
}
