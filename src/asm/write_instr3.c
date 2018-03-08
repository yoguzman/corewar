/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_instr3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:51:38 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/08 15:51:40 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		and_write(t_if *info_line, int dest)
{
	int		i;

	i = 0;
	ft_putchar_fd(6, dest);
	write_op_code(info_line->arg, 3, dest);
	while (i != 2)
	{
		if (info_line->arg[i][0] == 'r')
			ft_putchar_fd(ft_atoi(info_line->arg[i] + 1), dest);
		else if (info_line->arg[i][0] == '%')
			write_int(dest, ft_atoi(info_line->arg[i] + 1));
		else
			write_short(dest, ft_atoi(info_line->arg[i]));
		++i;
	}
	ft_putchar_fd(ft_atoi(info_line->arg[2] + 1), dest);
}

void		or_write(t_if *info_line, int dest)
{
	int		i;

	i = 0;
	ft_putchar_fd(7, dest);
	write_op_code(info_line->arg, 3, dest);
	while (i != 2)
	{
		if (info_line->arg[i][0] == 'r')
			ft_putchar_fd(ft_atoi(info_line->arg[i] + 1), dest);
		else if (info_line->arg[i][0] == '%')
			write_int(dest, ft_atoi(info_line->arg[i] + 1));
		else
			write_short(dest, ft_atoi(info_line->arg[i]));
		++i;
	}
	ft_putchar_fd(ft_atoi(info_line->arg[2] + 1), dest);
}

void		xor_write(t_if *info_line, int dest)
{
	int		i;

	i = 0;
	ft_putchar_fd(8, dest);
	write_op_code(info_line->arg, 3, dest);
	while (i != 2)
	{
		if (info_line->arg[i][0] == 'r')
			ft_putchar_fd(ft_atoi(info_line->arg[i] + 1), dest);
		else if (info_line->arg[i][0] == '%')
			write_int(dest, ft_atoi(info_line->arg[i] + 1));
		else
			write_short(dest, ft_atoi(info_line->arg[i]));
		++i;
	}
	ft_putchar_fd(ft_atoi(info_line->arg[2] + 1), dest);
}

void		zjmp_write(t_if *info_line, int dest)
{
	ft_putchar_fd(9, dest);
	write_short(dest, ft_atoi(info_line->arg[0] + 1));
}

void		ldi_write(t_if *info_line, int dest)
{
	int		i;

	i = 0;
	ft_putchar_fd(10, dest);
	write_op_code(info_line->arg, 3, dest);
	while (i != 2)
	{
		if (info_line->arg[i][0] == 'r')
			ft_putchar_fd(ft_atoi(info_line->arg[i] + 1), dest);
		else if (info_line->arg[i][0] == '%')
			write_short(dest, ft_atoi(info_line->arg[i] + 1));
		else
			write_short(dest, ft_atoi(info_line->arg[i]));
		++i;
	}
	ft_putchar_fd(ft_atoi(info_line->arg[2] + 1), dest);
}
