/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 06:37:30 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/22 22:08:35 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	update_player_count(t_corewar *vm)
{
	unsigned char	i;

	vm->players = 0;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player_table[i].code != NULL)
			++vm->players;
		++i;
	}
}
