/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:53:59 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:38:50 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	int	div;

	div = 1;
	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	while (n / div >= 10)
		div *= 10;
	while (div != 0)
	{
		ft_putchar_fd(n / div % 10 + 48, fd);
		div /= 10;
	}
}
