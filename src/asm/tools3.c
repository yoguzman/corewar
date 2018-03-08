/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoutare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:47:48 by jcoutare          #+#    #+#             */
/*   Updated: 2018/03/08 14:48:54 by jcoutare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

int				to_neg(unsigned short neg)
{
	int			first_octet;
	int			second_octet;
	t_neg		lol;

	lol.neg = neg;
	first_octet = lol.bneg[0];
	second_octet = lol.bneg[1];
	lol.bneg[0] = second_octet + 1;
	lol.bneg[1] = first_octet;
	return (lol.neg);
}
