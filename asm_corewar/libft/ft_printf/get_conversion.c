/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:11:05 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/23 13:44:21 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			get_conversion(const char *restrict format, int *n,
				t_data *data)
{
	int		type;

	type = 0;
	data->param.conv = format[*n];
	if (get_index(format[*n], SIGNED_NUMBERS) != -1)
		type = SIGNED_NUMBER;
	else if (get_index(format[*n], UNSIGNED_NUMBERS) != -1)
		type = UNSIGNED_NUMBER;
	else if (get_index(format[*n], POINTERS) != -1)
		type = POINTER;
	else if (get_index(format[*n], FLOATING_NUMBERS) != -1)
		type = FLOATING_NUMBER;
	if (type)
		get_vararg(data, data->param.target, type);
	else if (format[*n] && (data->param.conv = 'c'))
		data->arg.si_nb = format[*n];
	else if (!format[*n])
		data->param.conv = 0;
	if (format[*n] == 'n')
		data->arg.si_nb = data->nb_carac;
	if (format[*n])
		*n += 1;
	return (0);
}
