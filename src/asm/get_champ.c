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

int			get_nb_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;
	int		ret;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	count = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		free(line);
		count += 1;
	}
	if (ret == -1)
		return (-1);
	close(fd);
	return (count);
}

int			get_header(char **file, t_header *header)
{
	char	**tab;

	if ((tab = ft_strsplit(file[0], "\"")) == NULL)
		return (ft_puterr("function ft_splited fail in get header\n"));
	epur_space(tab[0]);
	if (tab == NULL || tab[0] == NULL || ft_strcmp(tab[0], ".name"))
		return (ft_puterr(".name needed in header\n"));
	if (tab[1] == NULL || tab[2] != NULL)
		return (ft_puterr(".name needed just one name\n"));
	if (ft_strlen(tab[1]) > PROG_NAME_LENGTH || ft_strlen(tab[1]) < 1)
		return (ft_puterr("Name need char between 1 to PROG_NAME_LENGTH\n"));
	ft_strcpy(header->prog_name, tab[1]);
	free(tab[0]);
	free(tab);
	if ((tab = ft_strsplit(file[1], "\t\"")) == NULL)
		return (ft_puterr("function ft_split failed in get header\n"));
	epur_space(tab[0]);
	if (tab == NULL || tab[0] == NULL || ft_strcmp(tab[0], ".comment"))
		return (ft_puterr(".comment needed in header\n"));
	if (ft_strlen(tab[1]) > COMMENT_LENGTH || ft_strlen(tab[1]) < 1)
		return (ft_puterr("Comment need char between 1 to COMMENT_LENGTH\n"));
	ft_strcpy(header->comment, tab[1]);
	free(tab[0]);
	free(tab);
	return (0);
}

int			get_info_file(char **file, t_header *champ, t_list **inf_line)
{
	int		tab[2];
	t_list	*tmp_list;
	t_if	info_line;
	t_if	*tmp;
	int		i;

	if (get_header(file, champ) == -1)
		return (-1);
	free(file[0]);
	free(file[1]);
	i = 2; 
	tmp = NULL;
	tmp_list = NULL;
	while (file[i])
	{
		if ((tab[0] = get_info_file_loop(file, &i, &info_line)) == -1)
			return (-1);
		else if (tab[0] == 1)
			continue ;
		tab[1] = (tmp == NULL ? 0 : tab[1] + tmp->cost_line);
		fill_cost_line(&info_line);
		info_line.bytes_line = tab[1];
		if (get_info_file_loop2(&tmp_list, inf_line, &info_line, &tmp) == -1)
			return (-1);
		free(file[i]);
		++i;
	}
	free(file);
	return (tmp->bytes_line + tmp->cost_line);
}

int			get_champ(char *name, t_header *champ, t_list **inf_line)
{
	int		ret;
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
	if ((ret = get_info_file(file, champ, inf_line)) == -1)
		return (-1);
	champ->prog_size = ret;
	return (0);
}
