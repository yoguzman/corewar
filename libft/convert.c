/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:25:28 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/06 18:33:37 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include <stdlib.h>

char							*convert_u(t_dt *dt, unsigned long long int ok)
{
	char						*buff;

	if (dt->conv == 'x')
	{
		if ((buff = ft_itoa_base_u(ok, "0123456789abcdef")) == NULL)
			return (NULL);
	}
	else if (dt->conv == 'X')
	{
		if ((buff = ft_itoa_base_u(ok, "0123456789ABCDEF")) == NULL)
			return (NULL);
	}
	else if (dt->conv == 'o' || dt->conv == 'O')
	{
		if ((buff = ft_itoa_base_u(ok, "01234567")) == NULL)
			return (NULL);
	}
	else
	{
		if ((buff = ft_itoa_base_u(ok, "0123456789")) == NULL)
			return (NULL);
	}
	return (buff);
}

char							*convert_modulo(void)
{
	char						*buff;

	if ((buff = malloc(sizeof(char) * 2)) == NULL)
		return (NULL);
	buff[0] = '%';
	buff[1] = 0;
	return (buff);
}

char							*convert_next(t_dt *dt, va_list ap)
{
	char						*buff;

	buff = NULL;
	if (dt->conv == 's')
	{
		if ((buff = (va_arg(ap, char *))) == NULL)
			return ((buff = ft_strdup("(null)")));
		return (ft_strdup(buff));
	}
	else if (dt->conv == 'p')
		buff = ft_itoa_base_u(va_arg(ap, long long int),
				"0123456789abcdef");
	else if (dt->conv == 'c')
	{
		if ((buff = malloc(sizeof(char) * 2)) == NULL)
			return (NULL);
		buff[0] = (char)va_arg(ap, int);
		dt->cz = buff[0];
		buff[1] = 0;
	}
	else if (dt->conv == '%')
		buff = convert_modulo();
	else if (dt->conv == 'C' || dt->conv == 'S')
		va_arg(ap, char *);
	return (buff);
}

char							*convert(t_dt *dt, va_list ap)
{
	char						*buff;
	long long int				ok;
	unsigned long long int		ok_u;

	buff = NULL;
	if (dt->conv == 'x' || dt->conv == 'X' || dt->conv == 'o' ||
			dt->conv == 'O' || dt->conv == 'u' || dt->conv == 'U')
	{
		ok_u = conv_usigned(dt, ap);
		if ((buff = convert_u(dt, ok_u)) == NULL)
			return (NULL);
	}
	else if (dt->conv == 'd' || dt->conv == 'D' || dt->conv == 'i')
	{
		ok = conv_signed(dt, ap);
		if ((buff = ft_itoa_base(ok, "0123456789")) == NULL)
			return (NULL);
	}
	else
		return (convert_next(dt, ap));
	return (buff);
}
