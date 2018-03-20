/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:49:28 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/08 15:50:49 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static const t_write	g_write_tab[17] =
{
	{"live", &live_write},
	{"ld", &ld_write},
	{"st", &st_write},
	{"add", &add_write},
	{"sub", &sub_write},
	{"and", &and_write},
	{"or", &or_write},
	{"xor", &xor_write},
	{"zjmp", &zjmp_write},
	{"ldi", &ldi_write},
	{"sti", &sti_write},
	{"fork", &fork_write},
	{"lld", &lld_write},
	{"lldi", &lldi_write},
	{"lfork", &lfork_write},
	{"aff", &aff_write},
	{0, 0}
};

void			aff_write(t_if *info_line, int dest)
{
	ft_putchar_fd(16, dest);
	write_op_code(info_line->arg, 1, dest);
	ft_putchar_fd(ft_atoi(info_line->arg[1] + 1), dest);
}

int				write_instr(t_list *inf_line, int dest)
{
	int			i;
	int			j;
	t_if		*info_line;

	j = 0;
	while (inf_line)
	{
		i = 0;
		info_line = (t_if *)inf_line->content;
		if (is_label(info_line, inf_line, j) == -1)
			return (-1);
		++j;
		while (g_write_tab[i].name)
		{
			if (info_line->name_instr)
				if (ft_strcmp(g_write_tab[i].name, info_line->name_instr) == 0)
				{
					g_write_tab[i].f(info_line, dest);
					break ;
				}
			++i;
		}
		inf_line = inf_line->next;
	}
	return (0);
}
