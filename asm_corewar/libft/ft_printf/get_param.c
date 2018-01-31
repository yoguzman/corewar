/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:10:55 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/22 15:45:54 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			get_param(const char *restrict format, int *n, t_data *data)
{
	if (get_target_arg(format, n, data) == -1)
		return (-1);
	get_attributes(format, n, data);
	if (get_field_width(format, n, data) == -1)
		return (-1);
	if (get_precision(format, n, data) == -1)
		return (-1);
	get_modifier(format, n, data);
	if (get_conversion(format, n, data) == -1)
		return (-1);
	get_overload(&data->param);
	return (0);
}
