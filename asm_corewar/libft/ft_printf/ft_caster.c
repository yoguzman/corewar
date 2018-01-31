/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_caster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 20:44:19 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/21 18:21:23 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_unsigned_caster(unsigned long long *un_nb, int modifier)
{
	if (modifier == HH)
		*un_nb = (unsigned char)*un_nb;
	else if (modifier == 'h')
		*un_nb = (unsigned short)*un_nb;
	else if (modifier == 'l')
		*un_nb = (unsigned long)*un_nb;
	else if (modifier == LL)
		*un_nb = (unsigned long long)*un_nb;
	else if (modifier == 'j')
		*un_nb = (uintmax_t)(*un_nb);
	else if (modifier == 'z')
		*un_nb = (size_t)*un_nb;
}

void		ft_signed_caster(long long *si_nb, int modifier)
{
	if (modifier == HH)
		*si_nb = (char)*si_nb;
	else if (modifier == 'h')
		*si_nb = (short)*si_nb;
	else if (modifier == 'l')
		*si_nb = (long)*si_nb;
	else if (modifier == LL)
		*si_nb = (long long)*si_nb;
	else if (modifier == 'j')
		*si_nb = (intmax_t)(*si_nb);
	else if (modifier == 'z')
		*si_nb = (ssize_t)(*si_nb);
}

void		ft_caster(long long *si_nb, unsigned long long *un_nb, int type,
				int modifier)
{
	if (type == SIGNED_NUMBER)
		ft_signed_caster(si_nb, modifier);
	else if (type == UNSIGNED_NUMBER)
		ft_unsigned_caster(un_nb, modifier);
}
