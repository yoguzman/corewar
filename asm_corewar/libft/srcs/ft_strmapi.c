/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:54:42 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:40:15 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	int		n;

	n = 0;
	if (!s || !f)
		return (NULL);
	if ((new = ft_strdup(s)) == NULL)
		return (NULL);
	while (s[n] != '\0')
	{
		new[n] = f(n, s[n]);
		n++;
	}
	new[n] = '\0';
	return (new);
}
