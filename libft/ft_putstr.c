/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 13:55:56 by yguzman           #+#    #+#             */
/*   Updated: 2018/03/22 19:19:04 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void			ft_putstr_null(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	else
		ft_putstr("(null)\n");
}

int				ft_putstr(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

void			ft_putstr_color(char *str, int color)
{
	ft_putstr("\033[");
	ft_putnbr(color);
	ft_putstr(";01m");
	ft_putstr(str);
	ft_putstr("\033[00m");
}
