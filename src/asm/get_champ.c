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

int		get_header(char **file, t_header *header)
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
		return (ft_puterr("Program name need char between 1 to PROG_NAME_LENGTH\n"));
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

int		get_info_file(char **file, t_header *champ, t_list **inf_line)
{
	int		bytes;
	t_list	*tmp_list;
	t_if	info_line;
	t_if	*tmp;
	int	i;
	int		ret;

	if (get_header(file, champ) == -1)
		return (-1);
	i = 2;
	tmp = NULL;
	while (file[i])
	{
		ft_bzero(&info_line, sizeof(info_line));
		if ((file[i] = check_label(file[i], &info_line)) == NULL)
			return (-1);
		if (file[i][0] == 0 || check_blank_line(file[i]) == 0)
		{
			free(file[i]);
			++i;
			continue ;
		}
		if ((ret = pars_instr(file[i], &info_line, i + 1)) == -1)
			return (-1);
		else if (ret == 1)
			continue ;
		if (tmp == NULL)
			bytes = 0;
		else
			bytes += tmp->cost_line;
		fill_cost_line(&info_line);
		info_line.bytes_line = bytes;
		if (list_push_back_alloc_content(inf_line, &info_line, sizeof(t_if)) == -1)
			return (-1);
		tmp_list = *inf_line;
		while (tmp_list->next)
			tmp_list = tmp_list->next;
		tmp = (t_if *)tmp_list->content;
		++i;
	}
	return (tmp->bytes_line + tmp->cost_line);
}

int		get_champ(char *name, t_header *champ, t_list **inf_line)
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
