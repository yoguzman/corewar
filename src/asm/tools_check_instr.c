/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_check_instr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:45:41 by jcoutare          #+#    #+#             */
/*   Updated: 2018/01/30 19:09:37 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"

int		puterr(char *str)
{
	ft_puterr(str);
	return (-1);
}

int		check_name(char *str, const t_op *op_tab)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strcmp(str, op_tab[i].name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		check_nb_arg(char **str, int index_op, const t_op *op_tab)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (i > op_tab[index_op].nb_arg)
			return (-1);
		i++;
	}
	return (0);
}
