# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adauchy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 19:57:04 by adauchy           #+#    #+#              #
#    Updated: 2018/01/24 19:57:05 by adauchy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER = 	libft.h get_next_line.h

CC		=	gcc

RM		=	rm -f

SRCS =		srcs/ft_memset.c				\
			srcs/ft_bzero.c					\
			srcs/ft_memcpy.c				\
			srcs/ft_memccpy.c				\
			srcs/ft_memmove.c				\
			srcs/ft_memchr.c				\
			srcs/ft_memcmp.c				\
			srcs/ft_strlen.c				\
			srcs/ft_strdup.c				\
			srcs/ft_strcpy.c				\
			srcs/ft_strncpy.c				\
			srcs/ft_strcat.c				\
			srcs/ft_strncat.c				\
			srcs/ft_strlcat.c				\
			srcs/ft_strchr.c				\
			srcs/ft_strrchr.c				\
			srcs/ft_strstr.c				\
			srcs/ft_strnstr.c				\
			srcs/ft_strcmp.c				\
			srcs/ft_strncmp.c				\
			srcs/ft_atoi.c					\
			srcs/ft_isalpha.c				\
			srcs/ft_isdigit.c				\
			srcs/ft_isalnum.c				\
			srcs/ft_isascii.c				\
			srcs/ft_isprint.c				\
			srcs/ft_toupper.c				\
			srcs/ft_tolower.c				\
			srcs/ft_memalloc.c				\
			srcs/ft_memdel.c				\
			srcs/ft_strnew.c				\
			srcs/ft_strdel.c				\
			srcs/ft_strclr.c				\
			srcs/ft_striter.c				\
			srcs/ft_striteri.c				\
			srcs/ft_strmap.c				\
			srcs/ft_strmapi.c				\
			srcs/ft_strequ.c				\
			srcs/ft_strnequ.c				\
			srcs/ft_strsub.c				\
			srcs/ft_strjoin.c				\
			srcs/ft_strtrim.c				\
			srcs/ft_strsplit.c				\
			srcs/ft_itoa.c					\
			srcs/ft_putchar.c				\
			srcs/ft_putstr.c				\
			srcs/ft_putendl.c				\
			srcs/ft_putnbr.c				\
			srcs/ft_putchar_fd.c			\
			srcs/ft_putstr_fd.c				\
			srcs/ft_putendl_fd.c			\
			srcs/ft_putnbr_fd.c				\
			srcs/ft_lstnew.c				\
			srcs/ft_lstdelone.c				\
			srcs/ft_lstdel.c				\
			srcs/ft_lstadd.c				\
			srcs/ft_lstiter.c				\
			srcs/ft_lstmap.c				\
			srcs/ft_print_tab_str.c			\
			srcs/ft_print_tab_int.c			\
			srcs/ft_print_test.c			\
			srcs/ft_count_char.c			\
			srcs/ft_sort_integer_table.c 	\
			srcs/ft_free_2d_tab.c			\
			srcs/ft_list_push_back.c		\
			srcs/ft_strccmp.c				\
			srcs/ft_strcdup.c				\
			srcs/ft_strclen.c				\
			srcs/get_input.c				\
			srcs/ft_create_elem.c			\
			srcs/get_next_line.c			\
			srcs/ft_abs.c					\
			srcs/get_size_list.c			\
			srcs/ft_swap_all.c				\
			srcs/ft_put_err.c				\
			srcs/get_angle.c				\
			ft_printf/ft_printf.c			\
			ft_printf/conversions1.c		\
			ft_printf/conversions2.c		\
			ft_printf/conversions3.c		\
			ft_printf/conversions4.c		\
			ft_printf/conversions5.c		\
			ft_printf/ft_caster.c			\
			ft_printf/ft_printf_itoa.c		\
			ft_printf/ft_itoa_base.c		\
			ft_printf/ft_print_unicode.c	\
			ft_printf/ft_put_err.c			\
			ft_printf/ft_strlen.c			\
			ft_printf/get_attributes.c		\
			ft_printf/get_conversion.c		\
			ft_printf/get_field_width.c		\
			ft_printf/get_index.c			\
			ft_printf/get_modifier.c		\
			ft_printf/get_nb.c				\
			ft_printf/get_overload.c		\
			ft_printf/get_param.c			\
			ft_printf/get_precision.c		\
			ft_printf/get_size_buffer.c		\
			ft_printf/get_size_nb.c			\
			ft_printf/get_size_nb_base.c	\
			ft_printf/get_target_arg.c		\
			ft_printf/get_vararg.c			\
			ft_printf/init_ft_printf.c		\
			ft_printf/print_format.c		\
			ft_printf/reset_data.c			\
			ft_printf/write_number.c		\
			ft_printf/write_unicode.c		\

OBJS 	= 	$(SRCS:.c=.o)

CFLAGS 	= 	-Wall -Werror -Wextra -c

all		: 	$(NAME)

$(NAME)	: 	$(OBJS)
			gcc $(CFLAGS) $(SRCS) -I ./
			ar rc $(NAME) $(OBJS)
			ranlib $(NAME)

%.o		:	%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean	:
			$(RM) *.o $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		: 	fclean $(NAME)

.PHONY	:	all clean fclean re
