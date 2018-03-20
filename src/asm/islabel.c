/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   islabel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:04:26 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/08 15:28:44 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			modif_label(t_if *here, char *str_tmp, int i[3], t_list *tmp)
{
	char	*save;
	t_if	*inf;

	inf = (t_if *)tmp->content;
	if (inf->label != NULL && (ft_strcmp(inf->label,
								here->arg[i[1]] + 1 + i[0]) == 0))
	{
		free(here->arg[i[1]]);
		if ((here->arg[i[1]] =
				ft_itoa(inf->bytes_line - here->bytes_line)) == NULL)
			return (-1);
		if (str_tmp[0] == '%')
		{
			str_tmp[1] = 0;
			if ((save = ft_strjoin(str_tmp, here->arg[i[1]])) == NULL)
				return (-1);
			free(here->arg[i[1]]);
			here->arg[i[1]] = save;
		}
		return (1);
	}
	return (0);
}

int			init_while_label(char **str_tmp, t_if *here, int i[3])
{
	if ((*str_tmp = ft_strdup(here->arg[i[1]])) == NULL)
		return (-1);
	i[0] = (here->arg[i[1]][0] == '%' ? i[0] + 1 : i[0]);
	return (0);
}

t_list		*go_first(t_list *list, char **str_tmp, t_if *here, int i[3])
{
	while (list->prev)
		list = list->prev;
	init_while_label(str_tmp, here, i);
	return (list);
}

int			is_label(t_if *here, t_list *list, int line)
{
	char	*str_tmp;
	t_list	*tmp;
	int		i[3];

	ft_bzero(i, 12);
	if (here->arg)
		while (here->arg[i[1]] && ((i[0] = 0) == 0))
		{
			tmp = go_first(list, &str_tmp, here, i);
			if (here->arg[i[1]][i[0]] == ':')
			{
				while (tmp)
				{
					if ((i[2] = modif_label(here, str_tmp, i, tmp)) == -1)
						return (-1);
					else if (i[2] == 1)
						break ;
					tmp = tmp->next;
				}
				if (tmp == NULL)
					return (print_error_label(here->name_instr, line));
			}
			free(str_tmp);
			++i[1];
		}
	return (0);
}
