/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 20:41:07 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/16 13:11:42 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_players(t_player player_table[MAX_PLAYERS])
{
	uint8_t	i;

	i = 0;
	ft_printf("!!!!!!! AND TODAY'S MATCHUP IS ... !!!!!!!\n");
	while (i < MAX_PLAYERS)
	{
		if (player_table[i].code != NULL)
		{
			ft_printf(">> Player %u :\n"
					"\t\\__ Name : \"%s\"\n"
					"\t\\__ Size : %u bytes\n"
					"\t\\__ Comment : (\"%s\")\n", i + 1,
					player_table[i].header.prog_name,
					player_table[i].header.prog_size,
					player_table[i].header.comment);
		}
		++i;
	}
}
