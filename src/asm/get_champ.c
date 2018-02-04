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

void	epur_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			str[i] = 0;
		++i;
	}
}

int		get_header(char **file, t_header *header)
{
	char	**tab;

	if ((tab = ft_strsplit(file[0], "\"")) == NULL)
		return (ft_puterr("function ft_split fail in get header\n"));
	epur_space(tab[0]);
	if (tab == NULL || tab[0] == NULL || ft_strcmp(tab[0], ".name"))
		return (ft_puterr(".name needed in header\n"));
	if (tab[1] == NULL || tab[2] != NULL)
		return (ft_puterr(".name needed just one name\n"));
	if (ft_strlen(tab[1]) > PROG_NAME_LENGTH || ft_strlen(tab[1]) < 1)
		return (ft_puterr("Prog name need char between 1 to PROG_NAME_LENGTH\n"));
	ft_strcpy(header->prog_name, tab[1]);
	free(tab[0]);
	free(tab);
	if ((tab = ft_strsplit(file[1], "\t\"")) == NULL)
		return (ft_puterr("function ft_split fail in get header\n"));
	epur_space(tab[0]);
	if (tab == NULL || tab[0] == NULL || ft_strcmp(tab[0], ".comment"))
		return (ft_puterr(".comment needed in header\n"));
	if (tab[1] == NULL || tab[2] != NULL)
	{
		ft_putstr(tab[1]);
		return (ft_puterr(".comment needed just one comment\n"));
	}
	if (ft_strlen(tab[1]) > COMMENT_LENGTH || ft_strlen(tab[1]) < 1)
		return (ft_puterr("Comment need char between 1 to COMMENT_LENGTH\n"));
	ft_strcpy(header->comment, tab[1]);
	free(tab[0]);
	free(tab);
	return (0);
}

int		get_info_file(char **file, t_header *champ, t_list **inf_line)
{
	if (get_header(file, champ) == -1)
		return (-1);
	return (0);
}

int		get_champ(char *name, t_header *champ, t_list **inf_line)
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
	if (get_info_file(file, champ, inf_line) == -1)
		return (-1);
	//champ->prog_size = ;
	return (0);
}
