/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 04:53:22 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/23 04:38:27 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "vm.h"

int				get_empty_slot(t_player player_table[MAX_PLAYERS])
{
	int	i;

	i = 0;
	while (player_table[i].code != NULL)
		++i;
	return (i);
}

static int		check_extension(const char *path)
{
	size_t	i;

	i = ft_strlen(path) - 1;
	if (path[i] == 'r' && path[i - 1] == 'o' && path[i - 2] == 'c'
			&& path[i - 3] == '.')
		return (1);
	return (0);
}

static void		start(const char *argv[], t_corewar *vm, int *fd,
		unsigned char buf[HEADER_SIZE])
{
	if (vm->players == MAX_PLAYERS)
		clean_print_err_exit(E4, vm->player_table);
	if (!check_extension(argv[0]))
		clean_print_err_exit(E3, vm->player_table);
	if ((*fd = open(argv[0], O_RDONLY)) == -1 ||
			read(*fd, buf, HEADER_SIZE) == - 1)
		clean_print_err_exit(NULL, vm->player_table);
	if (vm->player_id == -1)
		vm->player_id = get_empty_slot(vm->player_table);
}

const char		**load_champion(const char *argv[], t_corewar *vm)
{
	int				fd;
	unsigned char	buf[HEADER_SIZE];

	start(argv, vm, &fd, buf);
	++vm->players;
	ft_memcpy(&THIS_PLAYER.header, buf, HEADER_SIZE);
	switch_endianness(&THIS_PLAYER.header.magic, sizeof(int));
	switch_endianness(&THIS_PLAYER.header.prog_size, sizeof(int));
	if (THIS_PLAYER.header.magic != COREWAR_EXEC_MAGIC)
		clean_print_err_exit(E1, vm->player_table);
	if (THIS_PLAYER.header.prog_size > CHAMP_MAX_SIZE)
		clean_print_err_exit(E2, vm->player_table);
	if (!(THIS_PLAYER.code = malloc(THIS_PLAYER.header.prog_size))
			|| read(fd, THIS_PLAYER.code, THIS_PLAYER.header.prog_size) == -1
			|| close(fd) == -1)
		clean_print_err_exit(NULL, vm->player_table);
	vm->player_id = -1;
	return (&argv[1]);
}

void			load_champions_in_arena(t_corewar *vm)
{
	size_t	i;
	size_t	offset;

	i = 0;
	offset = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player_table[i].code != NULL)
		{
			ft_memcpy(&vm->arena[offset], vm->player_table[i].code,
					vm->player_table[i].header.prog_size);
			vm->player_table[i].load_index = i;
			offset += (MEM_SIZE / vm->players);
		}
		++i;
	}
}
