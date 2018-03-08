/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_instr1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:52:12 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/08 15:55:40 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "asm.h"

void		write_short(int fd, unsigned short nb)
{
	unsigned char	byte;

	byte = (unsigned char)(nb >> 8);
	write(fd, &byte, 1);
	byte = (unsigned char)nb;
	write(fd, &byte, 1);
}

char		mateub(int *i, char op_code, char **arg, int nb_arg)
{
	while (*i < nb_arg)
	{
		if (arg[*i][0] == '%')
		{
			op_code = op_code << 2;
			op_code += 2;
		}
		else if (arg[*i][0] == 'r')
		{
			op_code = op_code << 2;
			op_code += 1;
		}
		else
		{
			op_code = op_code << 2;
			op_code += 3;
		}
		++*i;
	}
	return (op_code);
}

void		write_op_code(char **arg, int nb_arg, int dest)
{
	int		i;
	char	op_code;

	i = 0;
	op_code = 0;
	op_code = mateub(&i, op_code, arg, nb_arg);
	while (i <= 3)
	{
		op_code = op_code << 2;
		++i;
	}
	ft_putchar_fd(op_code, dest);
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
