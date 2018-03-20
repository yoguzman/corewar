/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:18:30 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/14 19:23:23 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

void	toggle_pause(t_corewar *vm)
{
	if (vm->paused)
		mvprintw(2, 199, "** RUNNING **");
	else
		mvprintw(2, 199, "** PAUSED **");
	vm->paused = !vm->paused;
}

void	dec_speed(t_corewar *vm)
{
	if (vm->dec_sec > 10)
		vm->dec_sec -= 10;
	vm->cycles_sec = 1000000 / vm->dec_sec;
	mvprintw(4, 199 + 22, "%-4d", vm->dec_sec);
}

void	inc_speed(t_corewar *vm)
{
	if (vm->dec_sec < 1000)
		vm->dec_sec += 10;
	vm->cycles_sec = 1000000 / vm->dec_sec;
	mvprintw(4, 199 + 22, "%-4d", vm->dec_sec);
}

void	one_cycle(t_corewar *vm)
{
	vm->paused = 1;
	mvprintw(2, 199, "** PAUSED **");
	vm->one_cycle = 1;
}

void			key_action(t_corewar *vm)
{
	int		ret;

	ret = 0;
	attron(A_BOLD);
	attron(COLOR_PAIR(6));
	ret = getch();
	if (ret == ' ')
		toggle_pause(vm);
	else if (ret == ',')
		dec_speed(vm);
	else if (ret == '.')
		inc_speed(vm);
	else if (ret == 's')
		one_cycle(vm);
	else if (ret == 27)
	{
		clear_data(vm);
		exit(EXIT_SUCCESS);
	}
	attron(A_BOLD);
}
