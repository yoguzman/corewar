/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:54:23 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:39:43 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*ft_strdup(const char *s)
{
	char	*ret;
	int		size;

	size = ft_strlen(s);
	if ((ret = (char*)malloc((size + 1) * sizeof(char))) == NULL)
		return (NULL);
	ret = ft_memcpy(ret, s, size);
	ret[size] = '\0';
	return (ret);
}
