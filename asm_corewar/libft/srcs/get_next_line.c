/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:42:25 by adauchy           #+#    #+#             */
/*   Updated: 2018/01/21 03:25:18 by adauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int				get_line(int *stack, char **line, int end)
{
	int			size;
	int			n;

	size = 0;
	while (size < *stack && *stack && stack[size + 3] != '\n')
		size++;
	if (!*stack || (end && size == *stack))
		return (0);
	if ((*line = (char*)malloc(size + 1)) == NULL)
		return (-1);
	n = 0;
	while (n < size)
	{
		(*line)[n] = (char)stack[n + 3];
		n++;
	}
	(*line)[n] = 0;
	n = 0;
	while (n < *stack - size - 1)
	{
		stack[n + 3] = stack[n + size + 1 + 3];
		n++;
	}
	*stack -= (end) ? size + 1 : *stack;
	return (1);
}

int				update_stack(int **stack, int size_read)
{
	int			*new_stack;
	int			n;

	n = 0;
	if ((new_stack = (int*)malloc((size_read + (*stack)[0] + 3) *
							sizeof(int))) == NULL)
		return (-1);
	new_stack[0] = (*stack)[0];
	new_stack[1] = (*stack)[0] + size_read;
	new_stack[2] = (*stack)[2];
	while (n < (*stack)[0])
	{
		new_stack[n + 3] = (*stack)[n + 3];
		n++;
	}
	free(*stack);
	*stack = new_stack;
	return (0);
}

int				write_in_stack(char buffer[BUFF_SIZE], int **stack, int fd)
{
	int			size_read;
	int			n;
	int			nl;

	nl = 0;
	while (!nl)
	{
		size_read = read(fd, buffer, BUFF_SIZE);
		if (size_read <= 0)
			return (size_read);
		if ((*stack)[1] - (*stack)[0] < size_read &&
				update_stack(stack, size_read) == -1)
			return (-1);
		n = 0;
		while (n < size_read)
		{
			(*stack)[n + (*stack)[0] + 3] = (int)buffer[n];
			if (buffer[n] == '\n')
				nl = 1;
			n++;
		}
		(*stack)[0] += size_read;
	}
	return (1);
}

int				get_stack(int ***tab_stack, int fd)
{
	int			size;
	int			**new_tab;
	int			n;

	size = 0;
	n = -1;
	while ((*tab_stack)[size] && (*tab_stack)[size][2] != fd)
		size++;
	if ((*tab_stack)[size])
		return (size);
	if ((new_tab = (int**)malloc((size + 2) * sizeof(int*))) == NULL)
		return (-1);
	while (++n < size)
		new_tab[n] = (*tab_stack)[n];
	if ((new_tab[n] = (int*)malloc(3 * sizeof(int))) == NULL)
		return (-1);
	new_tab[n][0] = 0;
	new_tab[n][1] = 0;
	new_tab[n][2] = fd;
	new_tab[n + 1] = NULL;
	free(*tab_stack);
	*tab_stack = new_tab;
	return (n);
}

int				get_next_line(const int fd, char **line)
{
	static t_stack	*stk = NULL;
	int				ret;
	int				index;

	if (!line)
		return (-1);
	*line = NULL;
	if (!stk)
	{
		if ((stk = (t_stack*)malloc(sizeof(t_stack))) == NULL)
			return (-1);
		if ((stk->tab_stack = (int**)malloc(sizeof(int*))) == NULL)
			return (-1);
		stk->tab_stack[0] = NULL;
	}
	if ((index = get_stack(&stk->tab_stack, fd)) == -1)
		return (-1);
	if ((ret = get_line(stk->tab_stack[index], line, 1)) == -1)
		return (-1);
	if (*line)
		return (1);
	if ((ret = write_in_stack(stk->buffer, &stk->tab_stack[index], fd)) == -1)
		return (ret);
	return (get_line(stk->tab_stack[index], line, ret));
}
