/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:46:59 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/23 18:48:41 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		call_ft_itoa_base(t_param *param, char flag,
				unsigned long long nb, int n)
{
	if (!nb && !param->prec)
		return ;
	if (flag == 'o' || flag == 'O')
		ft_itoa_base(&param->buffer[n], nb, "01234567", param->prec);
	else if (flag == 'u' || flag == 'U')
		ft_itoa_base(&param->buffer[n], nb, "0123456789", param->prec);
	else if (flag == 'x')
		ft_itoa_base(&param->buffer[n], nb, "0123456789abcdef", param->prec);
	else if (flag == 'X')
		ft_itoa_base(&param->buffer[n], nb, "0123456789ABCDEF", param->prec);
}

void		write_un_number(t_param *p, unsigned long long nb,
				int size, char flag)
{
	int		n;
	int		m;
	int		size_nb;

	n = 0;
	size_nb = call_get_size_nb_base(nb, p->conv);
	while (!p->att.minus && !p->att.zero && n < p->field_width - size)
		p->buffer[n++] = ' ';
	if (nb && p->att.ashtag && flag == 'x' && (p->buffer[n++] = '0'))
		p->buffer[n++] = 'x';
	else if (nb && p->att.ashtag && flag == 'X' && (p->buffer[n++] = '0'))
		p->buffer[n++] = 'X';
	m = 0;
	while (!p->att.minus && p->att.zero && m < p->field_width - size)
		p->buffer[n + m++] = '0';
	n += m;
	if ((flag == 'o' || flag == 'O') && ((p->att.ashtag && !(p->att.zero &&
			p->field_width > size_nb) && !(p->prec > size_nb)) ||
			(p->att.ashtag && !nb && !p->prec)))
		p->buffer[n++] = '0';
	call_ft_itoa_base(p, flag, nb, n);
	n += size_nb > p->prec && nb && p->prec ? size_nb : p->prec;
	m = 0;
	while (p->att.minus && m < p->field_width - size)
		p->buffer[n + m++] = ' ';
}

void		write_number(t_param *p, char *buffer, long long nb, int size)
{
	int		n;
	int		m;
	int		prec;

	n = 0;
	m = 0;
	while (!p->att.minus && !p->att.zero && n < p->field_width - size)
		buffer[n++] = ' ';
	if (p->att.space && nb >= 0)
		buffer[n++] = ' ';
	if (p->att.plus && nb >= 0)
		buffer[n++] = '+';
	prec = p->att.zero * (p->field_width - size + get_size_nb(nb));
	if (prec && nb < 0)
		prec -= 1;
	if (!(!nb && !p->prec))
		ft_printf_itoa(&buffer[n], nb, prec ? prec : p->prec, &n);
	m = 0;
	while (p->att.minus && m < p->field_width - size)
		buffer[n + m++] = ' ';
}
