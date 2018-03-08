/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 18:09:42 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/22 19:15:01 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	print_mem(void *mem, size_t mem_size)
{
	unsigned char	*a;

	a = (unsigned char *)mem;
	while (mem_size--)
	{
		if (*a < 32 || *a > 126)
		{
			ft_putchar('\\');
			ft_putchar('x');
			ft_putchar(DIGITS[*a >> 4]);
			ft_putchar(DIGITS[*a & 0xf]);
		}
		else
			ft_putchar(*a);
		++a;
	}
	ft_putchar('\n');
}
