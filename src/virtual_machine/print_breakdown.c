/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_breakdown.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:27:34 by adauchy           #+#    #+#             */
/*   Updated: 2018/02/27 17:38:20 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

static void		calc_breakdown(t_corewar *vm)
{
	int		total_current_live;
	int		total_last_live;
	size_t	n;

	total_current_live = 0;
	total_last_live = 0;
	n = 0;
	while (n < vm->players)
	{
		total_last_live += vm->player_table[n].last_live;
		total_current_live += vm->player_table[n].current_live;
		n += 1;
	}
	n = 0;
	while (n < vm->players)
	{
		vm->player_table[n].last_breakdown =
			vm->player_table[n].last_live * 50 / total_last_live;
		vm->player_table[n].current_breakdown =
			vm->player_table[n].current_live * 50 / total_current_live;
		n += 1;
	}
}

static void		print_layout(void)
{
	mvprintw(27, 199, "Live breakdown for current period :");
	attron(COLOR_PAIR(1));
	mvprintw(28, 199, "[--------------------------------------------------]");
	attron(COLOR_PAIR(6));
	mvprintw(30, 199, "Live breakdown for last period :");
	attron(COLOR_PAIR(1));
	mvprintw(31, 199, "[--------------------------------------------------]");
}

void			print_breakdown(t_corewar *vm)
{
	size_t		n;
	size_t		i;
	size_t		j;
	static char	breakdown[] = "----------------------------------------------";

	calc_breakdown(vm);
	print_layout();
	n = 0;
	i = 200;
	j = 200;
	while (n < vm->players)
	{
		printf("curr ==> %d\n", vm->player_table[n].current_breakdown);
		printf("last ==> %d\n", vm->player_table[n].last_breakdown);
		attron(COLOR_PAIR(n + 2));
		mvprintw(28, i, "%.*s", vm->player_table[n].current_breakdown,
				breakdown);
		i += vm->player_table[n].current_breakdown;
		mvprintw(31, j, "%.*s", vm->player_table[n].last_breakdown, breakdown);
		j += vm->player_table[n].last_breakdown;
		n += 1;
	}
}
