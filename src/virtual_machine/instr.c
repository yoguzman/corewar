/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:44:10 by jcoutare          #+#    #+#             */
/*   Updated: 2018/02/28 20:04:49 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

// arg[0] = upcode;

void	avance_pc(t_corewar *vm, t_proc *lol)
{

}

void	ld(t_corewar *vm, t_proc *lol)
{
	char *arg[2];

	arg[0] = ft_itoa_base(vm->arena[lol->pc], "01");
	ft_putstr("\nfirst parametre = ");
	ft_putstr(arg[0]);
	lol->pc += 5;
	ft_putstr("\nregistre = ");
	arg[1] = ft_itoa_base(vm->arena[lol->pc], "01");
	ft_putstr(arg[1]);
}

void	init_tab_instr(void (*tab_instr[16])(t_corewar *vm, t_proc *lol))
{
	tab_instr[0] = &avance_pc;
	tab_instr[10] = &ld;
}

void	mabite(t_corewar *vm)
{
	t_proc lol;
	char *arg[3];
	void		(*tab_instr[16])(t_corewar *vm, t_proc *lol);

	lol.pc = 0;
	arg[0] = ft_itoa_base(vm->arena[lol.pc], "01");
	lol.pc++;
	ft_putstr("\nupcode = ");
	ft_putstr(arg[0]);
	init_tab_instr(tab_instr);
	tab_instr[ft_atoi(arg[0])](vm, &lol);
}
