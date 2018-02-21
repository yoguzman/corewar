/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_and_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 05:14:16 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/21 06:21:36 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "vm.h"

void	print_error_and_exit(const char *msg)
{
	if (msg)
	{
		ft_putstr_fd(ERR_STR, 2);
		ft_putendl_fd(msg, 2);
	}
	else
		perror(ERR_STR);
	exit(EXIT_FAILURE);
}
