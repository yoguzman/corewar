#include "op.h"
#include <inttypes.h>

void		reset_pc(uint32_t pc)
{
	int		buf;

	if (pc > MEM_SIZE - 1)
	{
		buf = pc - (MEM_SIZE - 1);
		buf -= 1;
	}
}
