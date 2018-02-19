/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 05:08:25 by adauchy           #+#    #+#             */
/*   Updated: 2018/02/16 16:49:45 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "asm.h"

static int	get_file(char *name)
{
	int		n;
	char	*new;
	int		dest;

	if (!ft_strstr(name, ".s"))
	{
		if ((new = ft_strdup(".cor")) == NULL)
			return (ft_puterr("Malloc fail in function get_file\n"));
	}
	else
	{
		n = 0;
		while (name[n] != '.')
			n += 1;
		if (!(new = (char*)malloc(n + 5)))
			return (ft_puterr("malloc failed"));
		n = -1;
		while (name[++n] != '.')
			new[n] = name[n];
		ft_strcpy(&new[n], ".cor");
	}
	if ((dest = open(new, O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR)) == -1)
		return (ft_puterr("Open failed"));
	ft_putstr("Writing output program to ");
	ft_putstr(new);
	ft_putstr("\n");
	free(new);
	return (dest);
}

int			compile_champ(t_header *champ, char *name, t_list *inf_line)
{
	int		dest;

	if ((dest = get_file(name)) == -1)
		return (-1);
	write_int(dest, COREWAR_EXEC_MAGIC);
	write_string(dest, champ->prog_name, PROG_NAME_LENGTH + 4);
	write_int(dest, champ->prog_size);
	write_string(dest, champ->comment, COMMENT_LENGTH + 4);
	if (write_instr(inf_line, dest) == -1)
		return (-1);
	return (0);
}
