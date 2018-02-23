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

void		print_champ(t_header *champ, t_list *inf_line)
{
	t_if	*info;
	int		count;
	
	ft_putstr("Dumping annotated program on standard output\n");
	printf("Program size : %d bytes\n", champ->prog_size);
	printf("NAME : \"%s\"\n", champ->prog_name);
	printf("Comment : \"%s\"\n\n", champ->comment);
	while (inf_line)
	{
		info = (t_if*)(inf_line->content);
		if (info->label)
			printf("%-11d:    %s:\n", info->bytes_line, info->label);
		printf("%-5d(%-3d) :        %-10s", info->bytes_line,
				            info->cost_line, info->name_instr);
		count = -1;
		while (info->arg[++count])
			printf("%-18s", info->arg[count]);
		printf("\n");
		printf("%20s%-4d", " ", get_instruction_code(info->name_instr) + 1);
		if (ft_strcmp("live", info->name_instr) && ft_strcmp("zjmp", info->name_instr) &&
			ft_strcmp("fork", info->name_instr) && ft_strcmp("lfork", info->name_instr))
			printf("%-6d\n", get_op_code(info->arg));
		else
			printf("%6s\n", " ");
		printf("%20s%s\n", " ", "-------------------------");
		inf_line = inf_line->next;
		printf("\n");
	}
}
