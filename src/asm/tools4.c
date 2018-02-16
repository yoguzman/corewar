/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:14:42 by jcoutare          #+#    #+#             */
/*   Updated: 2018/02/16 16:24:51 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"

int		print_error_name(char **t_str, int line, int i)
{
	puterr_noend("Invalid instruction at token instruction ");
	puterr_noend(t_str[i - 1]);
	puterr_noend(" at line ");
	puterr(ft_itoa(line));
	return (-1);
}

int		print_error_nb_arg(char *instr, int line)
{
	ft_putstr(instr);
	puterr_noend("At line ");
	puterr_noend(ft_itoa(line));
	puterr_noend(" ");
	return (puterr(ERR_ARG));
}
