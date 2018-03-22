/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:04:15 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/21 17:03:02 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

int			get_info_file_loop2(t_list **inf_line,
								t_if *info_line, t_if **tmp, int a)
{
	t_list	*tmp_list;

	info_line->bytes_line = a;
	if (list_push_back_alloc_content(inf_line, info_line, sizeof(t_if)) == -1)
		return (-1);
	tmp_list = *inf_line;
	while (tmp_list->next)
		tmp_list = tmp_list->next;
	*tmp = (t_if *)tmp_list->content;
	info_line->label = NULL;
	return (0);
}

int			del_comment_check(char *file)
{
	int		i;

	i = 0;
	while (file[i])
	{
		if (file[i] == '#')
			break ;
		i++;
	}
	if (file[i] == '#')
	{
		file[i] = 0;
		if (check_blank_line(file) == 0)
		{
			file[i] = '#';
			return (1);
		}
	}
	return (0);
}

int			del_comment(char *file)
{
	int		i;

	i = 0;
	while (file[i])
	{
		if (file[i] == '#')
		{
			file[i] = 0;
			return (0);
		}
		i++;
	}
	return (0);
}

int			get_info_file_loop(char **file, int *i, t_if *info_line)
{
	char	*tmp;

	tmp = file[*i];
	if (info_line->label == NULL)
		ft_bzero(info_line, sizeof(*info_line));
	if ((file[*i] = check_label(file[*i], info_line)) == NULL)
	{
		file[*i] = tmp;
		return (2);
	}
	if (del_comment(file[*i]) == 1 || file[*i][0] == 0 ||
			check_blank_line(file[*i]) == 0)
	{
		free(file[*i]);
		file[*i] = NULL;
		++*i;
		return (1);
	}
	if (pars_instr(file[*i], info_line, (*i) + 1) == -1)
		return (-1);
	return (0);
}

int			get_info_file_end(t_list **inf_line, t_if *info_line, t_if **tmp,
		int tab[2])
{
	if (info_line->label != NULL)
		if (get_info_file_loop2(inf_line, info_line, tmp, tab[1]) == -1)
			return (-1);
	if (*inf_line == NULL)
	{
		ft_printf("Champ need instruction\n");
		exit(0);
	}
	return (0);
}
