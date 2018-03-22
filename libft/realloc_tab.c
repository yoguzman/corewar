/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:35:03 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/14 18:35:08 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			**cpy_tab(char **tab, char **buff)
{
	int			i;

	i = 0;
	while (tab[i])
	{
		buff[i] = tab[i];
		++i;
	}
	buff[i] = NULL;
	free(tab);
	return (buff);
}

char			**realloc_tab(char **tab, char *str)
{
	char		**buff;
	int			i;

	if (tab == NULL)
	{
		if ((tab = malloc(sizeof(char *) * 2)) == NULL)
			return (ft_puterr_null("malloc fail in realloc_tab\n"));
		tab[0] = str;
		tab[1] = NULL;
	}
	else
	{
		i = 0;
		while (tab[i])
			++i;
		if ((buff = malloc(sizeof(char *) * (i + 2))) == NULL)
			return (ft_puterr_null("malloc fail in realloc_tab\n"));
		tab = cpy_tab(tab, buff);
		tab[i] = str;
		tab[i + 1] = NULL;
	}
	return (tab);
}
