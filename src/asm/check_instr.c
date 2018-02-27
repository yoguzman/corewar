/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 14:27:43 by jcoutare          #+#    #+#             */
/*   Updated: 2018/02/23 14:06:55 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"

static const t_op_a		g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2},
	{"st", 2, {T_REG, T_IND | T_REG}, 3},
	{"add", 3, {T_REG, T_REG, T_REG}, 4},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8},
	{"zjmp", 1, {T_DIR}, 9},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11},
	{"fork", 1, {T_DIR}, 12},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14},
	{"lfork", 1, {T_DIR}, 15},
	{"aff", 1, {T_REG}, 16},
	{0, 0, {0}, 0}
};

int				valid_arg(char *str, int index_op, int nb_arg)
{
	int			ret;

	if ((ret = arg_is_direct(str, index_op, nb_arg, g_op_tab)) < 0)
		return (ret);
	if ((ret = arg_is_reg(str, index_op, nb_arg, g_op_tab)) < 0)
		return (ret);
	return (0);
}

int				check_arg(char **t_str, int i_op, int i)
{
	int			ret;
	int			arg;

	arg = 0;
	while (t_str[i])
	{
		if ((ret = valid_arg(t_str[i], i_op, arg)) == -1)
			return (-1);
		else if (ret == -2)
			return (-1);
		arg++;
		i++;
	}
	return (0);
}

int				pars_instr(char *instr, t_if *info, int line)
{
	char		**t_str;
	int			i_op;
	int			i;

	i = 0;
	if (!(instr))
		return (puterr(ERR_INSTR_VIDE));
	if (!(t_str = ft_strsplit(instr, "\t ,")))
		return (puterr(ERR_SPLIT));
	if (ft_tablen(t_str) == 1)
		return (puterr("Syntax error at token ENDLINE"));
	if ((i_op = check_name(t_str[i++], g_op_tab)) == -1)
		return (print_error_name(t_str, line, i));
	if (check_nb_arg(t_str, i_op, g_op_tab) == -1)
		return (print_error_nb_arg(instr, line));
	if (check_arg(t_str, i_op, i) == -1)
		return (-1);
	if ((info->name_instr = ft_strdup(t_str[0])) == NULL)
		return (-1);
	i = 1;
	if ((info->arg = malloc(sizeof(char *) * 4)) == NULL)
		return (-1);
	while (t_str[i])
	{
		if ((info->arg[i - 1] = ft_strdup(t_str[i])) == NULL)
			return (-1);
		++i;
	}
	free(t_str[0]);
	free(t_str);
	info->arg[i - 1] = NULL;
	return (0);
}
