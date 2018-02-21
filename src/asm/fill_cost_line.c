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
