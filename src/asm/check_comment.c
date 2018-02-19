
#include "asm.h"
#include "libft.h"
#include "op.h"

int				check_comment(char **t_str)
{
	int			i;

	i = 0;
	while (t_str[i])
	{
		if (t_str[i][0] == '#')
		{
			if (t_str[i][1])
				t_str[i] = 0;
			else if (t_str[i + 1])
			{
				t_str[i] = 0;
				t_str[i + 1] = 0;
			}
			if (i == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int				check_comment2(char **t_str)
{
	int			onlycomment;
	int			i;
	int			j;

	onlycomment = 0;
	i = 0;
	while (t_str[i])
	{
		j = 0;
		while (t_str[i][j])
		{
			if (t_str[i][j] == '#')
			{
				t_str[i][j] = 0;
				if (t_str[i + 1])
					t_str[i + 1] = 0;
				if (i == 0)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
