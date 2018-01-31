/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 20:30:16 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/23 20:53:42 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../libft.h"

int			get_angle(int dist_x, int dist_y)
{
	int			angle;

	angle = (int)(atan((double)ft_abs(dist_y) /
				(double)ft_abs(dist_x)) * 180.0 / 3.1415);
	if (dist_x < 0 && dist_y < 0)
		return (180 - angle);
	if (dist_x <= 0 && dist_y >= 0)
		return (180 + angle);
	if (dist_x > 0 && dist_y > 0)
		return (-angle);
	return (angle);
}
