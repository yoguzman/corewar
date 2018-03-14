/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_cod_oct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:53:29 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/14 18:36:51 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int			replace_cod_oct(unsigned char octet, unsigned char op_code,
		const t_op g_op_tab[17])
{
	int			i;
	int			div;
	const int	*replace;

	i = -1;
	div = 6;
	replace = (const int[6]){0xC0, 0x30, 0xC, 0x40, 0x10, 4};
	while (++i < 3)
	{
		if (((op_code <= 15) && (((octet >> div) & 3) == 2
						|| ((octet >> div) & 3) == 3))
				&& (i < g_op_tab[op_code].parameter_count)
				&& ((g_op_tab[op_code].rep[i] == 1)
					|| (g_op_tab[op_code].rep[i] == 2
						&& ((octet >> div) & 3) == 3)))
		{
			if (((octet >> div) & 3) == 2)
				octet = octet | replace[i];
			else if (((octet >> div) & 3) == 3)
				octet = octet ^ replace[i + 3];
		}
		div -= 2;
	}
	return (octet);
}
