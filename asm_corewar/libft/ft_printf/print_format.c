/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 09:10:24 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/23 17:52:23 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			print_format(t_data *data, const char *restrict format)
{
	int		n;
	int		index;
	int		ret;

	n = 0;
	while (format[n])
	{
		if (format[n] == '%')
		{
			n += 1;
			ret = 0;
			reset_data(data);
			if (get_param(format, &n, data) == -1)
				return (-1);
			index = get_index(data->param.conv, CONVERSIONS);
			if (data->param.conv &&
				(ret = data->tab_conv[index](&data->param, &data->arg)) == -1)
				return (-1);
			data->nb_carac += ret;
		}
		else if ((data->nb_carac += 1))
			write(1, &format[n++], 1);
	}
	return (0);
}
