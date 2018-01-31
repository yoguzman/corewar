/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_functions3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 18:52:20 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/22 20:49:03 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_lower_x_flag(t_param *param, t_arg *arg)
{
	unsigned long long	nb;
	int					size;
	int					size_buffer;

	nb = (unsigned long long)arg->un_nb;
	if (param->modifier)
		ft_caster(NULL, &nb, UNSIGNED_NUMBER, param->modifier);
	else
		nb = (unsigned int)nb;
	if ((size_buffer = get_size_buffer_un_nb(nb, param, &size)) > BUFF_MAX)
		return (-1);
	write_un_number(param, nb, size, 'x');
	write(1, param->buffer, size_buffer);
	return (size_buffer);
}

int			ft_upper_x_flag(t_param *param, t_arg *arg)
{
	unsigned long long	nb;
	int					size;
	int					size_buffer;

	nb = (unsigned long long)arg->un_nb;
	if (param->modifier)
		ft_caster(NULL, &nb, UNSIGNED_NUMBER, param->modifier);
	else
		nb = (unsigned int)nb;
	if ((size_buffer = get_size_buffer_un_nb(nb, param, &size)) > BUFF_MAX)
		return (-1);
	write_un_number(param, nb, size, 'X');
	write(1, param->buffer, size_buffer);
	return (size_buffer);
}

int			ft_lower_c_flag(t_param *param, t_arg *arg)
{
	int		carac;
	int		m;
	int		n;

	if (param->modifier == 'l')
		return (ft_upper_c_flag(param, arg));
	carac = (int)arg->si_nb;
	carac = (unsigned char)carac;
	n = 0;
	if ((param->field_width ? param->field_width : 1) > BUFF_MAX)
		return (-1);
	while (!param->att.minus && n < param->field_width - 1)
		param->buffer[n++] = param->att.zero ? '0' : ' ';
	param->buffer[n++] = carac;
	m = 0;
	while (param->att.minus && m < param->field_width - 1)
		param->buffer[n + m++] = ' ';
	write(1, param->buffer, n + m);
	return (n + m);
}

int			ft_upper_c_flag(t_param *param, t_arg *arg)
{
	wint_t	carac;

	(void)param;
	carac = (wint_t)arg->si_nb;
	carac = (wchar_t)carac;
	ft_put_unicode(carac);
	return (get_size_unicode(carac));
}

int			ft_lower_e_flag(t_param *param, t_arg *arg)
{
	(void)param;
	(void)arg;
	return (0);
}
