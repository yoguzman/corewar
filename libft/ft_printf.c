/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:24:31 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/06 19:28:18 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include <stdlib.h>

char			*go_fill_string(const char *format, int *i,
								t_dt *dt, va_list ap)
{
	char		*string;
	char		*buff;

	string = NULL;
	if ((fill_data_base_flag(format, i, dt)) == -1)
		return (NULL);
	if ((string = convert(dt, ap)) == NULL)
		return (NULL);
	if (dt->conv == 'p')
	{
		if ((buff = ft_strjoin("0x", string)) == NULL)
			return (NULL);
		free(string);
		string = buff;
	}
	if ((string = go_preci(string, dt)) == NULL)
		return (NULL);
	if ((string = go_attr(string, dt)) == NULL)
		return (NULL);
	if ((string = go_width(string, dt)) == NULL)
		return (NULL);
	return (string);
}

int				event_c(t_dt *dt, char *string, int len)
{
	if (dt->conv == 'c' && dt->cz == 0)
	{
		if (dt->tab_f['-'] == 1)
		{
			ft_putchar(0);
			len = ft_strlen(string);
			ft_putstr(string);
			++len;
		}
		else
		{
			ft_putstr(string);
			ft_putchar(string[ft_strlen(string)]);
			++len;
		}
	}
	else
		ft_putstr(string);
	return (len);
}

int				go_printf(const char *format, int *i, va_list ap, t_dt *dt)
{
	char		*string;
	int			len;

	string = NULL;
	reset_flag(dt);
	if ((string = go_fill_string(format, i, dt, ap)) == NULL)
		return (0);
	len = ft_strlen(string);
	move_move(string, dt);
	++*i;
	len = event_c(dt, string, len);
	free(string);
	return (len);
}

void			loop_printf(int *i, int *len, const char *format)
{
	ft_putchar(format[*i]);
	++*i;
	++*len;
}

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	int			len;
	int			i;
	t_dt		dt;

	va_start(ap, format);
	if (init_flag(&dt) == -1)
		return (-1);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			++i;
			if ((len += go_printf(format, &i, ap, &dt)) == -1)
				return (-1);
		}
		else if (format[i])
			loop_printf(&i, &len, format);
	}
	va_end(ap);
	free_all(&dt);
	return (len);
}
