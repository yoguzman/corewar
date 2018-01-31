/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 05:08:25 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/30 06:46:18 by adauchy          ###   ########.fr       */
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

void		write_int(int fd, unsigned int nb)
{
	unsigned char	byte;

	byte = (unsigned char)(nb >> 24);
	write(fd, &byte, 1);
	byte = (unsigned char)(nb >> 16);
	write(fd, &byte, 1);
	byte = (unsigned char)(nb >> 8);
	write(fd, &byte, 1);
	byte = (unsigned char)nb;
	write(fd, &byte, 1);
}

void		write_string(int fd, char *string, int size)
{
	int		n;

	n = ft_strlen(string);
	write(fd, string, n);
	while (n < size)
	{
		write(fd, "\0", 1);
		n += 1;
	}
}

int			compile_champ(t_header *champ, char *name)
{
	int		dest;

	(void)champ;
	if ((dest = get_file(name)) == -1)
		return (-1);
	write_int(dest, COREWAR_EXEC_MAGIC);
	write_string(dest, champ->prog_name, PROG_NAME_LENGTH + 4);
	write_int(dest, champ->prog_size);
	write_string(dest, champ->comment, COMMENT_LENGTH + 4);
	return (0);
}
