/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:43:38 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/23 22:16:50 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		ft_free_2d_tab(void **tab, int free_big)
{
	int		n;

	n = 0;
	if (!tab)
		return ;
	while (tab[n])
	{
		free(tab[n]);
		n++;
	}
	if (free_big)
		free(tab);
}
