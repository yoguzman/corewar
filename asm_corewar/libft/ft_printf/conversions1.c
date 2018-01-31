/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 18:01:43 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/23 18:23:43 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_lower_s_flag(t_param *param, t_arg *arg)
{
	int		size;
	char	*str;
	int		n;
	int		m;

	n = 0;
	if (param->modifier == 'l')
		return (ft_upper_s_flag(param, arg));
	str = (char*)arg->ptr;
	if (!str)
		str = "(null)";
	if (get_size_buffer(str, param, &size) > BUFF_MAX)
		return (-1);
	while (!param->att.minus && n < param->field_width - size)
		param->buffer[n++] = param->att.zero ? '0' : ' ';
	m = 0;
	while (m < size && (param->buffer[n + m] = str[m]))
		m += 1;
	while (param->att.minus && n < param->field_width - size)
		param->buffer[n++ + m] = ' ';
	write(1, param->buffer, n + m);
	return (n + m);
}

int			ft_upper_s_flag(t_param *param, t_arg *arg)
{
	int		size;
	wchar_t	*str;
	int		n;
	int		m;

	n = 0;
	str = (wchar_t*)arg->ptr;
	if (!str)
		str = L"(null)";
	if (get_size_buffer_u(str, param, &size) > BUFF_MAX)
		return (-1);
	while (!param->att.minus && n < param->field_width - size)
		param->buffer[n++] = param->att.zero ? '0' : ' ';
	m = n;
	write_unicode(param->buffer, str, size, &m);
	n = 0;
	while (param->att.minus && n < param->field_width - size)
		param->buffer[n++ + m] = ' ';
	write(1, param->buffer, n + m);
	return (n + m);
}

int			ft_lower_p_flag(t_param *p, t_arg *arg)
{
	unsigned long	nb;
	int				size;
	int				n;
	int				m;

	nb = (unsigned long)arg->ptr;
	size = !p->prec && !nb ? 0 : get_size_nb_base(nb, "0123456789abcdef");
	if (p->prec > size)
		size = p->prec;
	size += 2;
	if ((p->field_width > size ? p->field_width : size) > BUFF_MAX)
		return (-1);
	n = 0;
	while (!p->att.minus && n < p->field_width - size)
		p->buffer[n++] = ' ';
	m = n;
	p->buffer[m] = '0';
	p->buffer[m + 1] = 'x';
	if (!(!nb && !p->prec))
		ft_itoa_base(&p->buffer[m + 2], nb, "0123456789abcdef", p->prec);
	m += size;
	while (p->att.minus && n < p->field_width - size)
		p->buffer[m + n++] = ' ';
	write(1, p->buffer, size + n);
	return (size + n);
}

int			ft_lower_d_flag(t_param *param, t_arg *arg)
{
	long long	nb;
	int			size;
	int			size_buffer;

	nb = (long long)arg->si_nb;
	if (param->modifier)
		ft_caster(&nb, NULL, SIGNED_NUMBER, param->modifier);
	else
		nb = (int)nb;
	if ((size_buffer = get_size_buffer_nb(nb, param, &size)) > BUFF_MAX)
		return (-1);
	write_number(param, param->buffer, nb, size);
	write(1, param->buffer, size_buffer);
	return (size_buffer);
}

int			ft_upper_d_flag(t_param *param, t_arg *arg)
{
	long		nb;
	int			size;
	int			size_buffer;

	nb = (long)arg->si_nb;
	if ((size_buffer = get_size_buffer_nb(nb, param, &size)) > BUFF_MAX)
		return (-1);
	write_number(param, param->buffer, nb, size);
	write(1, param->buffer, size_buffer);
	return (size_buffer);
}
