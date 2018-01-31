/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <abeauvoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 19:25:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/01/25 19:26:14 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <libft.h>
# include "op.h"

typedef struct		s_info_line
{
	char			*label;
	int				bytes_line;
	int				cost_line;
	char			*name_instr;
	char			**arg;
}					t_if;

int					get_champ(char *name, t_header *champ, t_list **inf_line);
void				print_champ(t_header *champ, t_list *inf_line);
int					compile_champ(t_header *champ, char *name, t_list *inf_line);

#endif
