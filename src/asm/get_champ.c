/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 05:03:44 by adauchy           #+#    #+#             */
/*   Updated: 2018/03/23 11:50:05 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include <fcntl.h>
#include "asm.h"

int			get_header(char **instr, t_header *header, int *i)
{
	if (instr[1] == NULL)
		puterr_header(NULL, *i);
	if (instr[2] != NULL &&
		(del_comment_check(instr[2]) == 1))
		puterr_header(instr[2], *i);
	if (ft_strcmp(instr[0], ".name") == 0)
	{
		if (ft_strlen(instr[1]) > PROG_NAME_LENGTH)
			puterr_size_header(instr[0], *i);
		ft_strcpy(header->prog_name, instr[1]);
	}
	else if (ft_strcmp(instr[0], ".comment") == 0)
	{
		if (ft_strlen(instr[1]) > COMMENT_LENGTH)
			puterr_size_header(instr[0], *i);
		ft_strcpy(header->comment, instr[1]);
	}
	return (0);
}

int			loop_get_header(char **file, t_header *header, int *i)
{
	char	**tab;

	ft_bzero(header->prog_name, PROG_NAME_LENGTH);
	ft_bzero(header->comment, COMMENT_LENGTH);
	while (file[*i] && (header->prog_name[0] == 0 || header->comment[0] == 0))
	{
		if (del_comment(file[*i]) == 1 || file[*i][0] == 0 ||
				check_blank_line(file[*i]) == 0)
		{
			free_line_head_and_incr(&(file[*i]), i);
			continue ;
		}
		if ((tab = ft_strsplit(file[*i], "\"")) == NULL)
			puterr_header(".name or .comment nedded in header", *i);
		epur_space(tab[0]);
		if (ft_strcmp(tab[0], ".name") == 0 ||
			ft_strcmp(tab[0], ".comment") == 0)
			get_header(tab, header, i);
		else
			puterr_header(tab[0], *i);
		free_head(tab, file[*i]);
		++*i;
	}
	return (0);
}

void		init_info_file(char **file, int *i, t_if **tmp, t_header *champ)
{
	*i = 0;
	if (loop_get_header(file, champ, i) == -1)
		exit(EXIT_FAILURE);
	*tmp = NULL;
}

int			get_info_file(char **file, t_header *champ, t_list **inf_line)
{
	int		tab[2];
	t_if	info_line;
	t_if	*tmp;
	int		i;

	init_info_file(file, &i, &tmp, champ);
	ft_bzero(&info_line, sizeof(info_line));
	while (file[i])
	{
		if ((tab[0] = get_info_file_loop(file, &i, &info_line)) == -1)
			return (-1);
		else if (tab[0] == 1)
			continue ;
		tab[1] = (tmp == NULL ? 0 : tab[1] + tmp->cost_line);
		fill_cost_line(&info_line);
		if (get_info_file_loop2(inf_line, &info_line, &tmp, tab[1]) == -1)
			return (-1);
		if (info_line.name_instr == NULL)
			continue ;
		free(file[i]);
		++i;
	}
	if (get_info_file_end(inf_line, &info_line, &tmp) == -1)
		return (-1);
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
	free(file);
	champ->prog_size = ret;
	return (0);
}
