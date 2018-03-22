/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_all_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:26:32 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/06 17:55:44 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

char			*put_flag(const char *format, int len, int cpi)
{
	char		*buff;

	if ((buff = malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_strncpy(buff, format + cpi, len);
	buff[len] = 0;
	return (buff);
}

char			*find_flag(const char *format, int *i, t_dt *dt)
{
	char		*flag;
	int			len;
	int			cpi;
	int			j;

	len = 0;
	cpi = *i;
	while (format[*i])
	{
		j = 0;
		++len;
		while (dt->all_conv[j])
		{
			if (format[*i] == dt->all_conv[j])
			{
				if ((flag = put_flag(format, len, cpi)) == NULL)
					return (NULL);
				return (flag);
			}
			++j;
		}
		++*i;
	}
	return (NULL);
}

int				find_attr(t_dt *dt, int *i, char *buff)
{
	int			j;

	while (dt->full_flag[*i])
	{
		j = 0;
		while (buff[j])
		{
			if (dt->full_flag[*i] == buff[j])
			{
				if (!(dt->tab_f[(int)buff[j]] == 1 &&
							buff[j] != 'h' && buff[j] != 'l') ||
						dt->tab_f[(int)buff[j]] == 2)
					dt->tab_f[(int)buff[j]] += 1;
				break ;
			}
			++j;
		}
		if (!buff[j])
			return (0);
		++*i;
	}
	return (0);
}

int				find_width(t_dt *dt, int *i)
{
	char		*buff;
	int			len;
	int			cpi;
	int			nb;

	len = 0;
	cpi = *i;
	buff = NULL;
	if (ft_isdigit(dt->full_flag[*i]))
		while (dt->full_flag[*i] && (ft_isdigit(dt->full_flag[*i])))
		{
			++*i;
			++len;
		}
	else
		return (0);
	if (*i != cpi)
		if ((buff = put_flag(dt->full_flag, len, cpi)) == NULL)
			return (-1);
	nb = ft_atoi(buff);
	free(buff);
	return (nb);
}

int				fill_data_base_flag(const char *format, int *i, t_dt *dt)
{
	int			j;

	j = 0;
	if ((dt->full_flag = find_flag(format, i, dt)) == NULL)
		return (-1);
	if (find_attr(dt, &j, dt->all_attr) == -1 ||
			(dt->width = find_width(dt, &j)) == -1)
		return (-1);
	if (dt->full_flag[j] == '.')
	{
		dt->prec = 1;
		++j;
		if ((dt->preci = find_width(dt, &j)) == -1)
			return (-1);
	}
	if (find_attr(dt, &j, dt->all_modif_conv) == -1 ||
			ft_strchr(dt->all_conv, dt->full_flag[j]) == NULL)
		dt->conv = dt->full_flag[j];
	else
	{
		dt->conv = format[*i];
		dt->tab_f[(int)format[*i]] = 1;
	}
	free(dt->full_flag);
	return (0);
}
