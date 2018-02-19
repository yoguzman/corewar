#include "asm.h" 

static const t_write    write_tab[17] =
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

int			modif_label(t_if *here, char *str_tmp, int i[3], t_list *tmp)
{
	char	*save;
	t_if	*inf;

	inf = (t_if *)tmp->content;
	if (inf->label != NULL && (ft_strcmp(inf->label,
								here->arg[i[1]] + 1 + i[0]) == 0))
	{
		if ((here->arg[i[1]] =
				ft_itoa(inf->bytes_line - here->bytes_line)) == NULL)
			return (-1);
		if (str_tmp[0] == '%')
		{
			str_tmp[1] = 0;
			if ((save = ft_strjoin(str_tmp, here->arg[i[1]])) == NULL)
				return (-1);
			here->arg[i[1]] = save;
		}
		return (1);
	}
	return (0);
}

t_list		*go_first(t_list *list)
{
	while (list->prev)
		list = list->prev;
	return (list);
}

int			is_label(t_if *here, t_list *list)
{
	char	*str_tmp;
	t_list	*tmp;
	int		i[3];

	ft_bzero(i, 12);
	while (here->arg[i[1]])
	{
		str_tmp = here->arg[i[1]];
		if (here->arg[i[1]][0] == '%')
			i[0] += 1;
		if (here->arg[i[1]][i[0]] == ':')
		{
			tmp = go_first(list);
			while (tmp)
			{
				if ((i[2] = modif_label(here, str_tmp, i, tmp)) == -1)
					return (-1);
				else if (i[2] == 1)
					break ;
				tmp = tmp->next;
			}
		}
		++i[1];
	}
	return (0);
}

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

void		aff_write(t_if *info_line, int dest)
{
	ft_putchar_fd(16, dest);
	write_op_code(info_line->arg, 1, dest);
	ft_putchar_fd(ft_atoi(info_line->arg[1] + 1), dest);
}
int		write_instr(t_list *inf_line, int dest)
{
	int		i;
	t_if	*info_line;

	while (inf_line)
	{
		i = 0;
		info_line = (t_if *)inf_line->content;
		if (is_label(info_line, inf_line) == -1)
			return (-1);
		while (write_tab[i].name)
		{
			if (ft_strcmp(write_tab[i].name, info_line->name_instr) == 0)
			{
				write_tab[i].f(info_line, dest);
				break ;
			}
			++i;
		}
		inf_line = inf_line->next;
	}
	return (0);
}
