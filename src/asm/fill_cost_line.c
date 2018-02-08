#include "asm.h"

static const t_cost    cost_tab[17] =
{
	{"live", &live_cost},
	{"ld", &ld_cost},
	{"st", &st_cost},
	{"add", &add_cost},
	{"sub", &sub_cost},
	{"and", &and_cost},
	{"or", &or_cost},
	{"xor", &xor_cost},
	{"zjmp", &zjmp_cost},
	{"ldi", &ldi_cost},
	{"sti", &sti_cost},
	{"fork", &fork_cost},
	{"lld", &lld_cost},
	{"lldi", &lldi_cost},
	{"lfork", &lfork_cost},
	{"aff", &aff_cost},
	{0, 0}
};

void		live_cost(t_if *info_line)
{
	info_line->cost_line = 5;
}

void		ld_cost(t_if *info_line)
{
	info_line->cost_line = 3;
	if (info_line->arg[0][0] == '%')
		info_line->cost_line += 4;
	else
		info_line->cost_line += 2;
}

void		st_cost(t_if *info_line)
{
	info_line->cost_line = 3;
	if (info_line->arg[1][0] == 'r')
		info_line->cost_line += 1;
	else
		info_line->cost_line += 2;
}

void		add_cost(t_if *info_line)
{
	info_line->cost_line = 5;
}
void		sub_cost(t_if *info_line)
{
	info_line->cost_line = 5;
}

void		and_cost(t_if *info_line)
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

void		or_cost(t_if *info_line)
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

void		xor_cost(t_if *info_line)
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
void		zjmp_cost(t_if *info_line)
{
	info_line->cost_line = 3;
}
void		ldi_cost(t_if *info_line)
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

void		sti_cost(t_if *info_line)
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

void		fork_cost(t_if *info_line)
{
	info_line->cost_line = 3;
}

void		lld_cost(t_if *info_line)
{
	info_line->cost_line = 3;
	if (info_line->arg[0][0] == '%')
		info_line->cost_line += 4;
	else
		info_line->cost_line += 2;
}
void		lldi_cost(t_if *info_line)
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

void		lfork_cost(t_if *info_line)
{
	info_line->cost_line = 3;
}

void		aff_cost(t_if *info_line)
{
	info_line->cost_line = 3;
}

int			fill_cost_line(t_if *info_line)
{
	int		i;

	i = 0;
	while (cost_tab[i].name)
	{
		if (ft_strcmp(cost_tab[i].name, info_line->name_instr) == 0)
		{
			cost_tab[i].f(info_line);
			return (0);
		}
		++i;
	}
	return (-1);
}
