#include "asm.h"

static const t_cost    write_tab[17] =
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

void		live_write(t_if *info_line)
{
	info_line->cost_line = 5;
}

void		ld_write(t_if *info_line)
{
	info_line->cost_line = 3;
	if (info_line->arg[0][0] == '%')
		info_line->cost_line += 4;
	else
		info_line->cost_line += 2;
}

void		st_write(t_if *info_line)
{
	info_line->cost_line = 3;
	if (info_line->arg[1][0] == 'r')
		info_line->cost_line += 1;
	else
		info_line->cost_line += 2;
}

void		add_write(t_if *info_line)
{
	info_line->cost_line = 5;
}
void		sub_write(t_if *info_line)
{
	info_line->cost_line = 5;
}

void		and_write(t_if *info_line)
{
	int		i;

	i = 0;
	info_line->cost_line = 3;
	while (i != 2)
	{
		if (info_line->arg[i][0] == 'r')
			info_line->cost_line += 1;
		else if (info_line->arg[i][0] == '%')
			info_line->cost_line += 4;
		else
			info_line->cost_line += 2;
		++i;
	}
}

void		or_write(t_if *info_line)
{
	int		i;

	i = 0;
	info_line->cost_line = 3;
	while (i != 2)
	{
		if (info_line->arg[i][0] == 'r')
			info_line->cost_line += 1;
		else if (info_line->arg[i][0] == '%')
			info_line->cost_line += 4;
		else
			info_line->cost_line += 2;
		++i;
	}
}

void		xor_write(t_if *info_line)
{
	int		i;

	i = 0;
	info_line->cost_line = 3;
	while (i != 2)
	{
		if (info_line->arg[i][0] == 'r')
			info_line->cost_line += 1;
		else if (info_line->arg[i][0] == '%')
			info_line->cost_line += 4;
		else
			info_line->cost_line += 2;
		++i;
	}
}
void		zjmp_write(t_if *info_line)
{
	info_line->cost_line = 3;
}
void		ldi_write(t_if *info_line)
{
	int		i;

	i = 0;
	info_line->cost_line = 3;
	while (i != 2)
	{
		if (info_line->arg[i][0] == 'r')
			info_line->cost_line += 1;
		else if (info_line->arg[i][0] == '%')
			info_line->cost_line += 2;
		else
			info_line->cost_line += 2;
		++i;
	}
}

void		sti_write(t_if *info_line)
{
	int		i;

	i = 1;
	info_line->cost_line = 3;
	while (i != 3)
	{
		if (info_line->arg[i][0] == 'r')
			info_line->cost_line += 1;
		else if (info_line->arg[i][0] == '%')
			info_line->cost_line += 2;
		else
			info_line->cost_line += 2;
		++i;
	}
}

void		fork_write(t_if *info_line)
{
	info_line->cost_line = 3;
}

void		lld_write(t_if *info_line)
{
	info_line->cost_line = 3;
	if (info_line->arg[0][0] == '%')
		info_line->cost_line += 4;
	else
		info_line->cost_line += 2;
}
void		lldi_write(t_if *info_line)
{
	int		i;

	i = 0;
	info_line->cost_line = 3;
	while (i != 2)
	{
		if (info_line->arg[i][0] == 'r')
			info_line->cost_line += 1;
		else if (info_line->arg[i][0] == '%')
			info_line->cost_line += 4;
		else
			info_line->cost_line += 2;
		++i;
	}
}

void		lfork_write(t_if *info_line)
{
	info_line->cost_line = 3;
}

void		aff_write(t_if *info_line)
{
	info_line->cost_line = 3;
}
void		write_instr(t_list *inf_line)
{
	int		i;
	t_if	*info_line;

	i = 0;
	while (inf_line)
	{
		info_line = (t_if *)inf_line->content;
		while (cost_tab[i].name)
		{
			if (ft_strcmp(cost_tab[i].name, info_line->name_instr) == 0)
			{
				write_tab[i].f(info_line);
				break ;
			}
			++i;
		}
		inf_line = inf_line->next;
	}
	return (-1);
}
