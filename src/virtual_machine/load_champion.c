/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 04:53:22 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/21 06:45:24 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "vm.h"

/*
** A faire: ? check si le code du champion est utilisable
** Le systeme de pid:
** Cas 1/ -n 3 a.cor b.cor -n 2 c.cor d.cor
** pid == 3, players == 0
** pid == -1, pid = players(0)++
** pid == 2, players == 1
** pid == -1, pid = players(1)++
** Le total des joueurs est update a la fin du parsing
** Ajouter verification si case dans player_table est vide avant de copier data
*/

const char		**load_champion(const char *argv[], t_corewar *vm)
{
	int				fd;
	unsigned char	buf[HEADER_SIZE];

	if ((fd = open(argv[0], O_RDONLY)) == -1
			|| read(fd, buf, HEADER_SIZE) == - 1)
		print_error_and_exit(NULL);
	if (vm->pid == -1)
		vm->pid = vm->players++;
	ft_memcpy(&THIS_PLAYER, buf, HEADER_SIZE);
	if (THIS_PLAYER.header.magic != COREWAR_EXEC_MAGIC)
		print_error_and_exit(E1);
	if (THIS_PLAYER.header.prog_size >= CHAMP_MAX_SIZE)
		print_error_and_exit(E2);
	if (!(THIS_PLAYER.code =
				(unsigned char *)malloc(THIS_PLAYER.header.prog_size)))
		print_error_and_exit(NULL);
	if (read(fd, THIS_PLAYER.code, THIS_PLAYER.header.prog_size) == -1
			|| close(fd) == -1)
		print_error_and_exit(NULL);
	vm->pid = -1;
	return (&argv[1]);
}
