/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 18:34:02 by yguzman           #+#    #+#             */
/*   Updated: 2018/03/22 16:46:39 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>

typedef struct					s_data
{
	int							width;
	int							preci;
	int							prec;
	char						conv;
	int							cz;
	char						*full_flag;
	int							tab_f[127];
	char						*all_conv;
	char						*all_attr;
	char						*all_modif_conv;
}								t_dt;

void							go_preci_p(char *string);
int								ft_printf(const char *format, ...);
int								fill_data_base_flag(const char *format,
												int *i, t_dt *dt);
int								init_flag(t_dt *dt);
void							reset_flag(t_dt *dt);
char							*convert(t_dt *dt, va_list ap);
char							*go_attr_sharp(char *string, t_dt *dt);
char							*go_attr_add(char *string);
char							*go_attr_space(char *string);
char							*go_width_neg(char *string, t_dt *dt);
char							*go_width_space(char *string, t_dt *dt);
char							*go_width_zero(char *string, t_dt *dt);
char							*go_preci(char *string, t_dt *dt);
void							go_preci_s(char *string, t_dt *dt);
char							*go_preci_next(char *string, t_dt *dt);
int								ft_isdigitnozero(char *str);
int								ft_strlen_mod(char *str);
unsigned long long int			conv_usigned(t_dt *dt, va_list ap);
long long int					conv_signed(t_dt *dt, va_list ap);
char							*go_preci(char *string, t_dt *dt);
char							*go_attr(char *string, t_dt *dt);
char							*go_width(char *string, t_dt *dt);
void							move_move(char *string, t_dt *dt);
void							free_all(t_dt *dt);

#endif
