/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 15:37:31 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/21 19:21:50 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"

int		direct_is_correct(char *str)
{
	int i;

	i = 0;
	if (str[0] == '-')
		++i;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			exit(EXIT_FAILURE);
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
			exit(EXIT_FAILURE);
		i++;
	}
	return (0);
}

int		check_op_tab(int index_op, int nb_arg, int type, const t_op *op_tab)
{
	if ((op_tab[index_op].parameter_types[nb_arg] & type) == 0)
	{
		puterr_noend("Invalid parameter ");
		ft_putnbr(nb_arg + 1);
		puterr_noend(" for instruction ");
		puterr(op_tab[index_op].name);
		exit(EXIT_FAILURE);
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
			exit(EXIT_FAILURE);
		}
		if (reg_is_correct(str + 1) == -1)
		{
			puterr_noend("Syntax error at token instruction ");
			exit(EXIT_FAILURE);
		}
		if (check_op_tab(index_op, nb_arg, T_REG, op_tab) == -1)
			exit(EXIT_FAILURE);
	}
	return (0);
}

int		arg_is_direct(char *str, int index_op, int nb_arg, const t_op *op_tab)
{
	int	i;
	int	type;

	i = 0;
	type = 4;
	if (str[0] == '%')
	{
		++i;
		type = 2;
	}
	if (str[i])
		if (julien_pu_le_caca(str, i) == -1)
			exit(EXIT_FAILURE);
	if (check_op_tab(index_op, nb_arg, type, op_tab) == -1)
		exit(EXIT_FAILURE);
	return (0);
}
