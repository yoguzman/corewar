#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yguzman <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/18 11:38:09 by yguzman           #+#    #+#              #
#    Updated: 2018/02/16 16:18:23 by jcoutare         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC				=	clang

NAME_ASM		=		./ASM

NAME_MACHINE	=		./Virtual_Machine

LIBFT			=		libft

LIBNAME			=		./libft/libft.a

DIR_SRC			=		./src/

SRCS_ASM		=		$(DIR_SRC)asm/main.c									\
						$(DIR_SRC)asm/tools4.c									\
						$(DIR_SRC)asm/write_instr2.c									\
						$(DIR_SRC)asm/write_instr4.c							\
						$(DIR_SRC)asm/write_instr3.c							\
						$(DIR_SRC)asm/write_instr1.c							\
						$(DIR_SRC)asm/check_comment.c							\
						$(DIR_SRC)asm/compile_champ.c							\
						$(DIR_SRC)asm/get_champ.c								\
						$(DIR_SRC)asm/islabel.c								\
						$(DIR_SRC)asm/cost.c								\
						$(DIR_SRC)asm/get_champ2.c								\
						$(DIR_SRC)asm/cost2.c								\
						$(DIR_SRC)asm/cost3.c								\
						$(DIR_SRC)asm/print_champ.c								\
						$(DIR_SRC)asm/check_label.c								\
						$(DIR_SRC)asm/tools.c									\
						$(DIR_SRC)asm/tools2.c									\
						$(DIR_SRC)asm/check_instr.c								\
						$(DIR_SRC)asm/check_arg.c								\
						$(DIR_SRC)asm/fill_cost_line.c							\
						$(DIR_SRC)asm/write_instr.c								\
						$(DIR_SRC)asm/tools3.c									\


SRCS_MACHINE	=		$(DIR_SRC)virtual_machine/main_virtual_machine.c		\

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
