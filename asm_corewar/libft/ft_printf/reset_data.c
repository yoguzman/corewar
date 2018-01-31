/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 17:53:09 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/23 17:56:41 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			reset_data(t_data *data)
{
	t_param		*param;
	t_arg		*arg;

	param = &data->param;
	arg = &data->arg;
	param->att.ashtag = DISABLED;
	param->att.zero = DISABLED;
	param->att.minus = DISABLED;
	param->att.plus = DISABLED;
	param->att.space = DISABLED;
	param->target = 0;
	param->field_width = 0;
	param->prec = -1;
	param->modifier = 0;
	param->conv = 0;
	arg->type = NONE;
	arg->si_nb = 0;
	arg->un_nb = 0;
	arg->ptr = NULL;
	arg->fl_nb = 0;
}
