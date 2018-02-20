/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 22:13:02 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 09:40:36 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**get_input(int fd, int nb_lines)
{
	char		**input;
	int			n;
	char		*line;
	int			ret;

	n = 0;
	if (!(input = (char**)malloc((nb_lines + 1) * sizeof(char*))))
	{
		ft_puterr("malloc failed");
		return (NULL);
	}
	while (n < nb_lines && (ret = get_next_line(fd, &line)) >= 1)
	{
		input[n] = line;
		n += 1;
	}
	input[n] = NULL;
	if (ret == -1)
	{
		ft_puterr("get_next_line failed");
		return (NULL);
	}
	close(fd);
	return (input);
}
