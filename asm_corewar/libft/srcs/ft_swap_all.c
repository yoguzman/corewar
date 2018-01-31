/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 06:57:32 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 05:10:01 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		ft_swap_all(void *a, void *b, int size)
{
	char	*char_a;
	char	*char_b;
	int		count;
	char	tmp;

	count = 0;
	char_a = (char*)a;
	char_b = (char*)b;
	while (count < size)
	{
		tmp = char_a[count];
		char_a[count] = char_b[count];
		char_b[count] = tmp;
		count += 1;
	}
}
