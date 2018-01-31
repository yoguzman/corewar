/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_functions5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 09:41:16 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/23 13:54:15 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_lower_a_flag(t_param *param, t_arg *arg)
{
	(void)param;
	(void)arg;
	return (0);
}

int			ft_upper_a_flag(t_param *param, t_arg *arg)
{
	(void)param;
	(void)arg;
	return (0);
}

int			ft_lower_n_flag(t_param *param, t_arg *arg)
{
	void	*ptr;

	ptr = (void*)arg->ptr;
	if (param->modifier == HH)
		*(char*)ptr = (char)arg->si_nb;
	else if (param->modifier == 'h')
		*(short*)ptr = (short)arg->si_nb;
	else if (param->modifier == 'l')
		*(long*)ptr = (long)arg->si_nb;
	else if (param->modifier == LL)
		*(long long*)ptr = (long long)arg->si_nb;
	else
		*(int*)ptr = (int)arg->si_nb;
	return (0);
}

int			ft_percent_flag(t_param *param, t_arg *arg)
{
	int		n;
	int		m;

	(void)arg;
	n = 0;
	if ((param->field_width ? param->field_width : 1) > BUFF_MAX)
		return (-1);
	while (!param->att.minus && n < param->field_width - 1)
		param->buffer[n++] = ' ';
	param->buffer[n++] = '%';
	m = 0;
	while (param->att.minus && m < param->field_width - 1)
		param->buffer[n + m++] = ' ';
	write(1, param->buffer, n + m);
	return (n + m);
}
