/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:26:10 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:38:19 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		ft_print_tab_int(int **tab, int height, int lenght)
{
	int		h;
	int		l;

	h = 0;
	while (h < height)
	{
		l = 0;
		while (l < lenght)
		{
			ft_putnbr(tab[h][l]);
			ft_putchar(' ');
			l++;
		}
		ft_putchar('\n');
		h++;
	}
}
