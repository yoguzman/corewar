/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_char_in_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:19:40 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/10 15:01:41 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			find_char_in_str(char c, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		++i;
	}
	return (0);
}
