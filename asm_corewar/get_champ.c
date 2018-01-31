/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 05:03:44 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/30 06:42:33 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_champ(char *name, t_champ *champ)
{
	char	**file;
	int		fd;

	if ((fd = open(name, O_RDONLY)) == -1 &&
		ft_printf("Can't read source file %s\n", name))
		return (-1);
	if (!(file = get_input(fd, CHAMP_MAX)))
		return (-1);
	champ->prog_name = ft_strdup("42");
	champ->comment = ft_strdup("Just a basic Winner Program");
	champ->prog_size = 993;
	return (0);
}
