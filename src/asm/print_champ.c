/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 05:06:41 by adauchy           #+#    #+#             */
/*   Updated: 2018/02/23 07:25:00 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

static const char	*print_tab[16] =
{
	"live",
	"ld",
	"st",
	"add",
	"sub",
	"and",
	"or",
	"xor",
	"zjmp",
	"ldi",
	"sti",
	"fork",
	"lld",
	"lldi",
	"lfork",
	"aff"
};

static unsigned char	get_op_code(char **arg)
{
	int				i;
	unsigned char	op_code;

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

int			get_instruction_code(char *instruction)
{
	int		n;

	n = 0;
	while (n < 16)
	{
		if (!ft_strcmp(instruction, print_tab[n]))
			return (n);
		n += 1;
	}
	return (-1);
}

void		print_arg(t_if *info)
{
	int		i;
	int		decal;

	i = 0;
	info->mask = 3;
	decal = 6;
	while (info->arg[i])
	{
		if (info->arg[i][0] == 'r' || info->arg[i][0] == '%')
			info->conv.nb = ft_atoi((info->arg[i] + 1));
		else
			info->conv.nb = ft_atoi((info->arg[i]));
		printf("%-18d", info->conv.nb);
		decal -= 2;
		++i;
	}
	printf("\n");
}

void		print_oct_arg(t_if *info)
{
	int		i;
	int		buff;
	int		decal;
	int		j;

	i = 0;
	info->mask = 3;
	decal = 6;
	while (info->arg[i])
	{
		if ((buff = ((info->op_code >> decal) & info->mask)) == 0)
			break ;
		if (info->arg[i][0] == 'r' || info->arg[i][0] == '%')
			info->conv.nb = ft_atoi((info->arg[i] + 1));
		else
			info->conv.nb = ft_atoi((info->arg[i]));
		if (buff == 3)
			++buff;
		--buff;
		j = buff;
		while (buff >= 0)
		{
			printf("%-3d ", info->conv.nb_oct[buff]);
			--buff;
		}
		while (++j < 4)
			printf("%-4c", ' ');
		printf("  ");
		decal -= 2;
		++i;
	}
	printf("\n");
}

void		print_info_begin(t_if *info)
{
	int		count;

	if (info->label)
		printf("%-11d:    %s:\n", info->bytes_line, info->label);
	printf("%-5d(%-3d) :        %-10s", info->bytes_line,
			info->cost_line, info->name_instr);
	count = -1;
	while (info->arg[++count])
		printf("%-18s", info->arg[count]);
	printf("\n");
	printf("%20s%-4d", " ", get_instruction_code(info->name_instr) + 1);
}

void		print_header_a(t_header *champ)
{
	ft_putstr("Dumping annotated program on standard output\n");
	printf("Program size : %d bytes\n", champ->prog_size);
	printf("Name : \"%s\"\n", champ->prog_name);
	printf("Comment : \"%s\"\n\n", champ->comment);
}

void		print_info_arg(t_if *info)
{
	if (ft_strcmp("live", info->name_instr) && ft_strcmp("zjmp", info->name_instr) &&
			ft_strcmp("fork", info->name_instr) && ft_strcmp("lfork", info->name_instr))
	{
		info->op_code = get_op_code(info->arg);
		printf("%-6d", info->op_code);
		info->op_code = replace_cod_oct(info->op_code, get_instruction_code(info->name_instr));
		print_oct_arg(info);
		printf("                    %-2d  %-6d", get_instruction_code(info->name_instr) + 1, get_op_code(info->arg));
		print_arg(info);
	}
	else
	{
		printf("%6s", " ");
		if (ft_strcmp("live", info->name_instr) == 0)
			info->op_code = (3 << 6);
		else
			info->op_code = (T_DIR << 6);
		print_oct_arg(info);
		printf("                    %-2d  %-6s", get_instruction_code(info->name_instr) + 1, " ");
		print_arg(info);
	}
}

int			print_champ(t_header *champ, t_list *inf_line)
{
	t_if	*info;
	int		j;

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
		printf("\n");
	}
	return (0);
}
