/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_precision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 15:48:19 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/22 15:48:22 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				get_arg_precision(const char *restrict format,
				int *n, t_data *data)
{
	int			c;

	if (format[*n] == '*')
		*n += 1;
	else if (!(data->param.prec = 0))
		return (0);
	c = *n;
	if (format[c] == '0')
		return (ft_put_err("invalid prec"));
	while (format[c] >= '0' && format[c] <= '9')
		c++;
	if (c - *n && format[c++] == '$')
	{
		get_vararg(data, get_nb((char*)&format[*n]), SIGNED_NUMBER);
		if ((data->param.prec = (int)data->arg.si_nb) < 0)
			data->param.prec = -1;
		*n = c;
		return (0);
	}
	get_vararg(data, get_nb((char*)&format[*n]), SIGNED_NUMBER);
	if ((data->param.prec = data->arg.si_nb) < 0)
		data->param.prec = -1;
	return (0);
}

int				get_precision(const char *restrict format,
				int *n, t_data *data)
{
	int			c;

	if (format[*n] != '.')
		return (0);
	*n += 1;
	c = *n;
	while (format[c] >= '0' && format[c] <= '9')
		c++;
	if (c - *n)
	{
		data->param.prec = get_nb((char*)&format[*n]);
		*n = c;
		return (0);
	}
	return (get_arg_precision(format, n, data));
}
