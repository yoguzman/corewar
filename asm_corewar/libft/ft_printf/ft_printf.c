/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 10:17:19 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/23 18:18:57 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				ft_printf(const char *restrict format, ...)
{
	t_data		data;

	init_ft_printf(&data);
	va_start(data.ap, format);
	va_start(data.start, format);
	if (format && print_format(&data, format) == -1)
		return (-1);
	va_end(data.ap);
	va_end(data.start);
	return (data.nb_carac);
}
