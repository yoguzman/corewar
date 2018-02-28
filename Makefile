#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yguzman <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/18 11:38:09 by yguzman           #+#    #+#              #
#    Updated: 2018/02/27 18:36:33 by adauchy          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

#
# Binaries
#

ASM	= ./asm
COREWAR	= ./corewar

#
# Directories
#

LIB_DIR	= libft
OBJ_DIR = obj
SRC_DIR	= src
ASM_DIR	= asm
COREWAR_DIR	= virtual_machine
VPATH	= $(addprefix $(SRC_DIR)/,$(COREWAR_DIR) $(ASM_DIR))

#
# Sources
#

SRCS_ASM		=		main_a.c							\
						tools4.c							\
						write_instr2.c						\
						write_instr4.c						\
						write_instr3.c						\
						write_instr1.c						\
						compile_champ.c						\
						get_champ.c							\
						islabel.c							\
						cost.c								\
						get_champ2.c						\
						cost2.c								\
						cost3.c								\
						print_champ.c						\
						check_label.c						\
						tools.c								\
						tools2.c							\
						check_instr.c						\
						check_arg.c							\
						fill_cost_line.c					\
						write_instr.c						\
						tools3.c							\

SRCS_COREWAR	= main.c op.c print_usage.c print_error_and_exit.c \
		ft_isdigitstr.c load_champion.c parse_argv.c \
		print_mem.c switch_endianness.c clear_data.c print_players.c \
		dump_arena.c engine.c process.c priority_queue.c \
		print_ncurses.c print_breakdown.c check_live.c \


OBJS_ASM	= $(addprefix $(OBJ_DIR)/, $(SRCS_ASM:.c=.o))
OBJS_COREWAR	= $(addprefix $(OBJ_DIR)/, $(SRCS_COREWAR:.c=.o))

#
# Build
#

LFLAGS	= -L$(LIB_DIR) -lft -lncurses
CFLAGS	+= -Iinclude
CFLAGS	+= -Wall -Wextra -g -O3
COMP	= $(CC) $(CFLAGS) -o $@ -c $<
LINK	= $(CC) $(LFLAGS) -o $@ $(filter-out $(LIB) $(OBJ_DIR), $^)
LIB	= libft.a

#
# Output
#

ECHO	= printf
NAME	= "\033[35m[ "$@" ]-->\033[0m"
SUCCESS	= "\033[33;32m["$@"]\n\033[0m"
FAILURE	= "\033[31m["$@"]\n\033[0m"

#
# Rules
#

all: $(ASM) $(COREWAR)

debug: CFLAGS += -fsanitize=address -g3
debug: all

$(LIB):
	@make -C $(LIB_DIR)

$(OBJ_DIR):
	@mkdir -p $@

$(ASM): $(LIB) $(OBJ_DIR) $(OBJS_ASM)
	@$(ECHO) $(NAME) 
	@$(LINK) && $(ECHO) $(SUCCESS) || $(ECHO) $(FAILURE)

$(COREWAR): $(LIB) $(OBJ_DIR) $(OBJS_COREWAR)
	@$(ECHO) $(NAME) 
	@$(LINK) && $(ECHO) $(SUCCESS) || $(ECHO) $(FAILURE)

$(OBJ_DIR)/%.o: %.c
	@$(ECHO) $(NAME)
	@$(COMP) && $(ECHO) $(SUCCESS) || $(ECHO) $(FAILURE)

clean:
	@make -C $(LIB_DIR) $@
	@$(ECHO) "\033[31m[ "$@" ]\n\033[0m"
	@$(RM) $(OBJS_COREWAR)
	@$(RM) $(OBJS_ASM)
	@rm -fr $(OBJ_DIR) 2> /dev/null || true

fclean_lib:
	@make -C $(LIB_DIR) fclean

fclean: fclean_lib
	@$(ECHO) "\033[31m[ clean ]\n\033[0m"
	@$(RM) $(OBJS_COREWAR)
	@$(RM) $(OBJS_ASM)
	@rm -fr $(OBJ_DIR) 2> /dev/null || true
	@$(ECHO) "\033[31m[ fclean ]\n\033[0m"
	@$(RM) $(COREWAR)
	@$(RM) $(ASM)

re: fclean all

.PHONY: all clean flean re
