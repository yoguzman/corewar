/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_all.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:50:37 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/09 12:56:50 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include <stdlib.h>

int					ft_isdigitnozero(char *str)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '1' && str[i] <= '9') ||
			(str[i] >= '1' && str[i] <= 'f'))
			return (1);
		++i;
	}
	return (0);
}

char				*go_attr_sharp(char *string, t_dt *dt)
{
	char			*buff;

	if (string == NULL)
		return (NULL);
	buff = NULL;
	if ((!(string[0]) || (ft_isdigitnozero(string) && string[0] != '0')) &&
			(dt->conv == 'o' || dt->conv == 'O'))
	{
		if ((buff = ft_strjoin("0", string)) == NULL)
			return (NULL);
	}
	else if (ft_isdigitnozero(string) && dt->conv == 'x')
	{
		if ((buff = ft_strjoin("0x", string)) == NULL)
			return (NULL);
	}
	else if (ft_isdigitnozero(string) && dt->conv == 'X')
	{
		if ((buff = ft_strjoin("0X", string)) == NULL)
			return (NULL);
	}
	else
		return (string);
	free(string);
	return (buff);
}

char				*go_attr_add(char *string)
{
	char			*buff;

	if (string == NULL)
		return (NULL);
	buff = NULL;
	if (!ft_strchr(string, '-'))
	{
		if ((buff = ft_strjoin("+", string)) == NULL)
			return (NULL);
	}
	else
		return (string);
	free(string);
	return (buff);
}

char				*go_attr_space(char *string)
{
	char			*buff;

	if (string == NULL)
		return (NULL);
	buff = NULL;
	if (!ft_strchr(string, '-'))
	{
		if ((buff = ft_strjoin(" ", string)) == NULL)
			return (NULL);
	}
	else
		return (string);
	free(string);
	return (buff);
}
