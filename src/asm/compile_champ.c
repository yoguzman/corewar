/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 05:08:25 by adauchy           #+#    #+#             */
/*   Updated: 2018/03/22 17:24:00 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "asm.h"

int				get_file2(char *new, int *dest)
{
	if ((*dest = open(new, O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR)) == -1)
		return (ft_puterr("Open failed"));
	return (0);
}

static int		get_file(char *name)
{
	int			dest;

	if (get_file2(name, &dest) == -1)
		return (-1);
	return (dest);
}

char			*create_new_file(char *name)
{
	char		*new;
	int			n;
	int			m;

	if (!ft_strstr(name, ".s"))
	{
		if ((new = ft_strdup(".cor")) == NULL)
			return ((char *)ft_puterr_null("Malloc fail in func get_file\n"));
	}
	else
	{
		n = 0;
		while (name[n])
			n += 1;
		while (n >= 0 && name[n] != '.')
			n -= 1;
		m = n;
		if (!(new = (char*)malloc(n + 5)))
			return (ft_puterr_null("malloc failed"));
		while (n--)
			new[n] = name[n];
		ft_strcpy(&new[m], ".cor");
	}
	return (new);
}

int				compile_champ(t_header *champ, char *name, t_list *inf_line)
{
	int			dest;
	char		*new_file;

	if ((new_file = create_new_file(name)) == NULL)
		return (-1);
	if ((dest = get_file(new_file)) == -1)
		return (-1);
	write_int(dest, COREWAR_EXEC_MAGIC);
	write_string(dest, champ->prog_name, PROG_NAME_LENGTH + 4);
	write_int(dest, champ->prog_size);
	write_string(dest, champ->comment, COMMENT_LENGTH + 4);
	if (write_instr(inf_line, dest) == -1)
		return (-1);
	ft_putstr("Writing output program to ");
	ft_putstr(new_file);
	ft_putstr("\n");
	free(new_file);
	close(dest);
	return (0);
}
