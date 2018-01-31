/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 18:13:51 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/22 14:21:13 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_lower_i_flag(t_param *param, t_arg *arg)
{
	return (ft_lower_d_flag(param, arg));
}

int			ft_lower_o_flag(t_param *param, t_arg *arg)
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
	write_un_number(param, nb, size, 'o');
	write(1, param->buffer, size_buffer);
	return (size_buffer);
}

int			ft_upper_o_flag(t_param *param, t_arg *arg)
{
	unsigned long		nb;
	int					size;
	int					size_buffer;

	nb = (unsigned long)arg->un_nb;
	if ((size_buffer = get_size_buffer_un_nb(nb, param, &size)) > BUFF_MAX)
		return (-1);
	write_un_number(param, nb, size, 'o');
	write(1, param->buffer, size_buffer);
	return (size_buffer);
}

int			ft_lower_u_flag(t_param *param, t_arg *arg)
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
	write_un_number(param, nb, size, 'u');
	write(1, param->buffer, size_buffer);
	return (size_buffer);
}

int			ft_upper_u_flag(t_param *param, t_arg *arg)
{
	unsigned long		nb;
	int					size;
	int					size_buffer;

	nb = (unsigned long)arg->un_nb;
	if ((size_buffer = get_size_buffer_un_nb(nb, param, &size)) > BUFF_MAX)
		return (-1);
	write_un_number(param, nb, size, 'u');
	write(1, param->buffer, size_buffer);
	return (size_buffer);
}
