/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_integer_table.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 01:53:43 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:39:08 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_sort_integer_table(int *tab, int size)
{
	int		count;
	int		status;
	int		tmp;

	count = 0;
	status = 1;
	while (status == 1)
	{
		status = 0;
		count = 0;
		while (count < size - 1)
		{
			if (tab[count] > tab[count + 1])
			{
				status = 1;
				tmp = tab[count];
				tab[count] = tab[count + 1];
				tab[count + 1] = tmp;
			}
			count++;
		}
	}
}
