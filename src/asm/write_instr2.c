#include "asm.h"

void		live_write(t_if *info_line, int dest)
{
	int		nb;

	nb = ft_atoi(info_line->arg[0] + 1);
	ft_putchar_fd(1, dest);
	write_int(dest, nb);
}

void		ld_write(t_if *info_line, int dest)
{
	ft_putchar_fd(2, dest);
	write_op_code(info_line->arg, 2, dest);
	if (info_line->arg[0][0] == '%')
		write_int(dest, ft_atoi(info_line->arg[0] + 1));
	else
		write_short(dest, ft_atoi(info_line->arg[0]));
	ft_putchar_fd(ft_atoi(info_line->arg[1] + 1), dest);
}

void		st_write(t_if *info_line, int dest)
{
	ft_putchar_fd(3, dest);
	write_op_code(info_line->arg, 2, dest);
	ft_putchar_fd(ft_atoi(info_line->arg[0] + 1), dest);
	if (info_line->arg[1][0] == 'r')
		ft_putchar_fd(ft_atoi(info_line->arg[1] + 1), dest);
	else
		write_short(dest, ft_atoi(info_line->arg[1]));
}

void		add_write(t_if *info_line, int dest)
{
	ft_putchar_fd(4, dest);
	write_op_code(info_line->arg, 3, dest);
	ft_putchar_fd(ft_atoi(info_line->arg[0] + 1), dest);
	ft_putchar_fd(ft_atoi(info_line->arg[1] + 1), dest);
	ft_putchar_fd(ft_atoi(info_line->arg[2] + 1), dest);
}

void		sub_write(t_if *info_line, int dest)
{
	ft_putchar_fd(5, dest);
	write_op_code(info_line->arg, 3, dest);
	ft_putchar_fd(ft_atoi(info_line->arg[0] + 1), dest);
	ft_putchar_fd(ft_atoi(info_line->arg[1] + 1), dest);
	ft_putchar_fd(ft_atoi(info_line->arg[2] + 1), dest);
}
