/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_field_width.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:06:09 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/15 23:20:52 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			get_arg_field_width(const char *restrict format,
			int *n, t_data *data)
{
	int		c;
	int		*field_width;

	field_width = &data->param.field_width;
	if (format[*n] == '*')
		*n += 1;
	else
		return (0);
	c = *n;
	if (format[c] == '0')
		return (ft_put_err("invalid field width"));
	while (format[c] >= '0' && format[c] <= '9')
		c++;
	if (c - *n && format[c++] == '$')
	{
		get_vararg(data, get_nb((char*)&format[*n]), SIGNED_NUMBER);
		*field_width = (int)data->arg.si_nb;
		*n = c;
		return (0);
	}
	get_vararg(data, 0, SIGNED_NUMBER);
	*field_width = (int)data->arg.si_nb;
	return (0);
}

int			get_field_width(const char *restrict format, int *n, t_data *data)
{
	int		c;
	int		*field_width;

	field_width = &data->param.field_width;
	c = *n;
	if (format[c] == '0')
		return (0);
	while (format[c] >= '0' && format[c] <= '9')
		c++;
	if (c - *n)
	{
		*field_width = get_nb((char*)&format[*n]);
		*n = c;
		return (0);
	}
	return (get_arg_field_width(format, n, data));
}
