/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:55:08 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:40:57 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int			get_nb_spaces(const char *s)
{
	int	nb_spaces;
	int	n;

	n = 0;
	nb_spaces = 0;
	while (s[n] == ' ' || s[n] == '\n' || s[n] == '\t')
	{
		n++;
		nb_spaces++;
	}
	n = ft_strlen(s) - 1;
	while (s[n] == ' ' || s[n] == '\n' || s[n] == '\t')
	{
		n--;
		nb_spaces++;
	}
	return (nb_spaces);
}

static void			copy_chain(const char *s, char *ret)
{
	int	n;
	int	start;
	int	end;

	n = 0;
	start = 0;
	while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
		start++;
	end = ft_strlen(s) - 1;
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		end--;
	end++;
	while (start < end)
	{
		ret[n] = s[start];
		n++;
		start++;
	}
	ret[n] = '\0';
}

char				*ft_strtrim(char const *s)
{
	int		nb_spaces;
	char	*ret;

	if (s == NULL)
		return (NULL);
	nb_spaces = get_nb_spaces(s);
	if (nb_spaces >= (int)ft_strlen(s))
	{
		if ((ret = (char*)malloc(1 * sizeof(char))) == NULL)
			return (NULL);
		*ret = 0;
		return (ret);
	}
	if (nb_spaces == 0)
		return (ft_strdup(s));
	if ((ret = (char*)malloc((ft_strlen(s) - nb_spaces + 1) *
				sizeof(char))) == NULL)
		return (NULL);
	copy_chain(s, ret);
	return (ret);
}
