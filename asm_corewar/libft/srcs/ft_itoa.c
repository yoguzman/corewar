/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:42:19 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/23 18:23:32 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void		get_size_malloc(long *n, int *div, int *c, char **ret)
{
	int		neg;
	int		size;

	neg = 0;
	*div = 1;
	size = 2;
	if (*n < 0)
	{
		neg = 1;
		*n = -*n;
		size++;
	}
	while (*n / *div >= 10)
	{
		*div *= 10;
		size++;
	}
	*ret = (char*)malloc(size * sizeof(char));
	if (neg && *ret)
	{
		**ret = '-';
		*c = 1;
	}
}

char			*ft_itoa(int n)
{
	int		div;
	long	nb;
	int		c;
	char	*ret;

	nb = (long)n;
	c = 0;
	get_size_malloc(&nb, &div, &c, &ret);
	if (!ret)
		return (NULL);
	if (nb < 0)
		nb = -nb;
	while (div != 0)
	{
		ret[c] = nb / div % 10 + '0';
		div /= 10;
		c++;
	}
	ret[c] = '\0';
	return (ret);
}
