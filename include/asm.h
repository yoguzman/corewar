/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <abeauvoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 19:25:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/01/30 19:12:54 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define USAGE "Usage: ./asm <file1>.s <file2>.s ..."
# define ERR_INSTR_VIDE "instr empty\n"
# define ERR_SPLIT "malloc strsplit kc\n"
# define ERR_NAME "inexistant instr name\n"
# define ERR_ARG "wrong number of arg\n"
# define ERR_ARG_TYPE "wrong types of arg\n"

typedef  struct  s_op
{
	char        *name;
	int         nb_arg;
	int         arg[3];
	int         nb_instr;
	int         nb_cycle;
	char        *phrase;
	int         nb_jsaispas;
	int         nb_jsaispasnonplus;
}               t_op;

int		puterr(char *str);
int		check_name(char *str, const t_op *op_tab);
int		check_nb_arg(char **str, int index_op, const t_op *op_tab);
#endif
