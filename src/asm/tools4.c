/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:14:42 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/21 17:11:56 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"

int		print_error_label(char *str, int line)
{
	puterr_noend("Invalid label at token instruction ");
	puterr_noend(str);
	puterr_noend(" at instruction ");
	ft_putnbr(line);
	puterr_noend("\n");
	exit(EXIT_FAILURE);
}

int		print_error_name(char **t_str, int line, int i)
{
	puterr_noend("Invalid instruction at token instruction ");
	puterr_noend(t_str[i - 1]);
	puterr_noend(" at line ");
	ft_putnbr(line);
	puterr_noend("\n");
	exit(EXIT_FAILURE);
}

int		print_error_nb_arg(char *instr, int line)
{
	ft_puterr(instr);
	puterr_noend("At line ");
	ft_putnbr(line);
	puterr_noend(" ");
	puterr(ERR_ARG);
	exit(EXIT_FAILURE);
}

int		julien_pu_le_caca(char *str, int i)
{
	if (str[i] == ':')
	{
		if (arg_is_labelchar(str + i + 1) == -1)
		{
			puterr_noend("Lexical error ");
			puterr(str);
			exit(0);
		}
	}
	else
	{
		if (direct_is_correct(str + i) == -1)
		{
			puterr_noend("Lexical error ");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

void	free_line_head_and_incr(char **line, int *i)
{
	free(*line);
	*line = NULL;
	++*i;
}
