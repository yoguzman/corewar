/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_check_instr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:45:41 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/08 15:45:10 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"

int				arg_is_labelchar(char *arg)
{
	char		*str;
	int			i;
	int			j;
	int			good;

	i = 0;
	str = LABEL_CHARS;
	while (arg[i])
	{
		j = 0;
		good = 0;
		while (str[j])
		{
			if (arg[i] == str[j])
				good = 1;
			j++;
		}
		if (good == 0)
			return (-1);
		i++;
	}
	return (0);
}

int				arg_is_number(char *arg)
{
	int			i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0 && arg[i] != '-')
			return (-1);
		i++;
	}
	return (0);
}

int				check_name(char *str, const t_op *op_tab)
{
	int			i;

	i = 0;
	while (i < 16)
	{
		if (ft_strcmp(str, op_tab[i].name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int				check_nb_arg(char **str, int index_op, const t_op *op_tab)
{
	int			i;

	i = 1;
	while (str[i])
		i++;
	i -= 1;
	if (i != op_tab[index_op].parameter_count)
		return (-1);
	return (0);
}

void			epur_space(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			str[i] = 0;
		++i;
	}
}
