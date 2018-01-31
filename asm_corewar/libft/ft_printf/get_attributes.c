/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:05:06 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/15 23:24:10 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		get_attributes(const char *restrict format, int *n,
				t_data *data)
{
	int		index;
	t_param	*param;

	param = &data->param;
	while ((index = get_index(format[*n], ATTRIBUTES)) != -1)
	{
		if (format[*n] == '#')
			param->att.ashtag = ENABLED;
		else if (format[*n] == '0' && param->att.minus == DISABLED)
			param->att.zero = ENABLED;
		else if (format[*n] == '-')
		{
			param->att.minus = ENABLED;
			param->att.zero = DISABLED;
		}
		else if (format[*n] == '+')
		{
			param->att.plus = ENABLED;
			param->att.space = DISABLED;
		}
		else if (format[*n] == ' ' && param->att.plus == DISABLED)
			param->att.space = ENABLED;
		*n += 1;
	}
}
