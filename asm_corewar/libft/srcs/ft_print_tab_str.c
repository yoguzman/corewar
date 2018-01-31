/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:26:18 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:38:23 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		ft_print_tab_str(char **tab)
{
	int		count;

	count = 0;
	if (!tab)
		return ;
	while (tab[count])
	{
		ft_putstr(tab[count]);
		ft_putstr("\n");
		count++;
	}
}
