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

#include "asm.h"

int		print_usage(void)
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>\n");
	ft_printf("    -a : Instead of creating a .cor file, ");
	ft_printf("outputs a stripped and annotated ");
	ft_printf("version of the code to the standard output\n");
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

void	free_champ(t_champ champ)
{
	(void)champ;
}

int		main(int ac, char **av)
{
	t_champ	champ;
	int		a_flag;
	int		file;

	if (ac == 1)
		return (print_usage());
	get_a_flag(ac, av, &file, &a_flag);
	if (!file)
		return (ft_printf("Can't read source file (null)\n"));
	if (get_champ(av[file], &champ) == -1)
		return (-1);
	if (a_flag)
		print_champ(champ);
	else if (compile_champ(champ, av[file]) == -1)
		return (-1);
	free_champ(champ);
	return (0);
}
