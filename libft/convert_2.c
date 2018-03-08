/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 15:10:46 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/06 17:05:30 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

unsigned long long int			conv_usigned_next(t_dt *dt, va_list ap)
{
	unsigned long long int		ok;
	unsigned short				ok1;
	unsigned char				ok2;

	ok = 0;
	ok1 = 0;
	ok2 = 0;
	if (dt->tab_f['j'] == 1)
		ok = va_arg(ap, uintmax_t);
	else if (dt->tab_f['z'] == 1)
		ok = va_arg(ap, size_t);
	else if (dt->tab_f['h'] == 1)
	{
		ok1 = (unsigned short)va_arg(ap, unsigned int);
		return (ok1);
	}
	else if (dt->tab_f['h'] == 2)
	{
		ok2 = (unsigned char)va_arg(ap, unsigned int);
		return (ok2);
	}
	else
		ok = va_arg(ap, unsigned int);
	return (ok);
}

unsigned long long int			conv_usigned(t_dt *dt, va_list ap)
{
	unsigned long long int		ok;

	ok = 0;
	if (dt->conv == 'O' || dt->conv == 'U')
		ok = va_arg(ap, unsigned long);
	else if (dt->tab_f['l'] == 2)
		ok = va_arg(ap, unsigned long long);
	else if (dt->tab_f['l'] == 1)
		ok = va_arg(ap, unsigned long);
	else
		return (conv_usigned_next(dt, ap));
	return (ok);
}

long long int					conv_signed_next(t_dt *dt, va_list ap)
{
	long long int				ok;
	short						ok1;
	char						ok2;

	ok = 0;
	ok1 = 0;
	ok2 = 0;
	if (dt->tab_f['j'] == 1)
		ok = va_arg(ap, intmax_t);
	else if (dt->tab_f['z'] == 1)
		ok = va_arg(ap, long);
	else if (dt->tab_f['h'] == 1)
	{
		ok1 = (short)va_arg(ap, int);
		return (ok1);
	}
	else if (dt->tab_f['h'] == 2)
	{
		ok2 = (char)va_arg(ap, int);
		return (ok2);
	}
	else
		ok = va_arg(ap, int);
	return (ok);
}

long long int					conv_signed(t_dt *dt, va_list ap)
{
	long long int				ok;

	ok = 0;
	if (dt->conv == 'D')
		ok = va_arg(ap, long);
	else if (dt->tab_f['l'] == 2)
		ok = va_arg(ap, long long);
	else if (dt->tab_f['l'] == 1)
		ok = va_arg(ap, long);
	else
		return (conv_signed_next(dt, ap));
	return (ok);
}
