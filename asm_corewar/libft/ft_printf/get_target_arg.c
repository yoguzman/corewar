/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_target_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:03:52 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/15 22:28:17 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			get_target_arg(const char *restrict format, int *n,
				t_data *data)
{
	int		c;
	int		index;

	c = *n;
	while (format[c] >= '0' && format[c] <= '9')
		c++;
	if (format[c] == '$')
	{
		if ((index = get_nb((char*)&format[*n])) == 0)
			return (ft_put_err("Position arguments start counting at one"));
		*n = c + 1;
		data->param.target = index;
	}
	return (0);
}
