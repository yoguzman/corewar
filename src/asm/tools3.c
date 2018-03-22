/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:47:48 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/08 14:48:54 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int				to_neg(unsigned short neg)
{
	int			first_octet;
	int			second_octet;
	t_neg		lol;

	lol.neg = neg;
	first_octet = lol.bneg[0];
	second_octet = lol.bneg[1];
	lol.bneg[0] = second_octet + 1;
	lol.bneg[1] = first_octet;
	return (lol.neg);
}

void			puterr_size_header(char *msg_err, int i)
{
	ft_puterr("Syntax error line ");
	ft_putnbr_fd(i + 1, 2);
	ft_puterr(" This ");
	ft_puterr(msg_err);
	ft_puterr(" is too long\n");
	exit(EXIT_FAILURE);
}

void			puterr_header(char *msg_err, int i)
{
	ft_puterr("Syntax error line ");
	ft_putnbr_fd(i + 1, 2);
	ft_puterr(" INSTRUCTION  ");
	if (msg_err == NULL)
		ft_puterr("(null)");
	else
		ft_puterr(msg_err);
	ft_puterr("\n");
	exit(EXIT_FAILURE);
}

int				get_nb_lines(char *file)
{
	int			fd;
	int			count;
	char		*line;
	int			ret;

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

void			free_head(char **tab, char *line)
{
	free(tab[0]);
	free(tab);
	free(line);
}
