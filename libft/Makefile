#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yguzman <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/18 11:38:09 by yguzman           #+#    #+#              #
#    Updated: 2018/03/22 16:49:38 by jcoutare         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC			=		clang

ARRC		=		ar rc

RANLIB		=		ranlib

NAME		=		libft.a

DIR_SRC_LIB	=		./

SRCS_LIB	=		$(DIR_SRC_LIB)ft_putchar.c					\
					$(DIR_SRC_LIB)ft_swap.c						\
					$(DIR_SRC_LIB)ft_memset.c					\
					$(DIR_SRC_LIB)ft_strsub.c					\
					$(DIR_SRC_LIB)ft_isspace.c					\
					$(DIR_SRC_LIB)ft_itoa_base.c				\
					$(DIR_SRC_LIB)ft_itoa_base_u.c				\
					$(DIR_SRC_LIB)ft_listpush_back_double.c		\
					$(DIR_SRC_LIB)ft_tablen.c					\
					$(DIR_SRC_LIB)ft_itoa_base_u.c				\
					$(DIR_SRC_LIB)ft_itoa_base.c				\
					$(DIR_SRC_LIB)ft_lstadd_double.c			\
					$(DIR_SRC_LIB)ft_reallocfake.c				\
					$(DIR_SRC_LIB)get_next_line.c				\
					$(DIR_SRC_LIB)free_elem_lst.c				\
					$(DIR_SRC_LIB)ft_lstnew.c					\
					$(DIR_SRC_LIB)ft_lstdelone.c				\
					$(DIR_SRC_LIB)ft_lstdel_double.c			\
					$(DIR_SRC_LIB)ft_lstdel.c					\
					$(DIR_SRC_LIB)ft_strjoin.c					\
					$(DIR_SRC_LIB)ft_lstadd.c					\
					$(DIR_SRC_LIB)ft_strtrim.c					\
					$(DIR_SRC_LIB)find_char_in_str.c			\
					$(DIR_SRC_LIB)ft_getenv.c					\
					$(DIR_SRC_LIB)ft_lstiter.c					\
					$(DIR_SRC_LIB)ft_lstmap.c					\
					$(DIR_SRC_LIB)ft_memcmp.c					\
					$(DIR_SRC_LIB)ft_memchr.c					\
					$(DIR_SRC_LIB)ft_puterr.c					\
					$(DIR_SRC_LIB)ft_memcpy.c					\
					$(DIR_SRC_LIB)ft_memccpy.c					\
					$(DIR_SRC_LIB)ft_memmove.c					\
					$(DIR_SRC_LIB)ft_bzero.c					\
					$(DIR_SRC_LIB)ft_putstr.c					\
					$(DIR_SRC_LIB)ft_putstr_fd.c				\
					$(DIR_SRC_LIB)ft_putendl_fd.c				\
					$(DIR_SRC_LIB)ft_putnbr_fd.c				\
					$(DIR_SRC_LIB)ft_putendl.c					\
					$(DIR_SRC_LIB)ft_putchar_fd.c				\
					$(DIR_SRC_LIB)ft_strcmp.c					\
					$(DIR_SRC_LIB)ft_print_words_tables.c		\
					$(DIR_SRC_LIB)ft_strlen.c					\
					$(DIR_SRC_LIB)ft_strchr.c					\
					$(DIR_SRC_LIB)ft_strrchr.c					\
					$(DIR_SRC_LIB)ft_isalpha.c					\
					$(DIR_SRC_LIB)ft_memalloc.c					\
					$(DIR_SRC_LIB)ft_memdel.c					\
					$(DIR_SRC_LIB)ft_strstr.c					\
					$(DIR_SRC_LIB)ft_strnew.c					\
					$(DIR_SRC_LIB)ft_strdel.c					\
					$(DIR_SRC_LIB)ft_strmap.c					\
					$(DIR_SRC_LIB)ft_strequ.c					\
					$(DIR_SRC_LIB)get_input.c					\
					$(DIR_SRC_LIB)ft_strnequ.c					\
					$(DIR_SRC_LIB)ft_strmapi.c					\
					$(DIR_SRC_LIB)ft_strclr.c					\
					$(DIR_SRC_LIB)ft_striter.c					\
					$(DIR_SRC_LIB)ft_striteri.c					\
					$(DIR_SRC_LIB)ft_isdigit.c					\
					$(DIR_SRC_LIB)ft_isalnum.c					\
					$(DIR_SRC_LIB)ft_isascii.c					\
					$(DIR_SRC_LIB)ft_isprint.c					\
					$(DIR_SRC_LIB)ft_toupper.c					\
					$(DIR_SRC_LIB)ft_tolower.c					\
					$(DIR_SRC_LIB)ft_strnstr.c					\
					$(DIR_SRC_LIB)ft_strcpy.c					\
					$(DIR_SRC_LIB)ft_strncat.c					\
					$(DIR_SRC_LIB)ft_itoa.c						\
					$(DIR_SRC_LIB)ft_strncmp.c					\
					$(DIR_SRC_LIB)ft_strlcpy.c					\
					$(DIR_SRC_LIB)ft_putnbr.c					\
					$(DIR_SRC_LIB)ft_strncpy.c					\
					$(DIR_SRC_LIB)ft_strcat.c					\
					$(DIR_SRC_LIB)ft_putnbr_base.c				\
					$(DIR_SRC_LIB)ft_strdup.c					\
					$(DIR_SRC_LIB)ft_atoi.c						\
					$(DIR_SRC_LIB)ft_strlcat.c					\
					$(DIR_SRC_LIB)ft_strsplit.c					\
					$(DIR_SRC_LIB)realloc_tab.c					\
					$(DIR_SRC_LIB)ft_printf.c					\
					$(DIR_SRC_LIB)ft_printf_next.c				\
					$(DIR_SRC_LIB)go_all_attr.c					\
					$(DIR_SRC_LIB)go_width.c					\
					$(DIR_SRC_LIB)go_preci.c					\
					$(DIR_SRC_LIB)convert.c						\
					$(DIR_SRC_LIB)move_move.c					\
					$(DIR_SRC_LIB)free.c						\
					$(DIR_SRC_LIB)convert_2.c					\
					$(DIR_SRC_LIB)find_all_flag.c				\
					$(DIR_SRC_LIB)init.c

