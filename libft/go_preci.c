/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_preci.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 15:43:38 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/06 18:10:41 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include <stdlib.h>

int				ft_strlen_mod(char *str)
{
	int			i;
	int			len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (!(str[i] == '+' || str[i] == '-' || str[i] == 'x' || str[i] == 'X'))
			++len;
		++i;
	}
	return (len);
}

void			go_preci_s(char *string, t_dt *dt)
{
	string[dt->preci] = 0;
}

void			go_preci_p(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'x' && str[i + 1] == '0' && str[i + 2] == 0)
			str[i + i] = 0;
		++i;
	}
}

char			*go_preci_next(char *string, t_dt *dt)
{
	char		*buff;
	char		*buff_other;
	int			len;

	buff = NULL;
	if (dt->conv == '%')
		return (string);
	if (!ft_isdigitnozero(string) && dt->preci == 0)
	{
		string[0] = 0;
		return (string);
	}
	len = dt->preci - ft_strlen_mod(string);
	if ((buff_other = malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_memset(buff_other, '0', len);
	buff_other[len] = 0;
	if ((buff = ft_strjoin(buff_other, string)) == NULL)
		return (NULL);
	free(string);
	free(buff_other);
	return (buff);
}
