/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vararg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 14:54:42 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/18 20:22:10 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			recup_arg(va_list ap, int type, t_arg *arg)
{
	arg->type = type;
	if (type == SIGNED_NUMBER)
		arg->si_nb = (long long)va_arg(ap, long long);
	else if (type == UNSIGNED_NUMBER)
		arg->un_nb = (unsigned long long)va_arg(ap, unsigned long long);
	else if (type == POINTER)
		arg->ptr = (void*)va_arg(ap, void*);
	else if (type == FLOATING_NUMBER)
		arg->fl_nb = (long double)va_arg(ap, long double);
}

void			get_vararg(t_data *data, int index, int type)
{
	va_list		ap;
	int			count;

	count = 1;
	if (index)
	{
		va_copy(ap, data->start);
		while (count < index)
		{
			va_arg(ap, int);
			count++;
		}
		recup_arg(ap, type, &data->arg);
		va_end(ap);
	}
	else
	{
		recup_arg(data->ap, type, &data->arg);
	}
}
