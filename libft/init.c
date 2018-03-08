/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:25:33 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/06 19:27:21 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

void			reset_flag(t_dt *dt)
{
	int			i;

	i = 0;
	while (i <= 126)
	{
		dt->tab_f[i] = 0;
		++i;
	}
	dt->full_flag = NULL;
	dt->width = 0;
	dt->preci = 0;
	dt->conv = 0;
	dt->prec = 0;
	dt->cz = -1;
}

int				init_flag(t_dt *dt)
{
	if ((dt->all_conv = ft_strdup("spdDioOuUxXcCS%")) == NULL)
		return (-1);
	if ((dt->all_attr = ft_strdup("#+-0 ")) == NULL)
		return (-1);
	if ((dt->all_modif_conv = ft_strdup("hljz")) == NULL)
		return (-1);
	return (0);
}
