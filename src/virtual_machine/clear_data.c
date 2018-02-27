/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 20:04:52 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/24 15:29:15 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

void	free_champions(t_player player_table[MAX_PLAYERS])
{
	unsigned char	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		free(player_table[i].code);
		++i;
	}
}

void	clear_data(t_corewar *vm)
{
	free_champions(vm->player_table);
	free(vm->print_data);
	free(vm->arena);
}
