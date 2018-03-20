/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <abeauvoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 19:25:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/14 20:08:07 by abeauvoi         ###   ########.fr       */
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

typedef union		u_convert_oct
{
	unsigned char	nb_oct[4];
	int				nb;
}					t_conv_oct;

typedef struct		s_info_line
{
	char			*label;
	unsigned char	op_code;
	int				mask;
	int				bytes_line;
	int				cost_line;
	char			*name_instr;
	char			**arg;
	t_conv_oct		conv;
}					t_if;

typedef struct		s_cost
{
	char			*name;
	void			(*f)(t_if *);
}					t_cost;

typedef struct		s_write
{
	char			*name;
	void			(*f)(t_if *, int dest);
}					t_write;

typedef union		u_neg
{
	unsigned short	neg;
	unsigned char	bneg[2];
}					t_neg;

void				print_header_a(t_header *champ);
void				print_oct_arg(t_if *info);
void				print_arg(t_if *info);
int					get_instruction_code(char *instruction);
int					is_label(t_if *here, t_list *list, int line);
int					modif_label(t_if *here, char *str_tmp, int i[3],
		t_list *tmp);
int					get_file2(char *new, int *dest);
int					get_info_file_loop2(t_list **inf_line,
					t_if *info_line, t_if **tmp);
int					get_info_file_loop(char **file, int *i, t_if *info_line);
int					print_error_nb_arg(char *instr, int line);
void				write_string(int dest, char *prog_name, int lenght);
int					print_error_name(char **t_str, int line, int i);
char				*check_label(char *line, t_if *info_line);
int					arg_is_direct(char *str, int index_op, int nb_arg,
		const t_op *op_tab);
int					arg_is_reg(char *str, int index_op, int nb_arg,
		const t_op *op_tab);
int					puterr(char *str);
int					puterr_noend(char *str);
int					check_name(char *str, const t_op *op_tab);
int					arg_is_number(char *arg);
int					arg_is_labelchar(char *arg);
int					pars_instr(char *instr, t_if *info, int line);
int					direct_is_correct(char *str);
int					reg_is_correct(char *str);
int					get_champ(char *name, t_header *champ, t_list **inf_line);
int					print_champ(t_header *champ, t_list *inf_line);
int					compile_champ(t_header *champ, char *name,
		t_list *inf_line);
void				epur_space(char *str);
int					check_blank_line(char *str);
int					puterr(char *str);
int					puterr_noend(char *str);
int					arg_is_labelchar(char *arg);
int					arg_is_number(char *arg);
int					check_name(char *str, const t_op *op_tab);
int					check_nb_arg(char **str, int index_op, const t_op *op_tab);
void				epur_space(char *str);
int					direct_is_correct(char *str);
int					reg_is_correct(char *str);
int					check_op_tab(int index_op, int nb_arg, int type,
		const t_op *op_tab);
int					arg_is_direct(char *str, int index_op, int nb_arg,
		const t_op *op_tab);
int					arg_is_reg(char *str, int index_op, int nb_arg,
		const t_op *op_tab);
void				live_cost(t_if *info_line);
void				ld_cost(t_if *info_line);
void				st_cost(t_if *info_line);
void				add_cost(t_if *info_line);
void				sub_cost(t_if *info_line);
void				and_cost(t_if *info_line);
void				or_cost(t_if *info_line);
void				xor_cost(t_if *info_line);
void				zjmp_cost(t_if *info_line);
void				ldi_cost(t_if *info_line);
void				sti_cost(t_if *info_line);
void				fork_cost(t_if *info_line);
void				lld_cost(t_if *info_line);
void				lldi_cost(t_if *info_line);
void				lfork_cost(t_if *info_line);
void				aff_cost(t_if *info_line);
int					fill_cost_line(t_if *info_line);
void				write_int(int fd, unsigned int nb);
void				live_write(t_if *info_line, int dest);
void				ld_write(t_if *info_line, int dest);
void				st_write(t_if *info_line, int dest);
void				add_write(t_if *info_line, int dest);
void				sub_write(t_if *info_line, int dest);
void				and_write(t_if *info_line, int dest);
void				or_write(t_if *info_line, int dest);
void				xor_write(t_if *info_line, int dest);
void				zjmp_write(t_if *info_line, int dest);
void				ldi_write(t_if *info_line, int dest);
void				sti_write(t_if *info_line, int dest);
void				fork_write(t_if *info_line, int dest);
void				lld_write(t_if *info_line, int dest);
void				lldi_write(t_if *info_line, int dest);
void				lfork_write(t_if *info_line, int dest);
void				aff_write(t_if *info_line, int dest);
int					write_instr(t_list *inf_line, int dest);
void				write_short(int fd, unsigned short nb);
void				write_op_code(char **arg, int nb_arg, int dest);
int					neg_to_neg(unsigned short neg);
int					print_usage(void);
int					get_nb_lines(char *name);
int					print_error_label(char *str, int line);
int					julien_pu_le_caca(char *str, int i);
int					replace_cod_oct(uint8_t octet, uint8_t op_code);
int					del_comment(char *file);
void				puterr_header(char *msg_err, int i);
void				puterr_size_header(char *msg_err, int i);
int					del_comment_check(char *file);
void				free_head(char **tab, char *line);
void				free_line_head_and_incr(char **line, int *i);

#endif
