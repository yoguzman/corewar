/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_champ2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 16:02:00 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/08 16:30:09 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

static const char	*g_print_tab[16] =
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

void					print_header_a(t_header *champ)
{
	ft_putstr("Dumping annotated program on standard output\n");
	printf("Program size : %d bytes\n", champ->prog_size);
	printf("Name : \"%s\"\n", champ->prog_name);
	printf("Comment : \"%s\"\n\n", champ->comment);
}

void					print_arg(t_if *info)
{
	int					i;
	int					decal;

	i = 0;
	info->mask = 3;
	decal = 6;
	while (info->arg[i])
	{
		if (info->arg[i][0] == 'r' || info->arg[i][0] == '%')
			info->conv.nb = ft_atoi((info->arg[i] + 1));
		else
			info->conv.nb = ft_atoi((info->arg[i]));
		ft_printf("%-18d", info->conv.nb);
		decal -= 2;
		++i;
	}
	printf("\n");
}

int						get_instruction_code(char *instruction)
{
	int					n;

	n = 0;
	while (n < 16)
	{
		if (!ft_strcmp(instruction, g_print_tab[n]))
			return (n);
		n += 1;
	}
	return (-1);
}

void					mabite(int buff, t_if *info)
{
	int j;

	j = buff;
	while (buff >= 0)
	{
		ft_printf("%-3d ", info->conv.nb_oct[buff]);
		--buff;
	}
	while (++j < 4)
		printf("%-4c", ' ');
}

void					print_oct_arg(t_if *info)
{
	int					i;
	int					buff;
	int					decal;

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
		mabite(buff, info);
		ft_printf("  ");
		decal -= 2;
		++i;
	}
	ft_printf("\n");
}
