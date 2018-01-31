#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yguzman <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/18 11:38:09 by yguzman           #+#    #+#              #
#    Updated: 2018/01/25 18:37:42 by abeauvoi         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC				=	clang

NAME_ASM		=		./ASM

NAME_MACHINE	=		./Virtual_Machine

LIBFT			=		libft

LIBNAME			=		./libft/libft.a

DIR_SRC			=		./src/

SRCS_ASM		=		$(DIR_SRC)asm/main.c									\
						$(DIR_SRC)asm/compile_champ.c							\
						$(DIR_SRC)asm/get_champ.c								\
						$(DIR_SRC)asm/print_champ.c								\


SRCS_MACHINE	=		$(DIR_SRC)virtual_machine/main_virtual_machine.c			\

OBJS_ASM		=		$(SRCS_ASM:.c=.o)
OBJS_MACHINE	=		$(SRCS_MACHINE:.c=.o)

CFLAGS			+=		-Iinclude
CFLAGS			+=		-Wall -Wextra -g -g3

RM				=		rm -f

LIB				=		./libft/libft.a

ECHO			=		printf

all				:		$(NAME_ASM) $(NAME_MACHINE)

$(LIBFT)		:		$(LIBNAME)

$(LIBNAME)		:
						@make -C ./libft

$(NAME_ASM)		:		$(LIBFT) $(OBJS_ASM)
						@$(ECHO) "\033[35m[~~~~COMPILATION PROJECT VIRTUAL MACHINE~~~~]\n\033[0m"
						@$(CC) -o $(NAME_ASM) -Llibft -lft -lncurses $(OBJS_ASM) && $(ECHO) "\033[33;32m["$@"]\n\033[0m" || $(ECHO) "\033[31m["$@"]\n\033[0m"

$(NAME_MACHINE)	:		$(LIBFT) $(NAME) $(OBJS_MACHINE)
						@$(ECHO) "\033[35m[~~~~COMPILATION PROJECT ASM ~~~~]\n\033[0m"
						@$(CC) -o $(NAME_MACHINE) -Llibft -lft -lncurses $(OBJS_MACHINE) && $(ECHO) "\033[33;32m["$@"]\n\033[0m" || $(ECHO) "\033[31m["$@"]\n\033[0m"

%.o				:		%.c
						@$(ECHO) "\033[35m[~~~Comipilation obj //project~~~]-->\033[0m"
						@$(CC) $(CFLAGS) -o $@ -c $< && $(ECHO) "\033[33;32m ["$@"]\n\033[0m" || $(ECHO) "\033[31m ["$@"]\n\033[0m"

clean_lib		:
						@make -C libft clean

clean			:		clean_lib
						@$(ECHO) "\033[31m[~~~~~~Supression des .o //project~~~~~~]\n\033[0m"
						@$(RM) $(OBJS_MACHINE)
						@$(RM) $(OBJS_ASM)

fclean_lib		:
						@make -C libft fclean

fclean			:		fclean_lib
						@$(ECHO) "\033[31m[~~~~~~Supression des .o //project~~~~~~]\n\033[0m"
						@$(RM) $(OBJS_MACHINE)
						@$(RM) $(OBJS_ASM)
						@$(ECHO) "\033[31m[~~~~Supression du Binaire~~~~]\n\033[0m"
						@$(RM) $(NAME_MACHINE)
						@$(RM) $(NAME_ASM)

re				:		fclean all

.PHONY			:		all clean flean re
