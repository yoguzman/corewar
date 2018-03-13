#include <inttypes.h>
#include <limits.h>

int		lol()
{
	uint32_t j;
	uint32_t i = 0xFFFFFFFF;

	j = i;
	return (j);
}

int		main()
{

	int		j;
	printf("%d\n", lol());
	return (0);
}
