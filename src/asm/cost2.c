#include "asm.h"

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
