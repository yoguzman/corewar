/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 12:10:30 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/23 18:46:46 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>
# include "../libft.h"

# define ENABLED			1
# define DISABLED			0

# define CONVERSIONS		"sSpdDioOuUxXcCeEfFgGaAn%"
# define ATTRIBUTES			"#0-+ "
# define MODIFIERS			"hljzL"

# define SIGNED_NUMBERS		"dDicC"
# define UNSIGNED_NUMBERS	"oOuUxX"
# define POINTERS			"sSpn"
# define FLOATING_NUMBERS	"eEfFgGaA"

# define HH					420
# define LL					421

# define BUFF_MAX			1000

typedef struct				s_attributes
{
	int						ashtag;
	int						zero;
	int						minus;
	int						plus;
	int						space;
}							t_attributes;

typedef struct				s_param
{
	t_attributes			att;
	int						target;
	int						field_width;
	int						prec;
	int						modifier;
	char					conv;
	char					buffer[BUFF_MAX];
}							t_param;

typedef struct				s_arg
{
	int						type;
	long long				si_nb;
	unsigned long long		un_nb;
	void					*ptr;
	long double				fl_nb;
}							t_arg;

# define SIGNED_NUMBER		42
# define UNSIGNED_NUMBER	43
# define POINTER			45
# define FLOATING_NUMBER	46
# define NONE				47

typedef struct				s_data
{
	va_list					ap;
	va_list					start;
	t_param					param;
	t_arg					arg;
	int						nb_carac;
	int						(*tab_conv[24])(t_param*, t_arg*);
}							t_data;

int							ft_printf(const char *restrict format, ...);
void						init_ft_printf(t_data *data);
int							print_format(t_data *data,
								const char *restrict format);
int							get_param(const char *restrict format, int *n,
								t_data *data);
int							get_index(char c, char *str);
int							get_target_arg(const char *restrict format, int *n,
								t_data *data);
void						get_attributes(const char *restrict format, int *n,
								t_data *data);
int							get_field_width(const char *restrict format, int *n,
								t_data *data);
int							get_precision(const char *restrict format, int *n,
								t_data *data);
void						get_modifier(const char *restrict format, int *n,
								t_data *data);
int							get_conversion(const char *restrict format, int *n,
								t_data *data);
void						get_overload(t_param *param);
int							ft_put_err(char *str);
unsigned int				ft_strlen(const char *str);
void						get_vararg(t_data *data, int index, int type);
int							get_nb(char *str);
void						reset_data(t_data *data);
int							get_size_buffer(char *str, t_param *param,
								int *size);
int							get_size_buffer_u(int *str, t_param *param,
								int *size);
void						write_unicode(char *buffer, int *str, int size,
								int *n);
int							get_size_unicode(wchar_t c);
int							convert_unicode(wchar_t c, char tab[4]);
unsigned int				get_size_nb_base(unsigned long long nb,
								char *base);
void						ft_itoa_base(char *str, unsigned long long nb,
								char *base, int size);
void						ft_caster(long long *si_nb,
								unsigned long long *un_nb, int type,
								int modifier);
void						ft_printf_itoa(char *str, long long nb, int size,
								int *pos);
unsigned int				get_size_nb(long long nb);
int							get_size_buffer_nb(long long nb, t_param *param,
								int *size);
void						write_number(t_param *param, char *buffer,
								long long nb, int size);
int							get_size_buffer_un_nb(unsigned long long nb,
								t_param *param, int *size);
void						write_un_number(t_param *param,
								unsigned long long nb, int size, char flag);
int							ft_put_unicode(wchar_t car);
int							call_get_size_nb_base(unsigned long long nb,
								char flag);

int							ft_lower_s_flag(t_param *param, t_arg *arg);
int							ft_upper_s_flag(t_param *param, t_arg *arg);
int							ft_lower_p_flag(t_param *param, t_arg *arg);
int							ft_lower_d_flag(t_param *param, t_arg *arg);
int							ft_upper_d_flag(t_param *param, t_arg *arg);
int							ft_lower_i_flag(t_param *param, t_arg *arg);
int							ft_lower_o_flag(t_param *param, t_arg *arg);
int							ft_upper_o_flag(t_param *param, t_arg *arg);
int							ft_lower_u_flag(t_param *param, t_arg *arg);
int							ft_upper_u_flag(t_param *param, t_arg *arg);
int							ft_lower_x_flag(t_param *param, t_arg *arg);
int							ft_upper_x_flag(t_param *param, t_arg *arg);
int							ft_lower_c_flag(t_param *param, t_arg *arg);
int							ft_upper_c_flag(t_param *param, t_arg *arg);
int							ft_lower_e_flag(t_param *param, t_arg *arg);
int							ft_upper_e_flag(t_param *param, t_arg *arg);
int							ft_lower_f_flag(t_param *param, t_arg *arg);
int							ft_upper_f_flag(t_param *param, t_arg *arg);
int							ft_lower_g_flag(t_param *param, t_arg *arg);
int							ft_upper_g_flag(t_param *param, t_arg *arg);
int							ft_lower_a_flag(t_param *param, t_arg *arg);
int							ft_upper_a_flag(t_param *param, t_arg *arg);
int							ft_lower_n_flag(t_param *param, t_arg *arg);
int							ft_percent_flag(t_param *param, t_arg *arg);

#endif
