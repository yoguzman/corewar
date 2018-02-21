/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 06:37:30 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/21 06:39:36 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	update_player_count(t_corewar *vm)
{
	unsigned char	i;

	i = 0;
	while (i < MAX_PLAYERS && vm->player_table[i].header.magic != 0)
		++i;
	vm->players = i;
}
