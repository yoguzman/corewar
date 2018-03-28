/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 09:36:53 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/28 10:49:14 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

void		sti_text_output(t_proc *lol, int offset)
{
	uint32_t	arg1;
	uint32_t	arg2;

	arg1 = lol->inv.val_arg[1] == T_REG ? lol->reg[lol->inv.param[1] - 1] :
			lol->inv.param[1];
	arg2 = lol->inv.val_arg[2] == T_REG ? lol->reg[lol->inv.param[2] - 1] :
			lol->inv.param[2];
	ft_printf("P%5u | sti r%u %d %d\n%7c| -> store to %d + %d = %d%s%d)\n",
			lol->pid,
			lol->inv.param[0],
			arg1, arg2, ' ', arg1, arg2, arg1 + arg2, " (with pc and mod ",
			offset);
}

void		ldi_text_output(t_corewar *vm, t_proc *lol, int offset)
{
	uint32_t	arg1;
	uint32_t	arg2;

	if (!vm->visual)
	{
		arg1 = lol->inv.val_arg[0] == T_REG ? lol->reg[lol->inv.param[0] - 1] :
			lol->inv.param[0];
		arg2 = lol->inv.val_arg[1] == T_REG ? lol->reg[lol->inv.param[1] - 1] :
			lol->inv.param[1];
		ft_printf("P%5u | ldi %d %d r%u\n%7c| ->%s%d + %d = %d%s%d)\n",
				lol->pid,
				arg1, arg2, lol->inv.param[2], ' ', " load from ", arg1, arg2,
				arg1 + arg2, " (with pc and mod ", offset);
	}
}

void		print_winner_msg(t_corewar *vm, int wins)
{
	if (vm->visual != 1)
		ft_printf("Player %d (\"%s\") won\n",
				wins + 1, vm->player_table[wins].header.prog_name);
	else
	{
		mvprintw(45, 199, "The winner is ");
		attron(COLOR_PAIR((wins) + 2));
		mvprintw(45, 213, "%s", vm->player_table[wins].header.prog_name);
		attroff(COLOR_PAIR((wins) + 2));
		while (getch() == ERR)
			;
	}
}
