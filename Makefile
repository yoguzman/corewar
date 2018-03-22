#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yguzman <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/18 11:38:09 by yguzman           #+#    #+#              #
#    Updated: 2018/03/22 16:55:29 by jcoutare         ###   ########.fr        #
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
VPATH 	= $(addprefix $(SRC_DIR)/,$(COREWAR_DIR) $(ASM_DIR))
VPATH	+= $(addprefix $(SRC_DIR)/$(COREWAR_DIR)/,instructions engine output parsing)

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
						print_champ2.c						\
						check_label.c						\
						tools.c								\
						tools2.c							\
						check_instr.c						\
						replace_cod_oct.c					\
						check_arg.c							\
						fill_cost_line.c					\
						write_instr.c						\
						tools3.c							\
						replace_cod_oct.c					\

SRCS_COREWAR	= main.c clear_data.c \
		  check_live.c engine.c priority_queue.c priority_queue2.c process.c replace_cod_oct.c \
		  calc_instr.c exec_instr.c get_instr_data.c init_instr.c ld_st_instr.c long_instr.c misc_instr.c \
		  dump_arena.c print_error_and_exit.c print_ncurses.c print_usage.c print_breakdown.c print_mem.c \
		  print_players.c visual.c key_events.c \
		  ft_isdigitstr.c load_champion.c parse_argv.c parse_argv2.c switch_endianness.c utils.c

OBJS_ASM	= $(addprefix $(OBJ_DIR)/, $(SRCS_ASM:.c=.o))
OBJS_COREWAR	= $(addprefix $(OBJ_DIR)/, $(SRCS_COREWAR:.c=.o))

#
# Build
#

LFLAGS	= -L$(LIB_DIR) -lft -lncurses
CFLAGS	+= -Iinclude
CFLAGS	+= -Wall -Wextra
COMP	= $(CC) $(CFLAGS) -o $@ -c $<
LINK	= $(CC) $(LFLAGS) -o $@ $(filter-out $(LIB) $(OBJ_DIR), $^)
LIB	= libft.a

#
# Output
#

HEADER	= include/asm.h include/op.h include/vm.h include/vm.h

ECHO	= printf
NAME	= "\033[35m[ "$@" ]-->\033[0m"
SUCCESS	= "\033[33;32m["$@"]\n\033[0m"
FAILURE	= "\033[31m["$@"]\n\033[0m"

#
# Rules
#

all: $(LIB) $(OBJ_DIR) $(ASM) $(COREWAR)

debug: CFLAGS += -g3
debug: all

test:
	@echo $(VPATH)

$(LIB):
	@make -C $(LIB_DIR)

$(OBJ_DIR):
	@mkdir -p $@

$(ASM): $(OBJS_ASM)
	@$(ECHO) "\n" && $(ECHO) $(NAME)
	@$(LINK) && ($(ECHO) $(SUCCESS) || $(ECHO) $(FAILURE)) && $(ECHO) "\n"

$(COREWAR): $(OBJS_COREWAR)
	@$(ECHO) "\n" && $(ECHO) $(NAME)
	@$(LINK) && ($(ECHO) $(SUCCESS) || $(ECHO) $(FAILURE)) && $(ECHO) "\n"

$(OBJ_DIR)/%.o: %.c $(HEADER)
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