OBJS_LIB	=		$(SRCS_LIB:.c=.o)

HEADER		=		../include/libft.h ../include/printf.h

CFLAGS		+=		-Wall -Wextra -I../include -g3

RM			=		rm -f

ECHO		=		printf

all			:		$(NAME)

$(NAME)	:			$(OBJS_LIB)
					@$(ECHO) "\033[35m[~~~~~~COMPILATION LIBFT~~~~~~]\n\033[0m"
					@$(ARRC) $(NAME) $(OBJS_LIB) && $(ECHO) "\033[33;32m["$@"]\n\033[0m" && $(RANLIB) $(NAME) || $(ECHO) "\033[31m"$@"\n\033[0m"

%.o			:		%.c $(HEADER)
					@$(ECHO) "\033[35m[~~~Comipilation obj //libft~~~]-->\033[0m"
					@$(CC) $(CFLAGS) -o $@ -c $< && $(ECHO) "\033[33;32m ["$@"]\n\033[0m" || $(ECHO) "\033[31m ["$@"]\n\033[0m"

clean		:
					@$(ECHO) "\033[31m[~~~~~~Supression des .o //libft-~~~~~]\n\033[0m"
					@$(RM) $(OBJS_LIB)

fclean		:
					@$(ECHO) "\033[31m[~~~~~~Supression des .o //libft~~~~~~]\n\033[0m"
					@$(RM) $(OBJS_LIB)
					@$(ECHO) "\033[31m[~~~~Supression de libft.a~~~~]\n\033[0m"
				@$(RM) $(NAME)

re			:		fclean all

.PHONY		:		all clean flean re
