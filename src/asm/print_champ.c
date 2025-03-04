/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 05:06:41 by adauchy           #+#    #+#             */
/*   Updated: 2018/03/23 12:20:51 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

static unsigned char	get_op_code(char **arg)
{
	int					i;
	unsigned char		op_code;

	i = 0;
	op_code = 0;
	while (arg[i])
	{
		op_code = op_code << 2;
		if (arg[i][0] == '%')
			op_code += 2;
		else if (arg[i][0] == 'r')
			op_code += 1;
		else
			op_code += 3;
		i += 1;
	}
	while (i <= 3)
	{
		op_code = op_code << 2;
		i += 1;
	}
	return (op_code);
}

void					print_info_begin(t_if *info)
{
	int					count;

	if (info->label)
		ft_printf("%-11d:    %s:", info->bytes_line, info->label);
	if (info->name_instr == NULL)
		return ;
	ft_printf("\n%-5d(%-3d) :        %-10s", info->bytes_line,
			info->cost_line, info->name_instr);
	count = -1;
	if (info->arg)
		while (info->arg[++count])
			ft_printf("%-18s", info->arg[count]);
	ft_printf("\n");
	ft_printf("%20s%-4d", " ", get_instruction_code(info->name_instr) + 1);
}

int						truc(t_if *info)
{
	if (info->name_instr)
		if (ft_strcmp("live", info->name_instr)
				&& ft_strcmp("zjmp", info->name_instr) &&
				ft_strcmp("fork", info->name_instr) &&
				ft_strcmp("lfork", info->name_instr))
		{
			info->op_code = get_op_code(info->arg);
			ft_printf("%-6d", info->op_code);
			info->op_code = replace_cod_oct(info->op_code,
					get_instruction_code(info->name_instr));
			print_oct_arg(info);
			ft_printf("                    %-2d  %-6d",
					get_instruction_code(info->name_instr) + 1,
					get_op_code(info->arg));
			print_arg(info);
			return (1);
		}
	return (0);
}

void					print_info_arg(t_if *info)
{
	if (info->name_instr)
		if (truc(info) == 0)
		{
			ft_printf("%6s", " ");
			if (ft_strcmp("live", info->name_instr) == 0)
				info->op_code = (3 << 6);
			else
				info->op_code = (T_DIR << 6);
			print_oct_arg(info);
			ft_printf("                    %-2d  %-6s",
					get_instruction_code(info->name_instr) + 1, " ");
			print_arg(info);
		}
}

int						print_champ(t_header *champ, t_list *inf_line)
{
	t_if				*info;
	int					j;

	j = 0;
	print_header_a(champ);
	while (inf_line)
	{
		info = (t_if*)(inf_line->content);
		print_info_begin(info);
		if (is_label(info, inf_line, j) == -1)
			return (-1);
		++j;
		print_info_arg(info);
		inf_line = inf_line->next;
		ft_printf("\n");
	}
	return (0);
}
