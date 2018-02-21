/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 18:09:42 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/21 19:51:29 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	print_mem(unsigned char *mem, size_t mem_size)
{
	while (mem_size--)
	{
		if (*mem < 32 || *mem > 126)
		{
			ft_putchar('\\');
			ft_putchar('X');
			ft_putchar(DIGITS[*mem & 0XF]);
			ft_putchar(DIGITS[(*mem >> 4) & 0xFF]);
		}
		else
			ft_putchar(*mem);
		++mem;
	}
}
