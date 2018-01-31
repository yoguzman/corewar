/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 05:03:44 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/31 15:54:02 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_nb_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;
	int		ret;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	count = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
		count += 1;
	if (ret == -1)
		return (-1);
	close(fd);
	return (count);
}

int		get_champ(char *name, t_champ *champ)
{
	char	**file;
	int		fd;
	int		nb_lines;

	if ((fd = open(name, O_RDONLY)) == -1 &&
		ft_printf("Can't read source file %s\n", name))
		return (-1);
	if ((nb_lines = get_nb_lines(name)) == -1)
		return (-1);
	if (!(file = get_input(fd, nb_lines)))
		return (-1);
	champ->prog_name = ft_strdup("42");
	champ->comment = ft_strdup("Just a basic Winner Program");
	champ->prog_size = 993;
	return (0);
}
