/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */ /*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <abeauvoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 19:25:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/01/31 18:09:29 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <libft.h>
# include "op.h"

# define USAGE "Usage: ./asm <file1>.s <file2>.s ..."
# define ERR_INSTR_VIDE "instr empty"
# define ERR_SPLIT "malloc strsplit kc"
# define ERR_NAME "inexistant instr name"
# define ERR_ARG "wrong number of arg"
# define ERR_ARG_TYPE "wrong types of arg"

typedef struct		s_info_line
{
	char			*label;
	int				bytes_line;
	int				cost_line;
	char			*name_instr;
	char			**arg;
}					t_if;

typedef struct	s_cost
{
	char		*name;
	void		(*f)(t_if *);
}				t_cost;

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

char    	*check_label(char *line, t_if *info_line);
int			arg_is_direct(char *str, int index_op, int nb_arg, const t_op *op_tab);
int			arg_is_reg(char *str, int index_op, int nb_arg, const t_op *op_tab);
int			puterr(char *str);
int			puterr_noend(char *str);
int			check_name(char *str, const t_op *op_tab);
int			check_nb_arg(char **str, int index_op, const t_op *op_tab);
int			arg_is_number(char *arg);
int			arg_is_labelchar(char *arg);
int			pars_instr(char *instr, t_if *info);
int			direct_is_correct(char *str);
int			reg_is_correct(char *str);
int			get_champ(char *name, t_header *champ, t_list **inf_line);
void		print_champ(t_header *champ, t_list *inf_line);
int			compile_champ(t_header *champ, char *name, t_list *inf_line);
void		epur_space(char *str);
int			check_blank_line(char *str);
int			puterr(char *str);
int			puterr_noend(char *str);
int			arg_is_labelchar(char *arg);
int			arg_is_number(char *arg);
int			check_name(char *str, const t_op *op_tab);
int			check_nb_arg(char **str, int index_op, const t_op *op_tab);
void		epur_space(char *str);
int			direct_is_correct(char *str);
int			reg_is_correct(char *str);
int			check_op_tab(int index_op, int nb_arg, int type, const t_op *op_tab);
int			arg_is_direct(char *str, int index_op, int nb_arg, const t_op *op_tab);
int			arg_is_reg(char *str, int index_op, int nb_arg, const t_op *op_tab);
void		live_cost(t_if *info_line);
void		ld_cost(t_if *info_line);
void		st_cost(t_if *info_line);
void		add_cost(t_if *info_line);
void		sub_cost(t_if *info_line);
void		and_cost(t_if *info_line);
void		or_cost(t_if *info_line);
void		xor_cost(t_if *info_line);
void		zjmp_cost(t_if *info_line);
void		ldi_cost(t_if *info_line);
void		sti_cost(t_if *info_line);
void		fork_cost(t_if *info_line);
void		lld_cost(t_if *info_line);
void		lldi_cost(t_if *info_line);
void		lfork_cost(t_if *info_line);
void		aff_cost(t_if *info_line);
int			fill_cost_line(t_if *info_line);
void		write_int(int fd, unsigned int nb);
void		live_write(t_if *info_line);
void		ld_write(t_if *info_line);
void		st_write(t_if *info_line);
void		add_write(t_if *info_line);
void		sub_write(t_if *info_line);
void		and_write(t_if *info_line);
void		or_write(t_if *info_line);
void		xor_write(t_if *info_line);
void		zjmp_write(t_if *info_line);
void		ldi_write(t_if *info_line);
void		sti_write(t_if *info_line);
void		fork_write(t_if *info_line);
void		lld_write(t_if *info_line);
void		lldi_write(t_if *info_line);
void		lfork_write(t_if *info_line);
void		aff_write(t_if *info_line);
void		write_instr(t_list *info_line);

#endif
