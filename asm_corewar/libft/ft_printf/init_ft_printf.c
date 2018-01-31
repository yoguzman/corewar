/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ft_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 02:16:01 by adauchy           #+#    #+#             */
/*   Updated: 2017/12/18 20:03:41 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			init_tab_conv(int (*tab_func[23])())
{
	tab_func[0] = ft_lower_s_flag;
	tab_func[1] = ft_upper_s_flag;
	tab_func[2] = ft_lower_p_flag;
	tab_func[3] = ft_lower_d_flag;
	tab_func[4] = ft_upper_d_flag;
	tab_func[5] = ft_lower_i_flag;
	tab_func[6] = ft_lower_o_flag;
	tab_func[7] = ft_upper_o_flag;
	tab_func[8] = ft_lower_u_flag;
	tab_func[9] = ft_upper_u_flag;
	tab_func[10] = ft_lower_x_flag;
	tab_func[11] = ft_upper_x_flag;
	tab_func[12] = ft_lower_c_flag;
	tab_func[13] = ft_upper_c_flag;
	tab_func[14] = ft_lower_e_flag;
	tab_func[15] = ft_upper_e_flag;
	tab_func[16] = ft_lower_f_flag;
	tab_func[17] = ft_upper_f_flag;
	tab_func[18] = ft_lower_g_flag;
	tab_func[19] = ft_upper_g_flag;
	tab_func[20] = ft_lower_a_flag;
	tab_func[21] = ft_upper_a_flag;
	tab_func[22] = ft_lower_n_flag;
	tab_func[23] = ft_percent_flag;
}

void			init_ft_printf(t_data *data)
{
	init_tab_conv(data->tab_conv);
	data->nb_carac = 0;
}
