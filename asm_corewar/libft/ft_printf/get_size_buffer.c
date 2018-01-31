/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:45:12 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/22 19:13:52 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			call_get_size_nb_base(unsigned long long nb, char flag)
{
	if (flag == 'o' || flag == 'O')
		return (get_size_nb_base(nb, "01234567"));
	if (flag == 'u' || flag == 'U')
		return (get_size_nb_base(nb, "0123456789"));
	if (flag == 'x' || flag == 'X')
		return (get_size_nb_base(nb, "0123456789abcdef"));
	return (0);
}

int			get_size_buffer_un_nb(unsigned long long nb,
				t_param *param, int *size)
{
	int		size_nb;

	size_nb = call_get_size_nb_base(nb, param->conv);
	*size = size_nb;
	if (param->prec > *size)
		*size = param->prec;
	if (!param->prec && !nb)
		*size = 0;
	if ((param->conv == 'o' || param->conv == 'O') &&
		((nb && param->att.ashtag &&
		!(param->att.zero && param->field_width > size_nb) &&
		!(param->prec > size_nb)) || (param->att.ashtag &&
		!nb && !param->prec)))
		*size += 1;
	if (nb && (param->conv == 'x' || param->conv == 'X') && param->att.ashtag)
		*size += 2;
	if (param->field_width > *size)
		return (param->field_width);
	return (*size);
}

int			get_size_buffer_nb(long long nb, t_param *param, int *size)
{
	*size = get_size_nb(nb);
	if (param->prec >= *size)
	{
		*size = param->prec;
		if (nb < 0)
			*size += 1;
	}
	if (!param->prec && !nb)
		*size = 0;
	if (param->att.space && nb >= 0)
		*size += 1;
	if (param->att.plus && nb >= 0)
		*size += 1;
	if (param->field_width > *size)
		return (param->field_width);
	return (*size);
}

int			get_size_buffer_u(int *str, t_param *param, int *size)
{
	int		count;

	*size = 0;
	count = 0;
	while ((param->prec == -1 || *size < param->prec) && str[count])
	{
		*size += get_size_unicode(str[count]);
		count += 1;
	}
	if (param->prec != -1 && *size > param->prec)
		*size = param->prec;
	if (param->field_width > *size)
		return (count + param->field_width - *size);
	return (*size);
}

int			get_size_buffer(char *str, t_param *param, int *size)
{
	int		count;

	count = 0;
	while ((param->prec == -1 || count < param->prec) && str[count])
		count++;
	*size = count;
	if (param->field_width > count)
		return (param->field_width);
	return (count);
}
