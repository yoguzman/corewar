/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 04:53:22 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/03/21 19:08:15 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "vm.h"

int			get_empty_slot(t_player player_table[MAX_PLAYERS])
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS && player_table[i].code != NULL)
		++i;
	if (i == MAX_PLAYERS)
		i = -1;
	return (i);
}

static int	check_extension(const char *path)
{
	size_t	i;

	i = ft_strlen(path) - 1;
	if (i > 4 && path[i] == 'r' && path[i - 1] == 'o' && path[i - 2] == 'c'
			&& path[i - 3] == '.')
		return (1);
	return (0);
}

static void	start(const char *argv[], t_corewar *vm, int *fd,
		unsigned char buf[HEADER_SIZE])
{
	if (vm->player_id == -1
			&& (vm->player_id = get_empty_slot(vm->player_table)) == -1)
		clean_print_err_exit(E4, vm->player_table);
	if (!check_extension(argv[0]))
		clean_print_err_exit(E3, vm->player_table);
	if ((*fd = open(argv[0], O_RDONLY)) == -1 ||
			read(*fd, buf, HEADER_SIZE) == -1)
		clean_print_err_exit(NULL, vm->player_table);
}

const char	**load_champion(const char *argv[], t_corewar *vm)
{
	int				fd;
	unsigned char	buf[HEADER_SIZE];

	start(argv, vm, &fd, buf);
	ft_memcpy(&THIS_PLAYER.header, buf, HEADER_SIZE);
	switch_endianness(&THIS_PLAYER.header.magic, sizeof(int));
	switch_endianness(&THIS_PLAYER.header.prog_size, sizeof(int));
	if (THIS_PLAYER.header.magic != COREWAR_EXEC_MAGIC)
		clean_print_err_exit(E1, vm->player_table);
	if (THIS_PLAYER.header.prog_size > CHAMP_MAX_SIZE)
		clean_print_err_exit(E2, vm->player_table);
	THIS_PLAYER.load_address = get_load_address(vm,
			(vm->load_address != -1 && vm->load_address < MEM_SIZE ?
			vm->load_address : (vm->player_id * MEM_SIZE) / vm->players),
			THIS_PLAYER.header.prog_size);
	if (!(THIS_PLAYER.code = (uint8_t *)malloc(THIS_PLAYER.header.prog_size))
			|| read(fd, THIS_PLAYER.code, THIS_PLAYER.header.prog_size) == -1
			|| close(fd) == -1)
		clean_print_err_exit(NULL, vm->player_table);
	load_champion_in_arena(vm, vm->player_id);
	vm->player_id = -1;
	vm->load_address = -1;
	return (&argv[1]);
}

void		load_champion_in_arena(t_corewar *vm, uint8_t player_id)
{
	unsigned int	n;

	n = 0;
	safe_memcpy(vm->arena,
			vm->player_table[player_id].code,
			vm->player_table[player_id].header.prog_size,
			vm->player_table[player_id].load_address);
	vm->print_data[(n + vm->player_table[player_id].load_address) % MEM_SIZE] =
		player_id + 1 + 5;
	while (++n < vm->player_table[player_id].header.prog_size)
		vm->print_data[(n + vm->player_table[player_id].load_address)
			% MEM_SIZE] = player_id + 1;
}
