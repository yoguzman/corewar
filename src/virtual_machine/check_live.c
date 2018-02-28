#include "vm.h"

void			check_live_process(t_mh *mh)
{
	uint64_t	i;

	i = 0;
	//while (i < mh->size)
	{
	//	if (mh->tab[i]->current_live == 0)
	//		destroy_process(mh_tab[i]);
	//	else
	//		mh->tab[i]->current_live = 0;
	//	++i;
	}
}

int				check_live_player(t_player player_table[MAX_PLAYERS])
{
	int			i;
	int			count_live;

	i = 0;
	count_live = 0;
	while (i < MAX_PLAYERS)
	{
		if (player_table[i].die == 0)
		{
			if (player_table[i].current_live == 0)
			{
				player_table[i].die = 1;
				continue ;
			}
			else
				count_live += player_table[i].current_live;
			player_table[i].current_live = 0;
		}
		++i;
	}
	return (count_live);
}

void		check_cycle_to_die(t_corewar *vm)
{
	int		ret;

//	if (vm->cycle_to_die == 0)
//	{
		ret = check_live_player(vm->player_table);
		//check_live_process(vm->mh); // a creer(check les lives et les resets a 0)
		if (ret >= NBR_LIVE)
			vm->cycle_to_die_max -= CYCLE_DELTA;
		vm->cycle_to_die = vm->cycle_to_die_max;
//	}
}
