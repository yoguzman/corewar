/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_modifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:08:43 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/15 17:35:59 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		get_modifier(const char *restrict format, int *n,
				t_data *data)
{
	if (format[*n] == 'h' && format[*n + 1] == 'h' && (*n += 2))
		data->param.modifier = HH;
	else if (format[*n] == 'l' && format[*n + 1] == 'l' && (*n += 2))
		data->param.modifier = LL;
	else if (get_index(format[*n], MODIFIERS) != -1)
	{
		data->param.modifier = format[*n];
		*n += 1;
	}
}
