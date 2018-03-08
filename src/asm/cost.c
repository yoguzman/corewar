/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:58:15 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/08 14:58:19 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		live_cost(t_if *info_line)
{
	info_line->cost_line = 5;
}

void		ld_cost(t_if *info_line)
{
	info_line->cost_line = 3;
	if (info_line->arg[0][0] == '%')
		info_line->cost_line += 4;
	else
		info_line->cost_line += 2;
}

void		st_cost(t_if *info_line)
{
	info_line->cost_line = 3;
	if (info_line->arg[1][0] == 'r')
		info_line->cost_line += 1;
	else
		info_line->cost_line += 2;
}

void		add_cost(t_if *info_line)
{
	info_line->cost_line = 5;
}

void		sub_cost(t_if *info_line)
{
	info_line->cost_line = 5;
}
