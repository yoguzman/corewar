/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 04:53:22 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/21 20:29:34 by abeauvoi         ###   ########.fr       */
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

static void		reverse_bits(unsigned char *mem, size_t mem_size,
		unsigned char lookup[16])
{
	 while (mem_size--)
	 {
		 *mem = (lookup[*mem & 0xF] << 4) | lookup[*mem >> 4];
		 ++mem;
	 }
}

const char		**load_champion(const char *argv[], t_corewar *vm)
{
	int				fd;
	unsigned char	buf[HEADER_SIZE];
	unsigned char	*s;

	s = &buf;
	if ((fd = open(argv[0], O_RDONLY)) == -1 ||
			read(fd, s, HEADER_SIZE) == - 1)
		print_error_and_exit(NULL);
	ft_putendl(argv[0]);
	if (vm->pid == -1)
		vm->pid = vm->players++;
	print_mem(s, HEADER_SIZE);
	ft_memcpy(&THIS_PLAYER, s, HEADER_SIZE);
	/*reverse_bits((unsigned char *)&THIS_PLAYER, HEADER_SIZE, vm->lookup);
	ft_putnbr_base(THIS_PLAYER.header.magic, DIGITS);
	ft_putchar('\n');*/
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
