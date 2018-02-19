#include "asm.h"

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
