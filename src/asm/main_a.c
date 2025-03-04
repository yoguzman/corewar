/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 21:29:31 by adauchy           #+#    #+#             */
/*   Updated: 2018/03/08 15:30:38 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "asm.h"

void			get_a_flag(int ac, char **av, int *file, int *a_flag)
{
	int			n;

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

void			free_lesbails(t_list *inf_line)
{
	t_list		*tmp;
	t_if		*blbl;
	int			i;
	int			j;

	j = 0;
	while (inf_line)
	{
		tmp = inf_line->next;
		blbl = inf_line->content;
		free(blbl->label);
		free(blbl->name_instr);
		i = 0;
		if (blbl->arg)
			while (blbl->arg[i])
			{
				free(blbl->arg[i]);
				++i;
			}
		free(blbl->arg);
		free(blbl);
		free(inf_line);
		inf_line = tmp;
		++j;
	}
}

int				main(int ac, char **av)
{
	t_header	champ;
	int			a_flag;
	int			file;
	t_list		*inf_line;

	if (ac == 1)
		return (print_usage());
	inf_line = NULL;
	get_a_flag(ac, av, &file, &a_flag);
	if (!file)
		return (ft_puterr("Can't read source file (null)\n"));
	if (get_champ(av[file], &champ, &inf_line) == -1)
		return (-1);
	if (a_flag)
	{
		if (print_champ(&champ, inf_line) == -1)
			return (-1);
	}
	else if (compile_champ(&champ, av[file], inf_line) == -1)
		return (-1);
	free_lesbails(inf_line);
	return (0);
}
