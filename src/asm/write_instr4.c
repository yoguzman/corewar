#include "asm.h"

void		sti_write(t_if *info_line, int dest)
{
	int		i;

	i = 1;
	ft_putchar_fd(11, dest);
	write_op_code(info_line->arg, 3, dest);
	ft_putchar_fd(ft_atoi(info_line->arg[0] + 1), dest);
	while (i != 3)
	{
		if (info_line->arg[i][0] == 'r')
			ft_putchar_fd(ft_atoi(info_line->arg[i] + 1), dest);
		else if (info_line->arg[i][0] == '%')
			write_short(dest, ft_atoi(info_line->arg[i] + 1));
		else
			write_short(dest, ft_atoi(info_line->arg[i]));
		++i;
	}
}

void		fork_write(t_if *info_line, int dest)
{
	ft_putchar_fd(12, dest);
	write_short(dest, ft_atoi(info_line->arg[0] + 1));
}

void		lld_write(t_if *info_line, int dest)
{
	ft_putchar_fd(13, dest);
	write_op_code(info_line->arg, 2, dest);
	if (info_line->arg[0][0] == '%')
		write_int(dest, ft_atoi(info_line->arg[0] + 1));
	else
		write_short(dest, ft_atoi(info_line->arg[0]));
	ft_putchar_fd(ft_atoi(info_line->arg[1] + 1), dest);
}

void		lldi_write(t_if *info_line, int dest)
{
	int		i;

	i = 0;
	info_line->cost_line = 3;
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

void		lfork_write(t_if *info_line, int dest)
{
	ft_putchar_fd(15, dest);
	write_short(dest, ft_atoi(info_line->arg[0] + 1));
}
