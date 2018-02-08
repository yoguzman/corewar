/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 21:29:31 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/30 06:47:06 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "asm.h"

int		print_usage(void)
{
	ft_putstr("Usage: ./asm [-a] <sourcefile.s>\n");
	ft_putstr("    -a : Instead of creating a .cor file, ");
	ft_putstr("outputs a stripped and annotated ");
	ft_putstr("version of the code to the standard output\n");
	return (0);
}

void	get_a_flag(int ac, char **av, int *file, int *a_flag)
{
	int	n;

	n = 1;
	*a_flag = 0;
	while (n < ac)
	{
		if (!ft_strcmp(av[n], "-a"))
		{
			*a_flag = 1;
			break ;
		}
		n += 1;
	}
	n = ac - 1;
	while (n && !ft_strcmp(av[n], "-a"))
		n -= 1;
	*file = n;
}

void	free_champ(t_header *champ, t_list *inf_line)
{
	(void)champ;
}

int		main(int ac, char **av)
{
	t_header	champ;
	int		a_flag;
	int		file;
	t_list	*inf_line;

	if (ac == 1)
		return (print_usage());
	inf_line = NULL;
	get_a_flag(ac, av, &file, &a_flag);
	if (!file)
		return (ft_puterr("Can't read source file (null)\n"));
	if (get_champ(av[file], &champ, &inf_line) == -1)
		return (-1);
	if (a_flag)
		print_champ(&champ, inf_line);
	else if (compile_champ(&champ, av[file], inf_line) == -1)
		return (-1);
	free_champ(&champ, inf_line);
	return (0);
}
