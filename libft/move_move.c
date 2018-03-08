/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 15:22:28 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/06 18:04:20 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void			swap_move(char *string, int i, int save, t_dt *dt)
{
	char		save_l;

	if (save != -1 && (string[i] == '-' || string[i] == '+' ||
						(string[i] == ' ' && dt->tab_f['-'] == 0)))
	{
		save_l = string[i];
		string[i] = string[save];
		string[save] = save_l;
	}
	if (save != -1 && (string[i] == 'x' || string[i] == 'X'))
	{
		save_l = string[i];
		string[i] = string[save];
		string[save + 1] = save_l;
	}
}

void			move_move(char *string, t_dt *dt)
{
	int			i;
	int			save;

	i = 0;
	save = -1;
	if (dt->conv == 'x' || dt->conv == 'X' || dt->conv == 'o' ||
			dt->conv == 'O' || dt->conv == 'u' || dt->conv == 'U' ||
			dt->conv == 'd' || dt->conv == 'D' || dt->conv == 'i')
	{
		while (string[i])
		{
			if (string[i] == '0' && save == -1)
				save = i;
			swap_move(string, i, save, dt);
			++i;
		}
	}
}
