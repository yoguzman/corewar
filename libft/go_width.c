/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 15:13:52 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/09 12:57:29 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "printf.h"

char			*go_width_zero(char *string, t_dt *dt)
{
	char		*buff;
	char		*buff_other;
	int			len;

	len = dt->width - ft_strlen(string);
	if (dt->conv == 'c' && dt->cz == 0)
		len = len - 1;
	if ((buff_other = malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_memset(buff_other, '0', len);
	buff_other[len] = 0;
	if ((buff = ft_strjoin(buff_other, string)) == NULL)
		return (NULL);
	free(string);
	free(buff_other);
	return (buff);
}

char			*string_debut_zero(char *string, t_dt *dt)
{
	char		*buff;
	int			len;

	buff = NULL;
	len = dt->width - ft_strlen(string);
	len -= 1;
	if ((buff = malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_memset(buff, ' ', len);
	buff[len] = 0;
	return (buff);
}

char			*go_width_neg(char *string, t_dt *dt)
{
	char		*buff;
	char		*buff_other;
	int			len;

	if (dt->conv == 'c' && dt->cz == 0 && dt->tab_f['-'])
		return (string_debut_zero(string, dt));
	len = dt->width - ft_strlen(string);
	if (dt->conv == 'c' && dt->cz == 0)
		len = len - 1;
	if ((buff_other = malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_memset(buff_other, ' ', len);
	buff_other[len] = 0;
	if ((buff = ft_strjoin(string, buff_other)) == NULL)
		return (NULL);
	free(string);
	free(buff_other);
	return (buff);
}

char			*go_width_space(char *string, t_dt *dt)
{
	char		*buff;
	char		*buff_other;
	int			len;

	len = dt->width - ft_strlen(string);
	if (dt->conv == 'c' && dt->cz == 0)
		len = len - 1;
	if ((buff_other = malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_memset(buff_other, ' ', len);
	buff_other[len] = 0;
	if ((buff = ft_strjoin(buff_other, string)) == NULL)
		return (NULL);
	free(string);
	free(buff_other);
	return (buff);
}
