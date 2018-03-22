/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_next.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 15:16:56 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/06 18:10:53 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

char			*go_attr(char *string, t_dt *dt)
{
	if (dt->tab_f['#'] == 1 && (dt->conv == 'o' || dt->conv == 'O' ||
				dt->conv == 'x' || dt->conv == 'X'))
		string = go_attr_sharp(string, dt);
	if (dt->tab_f['+'] == 1 &&
			(dt->conv == 'd' || dt->conv == 'D' || dt->conv == 'i'))
		string = go_attr_add(string);
	if (dt->tab_f[' '] == 1 && dt->tab_f['+'] == 0 &&
			(dt->conv == 'd' || dt->conv == 'D' || dt->conv == 'i'))
		string = go_attr_space(string);
	return (string);
}

char			*go_width(char *string, t_dt *dt)
{
	if (dt->width > (int)ft_strlen(string))
	{
		if (dt->tab_f['-'] == 1)
			return (go_width_neg(string, dt));
		else if (dt->tab_f['0'] == 1 && dt->prec == 0)
			return (go_width_zero(string, dt));
		else
			return (go_width_space(string, dt));
	}
	return (string);
}

char			*go_preci(char *string, t_dt *dt)
{
	if (dt->prec == 1)
	{
		if (dt->conv == 's')
			go_preci_s(string, dt);
		else if (dt->conv == 'p')
			go_preci_p(string);
		else if (dt->conv != 'c')
			if (dt->preci > (int)ft_strlen_mod(string) ||
					!ft_isdigitnozero(string))
				return (go_preci_next(string, dt));
	}
	return (string);
}
