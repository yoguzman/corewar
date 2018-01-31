/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 05:03:44 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/30 06:42:33 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include <fcntl.h>
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

int		get_champ(char *name, t_header *champ)
{
	char	**file;
	int		nb_lines;
	int		fd;

	if ((fd = open(name, O_RDONLY)) == -1)
	{
		ft_puterr("Can't read source file ");
		ft_puterr(name);
		return (ft_puterr("\n"));
	}
	if ((nb_lines = get_nb_lines(name)) == -1)
		return (-1);
	if (!(file = get_input(fd, nb_lines)))
		return (-1);
//	champ->prog_name = ;
//	champ->comment = ;
//	champ->prog_size = 993;
	return (0);
}
