/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:51:11 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/08 15:15:26 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"

int				ft_islabel(int c)
{
	char		*str;
	int			i;

	str = LABEL_CHARS;
	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char			*check_label(char *line, t_if *info_line, int j)
{
	char		*tmp;
	int			i;

	i = -1;
	while (line[++i])
	{
		if (ft_islabel(line[i]) == 0)
		{
			if (line[i] == ':')
			{
				if (info_line->label != NULL)
				{
					ft_printf("Redefinition Label in line %d", j);
					return (ft_puterr_null("\n"));
				}
				if (!(tmp = ft_strsub(line, i + 1, ft_strlen(line) - (i + 1)))
			|| (!(info_line->label = ft_strsub(line, 0, i))))
					return (NULL);
				free(line);
				return (tmp);
			}
			return (line);
		}
	}
	return (line);
}
