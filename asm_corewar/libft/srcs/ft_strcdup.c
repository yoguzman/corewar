/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 01:20:49 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/23 18:56:41 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*ft_strcdup(char *str, char car)
{
	int		n;
	int		size;
	char	*ret;

	n = 0;
	size = 0;
	ret = NULL;
	size = ft_strclen(str, car);
	if (!(ret = (char*)malloc((size + 1) * sizeof(char))))
	{
		ft_put_err("malloc failed");
		return (NULL);
	}
	while (n < size)
	{
		ret[n] = str[n];
		n += 1;
	}
	ret[n] = '\0';
	return (ret);
}
