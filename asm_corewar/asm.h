/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 21:51:07 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/30 06:47:20 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "op.h"

# define CHAMP_MAX	1000

typedef struct		s_champ
{
	char			*prog_name;
	unsigned int	prog_size;
	char			*comment;
}					t_champ;

int					get_champ(char *name, t_champ *champ);
void				print_champ(const t_champ champ);
int					compile_champ(const t_champ champ, char *name);

#endif
