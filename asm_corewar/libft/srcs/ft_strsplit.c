/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 07:54:59 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 01:40:45 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int			get_nb_words(char const *s, char c)
{
	int	n;
	int	nb_words;

	nb_words = 0;
	n = 0;
	if (!s)
		return (0);
	while (s[n] == c)
		n++;
	while (s[n] != '\0')
	{
		while (s[n] != c && s[n] != '\0')
			n++;
		nb_words++;
		while (s[n] == c)
			n++;
	}
	return (nb_words);
}

static int			get_size_word(char const *s, int pos, char c)
{
	int	size_word;

	size_word = 0;
	while (s[pos] != c && s[pos] != '\0')
	{
		size_word++;
		pos++;
	}
	return (size_word);
}

static void			write_word(char const *s, char *dest, int *pos, char c)
{
	int	n;

	n = 0;
	while (s[*pos] != c && s[*pos] != '\0')
	{
		dest[n] = s[*pos];
		n++;
		(*pos)++;
	}
	dest[n] = '\0';
	while (s[*pos] == c)
		(*pos)++;
}

char				**ft_strsplit(char const *s, char c)
{
	int		nb_words;
	char	**ret;
	int		count;
	int		pos;

	pos = 0;
	count = 0;
	nb_words = get_nb_words(s, c);
	if (!s || (ret = (char**)malloc((nb_words + 1) * sizeof(char*))) == NULL)
		return (NULL);
	while (s[pos] == c)
		pos++;
	while (count < nb_words)
	{
		if ((ret[count] = (char*)malloc((get_size_word(s, pos, c) + 1) *
			sizeof(char))) == NULL)
			return (NULL);
		write_word(s, ret[count], &pos, c);
		count++;
	}
	ret[count] = NULL;
	return (ret);
}
