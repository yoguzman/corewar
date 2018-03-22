/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:49:18 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/08 14:49:20 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		print_usage(void)
{
	ft_putstr("Usage: ./asm [-a] <sourcefile.s>\n");
	ft_putstr("    -a : Instead of creating a .cor file, ");
	ft_putstr("outputs a stripped and annotated ");
	ft_putstr("version of the code to the standard output\n");
	return (-1);
}

int		check_blank_line(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 1)
			++count;
		++i;
	}
	if (count == i)
		return (0);
	return (1);
}

int		ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		puterr(char *str)
{
	ft_puterr(str);
	ft_puterr("\n");
	return (-1);
}

int		puterr_noend(char *str)
{
	ft_puterr(str);
	return (-1);
}
