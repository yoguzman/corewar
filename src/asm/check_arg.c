/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 15:37:31 by jcoutare          #+#    #+#             */
/*   Updated: 2018/02/16 14:27:16 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"

int		direct_is_correct(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '-')
			return (-1);
		i++;
	}
	return (0);
}

int		reg_is_correct(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int		check_op_tab(int index_op, int nb_arg, int type, const t_op *op_tab)
{
	if ((op_tab[index_op].arg[nb_arg] & type) == 0)
	{
		puterr_noend("Invalid parameter type ");
		puterr_noend(ft_itoa(nb_arg));
		puterr_noend(" for instruction ");
		puterr(op_tab[index_op].name);
		return (-1);
	}
	return (0);
}

int		arg_is_reg(char *str, int index_op, int nb_arg, const t_op *op_tab)
{
	if (str[0] == 'r')
	{
		if (ft_strlen((str + 1)) >= 3)
		{
			puterr_noend("Syntax error at token instruction ");
			return (puterr(str));
		}
		if (reg_is_correct(str + 1) == -1)
		{
			puterr_noend("Syntax error at token instruction ");
			return (puterr(str));
		}
		if (check_op_tab(index_op, nb_arg, T_REG, op_tab) == -1)
			return (-1);
	}
	return (0);
}

int		arg_is_direct(char *str, int index_op, int nb_arg, const t_op *op_tab)
{
	if (str[0] == '%')
	{
		if (str[1])
		{
			if (str[1] == ':')
			{
				if (arg_is_labelchar(str + 2) == -1)
				{
					puterr_noend("Lexical error ");
					return (puterr(str));
				}
			}
			else
			{
				if (direct_is_correct(str + 1) == -1)
				{
					puterr_noend("Lexical error ");
					return (puterr(str));
				}
			}
		}
		if (check_op_tab(index_op, nb_arg, T_DIR, op_tab) == -1)
			return (-1);
	}
	return (0);
}
