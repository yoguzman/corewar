#include "vm.h"

void			key_action(t_corewar *vm)
{
	int		ret;

	ret = 0;
	attron(A_BOLD);
	attron(COLOR_PAIR(6));
	ret = getch();
	if (ret == ' ' && vm->paused == 1)
	{
		mvprintw(2, 199, "** RUNNING **");
		vm->paused = 0;
	}
	else if (ret == ' ' && vm->paused == 0)
	{
		mvprintw(2, 199, "** PAUSED **");
		vm->paused = 1;
	}
	else if (ret == ',')
	{
		if (vm->dec_sec > 10)
			vm->dec_sec -= 10;
		vm->cycles_sec = 1000000 / vm->dec_sec;
		mvprintw(4, 199 + 22, "%-4d", vm->dec_sec);
	}
	else if (ret == '.')
	{
		if (vm->dec_sec < 1000)
			vm->dec_sec += 10;
		vm->cycles_sec = 1000000 / vm->dec_sec;
		mvprintw(4, 199 + 22, "%-4d", vm->dec_sec);
	}
	else if (ret == 's')
	{
		vm->paused = 1;
		mvprintw(2, 199, "** PAUSED **");
		vm->one_cycle = 1;
	}
	attron(A_BOLD);
}
