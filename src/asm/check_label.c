/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:51:11 by jcoutare          #+#    #+#             */
/*   Updated: 2018/01/31 18:02:23 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"

char	*check_label(char *line, t_if *info_line)
{
	char *tmp;
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_isalpha(line[i]) == 0)
		{
			if (line[i] == ':')
			{
				if (!(info_line->label = ft_strsub(line, 0, i)))
					return (NULL);
				if (!(tmp = ft_strsub(line, i, ft_strlen(line))))
					return (NULL);
				free(line);
				return (tmp);
			}
			return (line);
		}
		i++;
	}
}
