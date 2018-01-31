/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_overload.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 15:44:58 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/22 15:45:00 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		get_overload(t_param *param)
{
	if ((param->field_width < 0 && (param->field_width = -param->field_width) &&
			(param->att.minus = ENABLED)) || (param->prec != -1 &&
			get_index(param->conv, "dDioOuUxX") != -1))
		param->att.zero = DISABLED;
}
