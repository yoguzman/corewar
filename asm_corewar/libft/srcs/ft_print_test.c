/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:26:30 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:38:27 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char		get_flag(char *s)
{
	int		n;

	n = 0;
	while (s[n] != '%' && s[n])
		n++;
	if (s[n] && s[n + 1] == 'd')
		return ('d');
	else if (s[n] && s[n + 1] == 's')
		return ('s');
	else if (s[n] && s[n + 1] == 'c')
		return ('c');
	return (-1);
}

void			ft_print_test(char *s, void *var)
{
	int		n;
	char	flag;

	n = 0;
	if (!s || !var)
		return ;
	if ((flag = get_flag(s)) == -1)
		return ;
	while (s[n] != '%')
	{
		ft_putchar(s[n]);
		n++;
	}
	if (flag == 'd')
		ft_putnbr(*(int*)var);
	else if (flag == 's')
		ft_putstr((char*)var);
	else if (flag == 'c')
		ft_putchar(*(char*)var);
	n += 2;
	while (s[n])
	{
		ft_putchar(s[n]);
		n++;
	}
}
