# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adauchy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/28 21:27:40 by adauchy           #+#    #+#              #
#    Updated: 2018/01/30 05:09:47 by adauchy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=		gcc

RM			=		rm -f

NAME		=		asm

CFLAGS		=		-Wextra -Wall -Werror

LIBFT		=		libft/libft.a

SRCS		=		main.c						\
					get_champ.c					\
					print_champ.c				\
					compile_champ.c				\

OBJS		=		$(SRCS:.c=.o)

HEADER 		= 		asm.h

all			:		$(NAME)

$(NAME)		:		$(OBJS)
					make -C libft/
					$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT)

%.o 		: 		%.c $(HEADER)
					$(CC) $(CFLAGS) -c $< -o $@

clean		:
					$(RM) $(OBJS)
					make clean -C libft/

fclean		:		clean
					$(RM) $(NAME)
					make fclean -C libft/

re			:		fclean all

.PHONY		:		all clean fclean re
