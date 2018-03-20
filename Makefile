#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yguzman <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/18 11:38:09 by yguzman           #+#    #+#              #
#    Updated: 2018/03/20 15:45:11 by abeauvoi         ###   ########.fr        #
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
		  ft_isdigitstr.c load_champion.c parse_argv.c switch_endianness.c utils.c

OBJS_ASM	= $(addprefix $(OBJ_DIR)/, $(SRCS_ASM:.c=.o))
OBJS_COREWAR	= $(addprefix $(OBJ_DIR)/, $(SRCS_COREWAR:.c=.o))

#
# Build
#

LFLAGS	= -L$(LIB_DIR) -lft -lncurses
CFLAGS	+= -Iinclude
CFLAGS	+= -Wall -Wextra -g -g3
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

test:
	@echo $(VPATH)

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

depend		:		./src/asm/$(SRCS_ASM) ./src/virtual_machine/$(SRCS_COREWAR)
	@makedepend -- -Yinclude/ -- $^ 2> /dev/null

.PHONY: all clean flean re

# DO NOT DELETE THIS LINE -- make depend depends on it.

obj/main_a.o: include/libft.h include/printf.h include/asm.h include/op.h
obj/tools4.o: include/asm.h include/libft.h include/printf.h include/op.h
obj/write_instr2.o: include/asm.h include/libft.h include/printf.h
obj/write_instr2.o: include/op.h
obj/write_instr4.o: include/asm.h include/libft.h include/printf.h
obj/write_instr4.o: include/op.h
obj/write_instr3.o: include/asm.h include/libft.h include/printf.h
obj/write_instr3.o: include/op.h
obj/write_instr1.o: include/libft.h include/printf.h include/asm.h
obj/write_instr1.o: include/op.h
obj/compile_champ.o: include/libft.h include/printf.h include/asm.h
obj/compile_champ.o: include/op.h
obj/get_champ.o: include/libft.h include/printf.h include/asm.h
obj/get_champ.o: include/op.h
obj/islabel.o: include/asm.h include/libft.h include/printf.h
obj/islabel.o: include/op.h
obj/cost.o: include/asm.h include/libft.h include/printf.h include/op.h
obj/get_champ2.o: include/libft.h include/printf.h include/asm.h
obj/get_champ2.o: include/op.h
obj/cost2.o: include/asm.h include/libft.h include/printf.h include/op.h
obj/cost3.o: include/asm.h include/libft.h include/printf.h include/op.h
obj/print_champ.o: include/asm.h include/libft.h include/printf.h
obj/print_champ.o: include/op.h
obj/print_champ2.o: include/asm.h include/libft.h include/printf.h
obj/print_champ2.o: include/op.h
obj/check_label.o: include/asm.h include/libft.h include/printf.h
obj/check_label.o: include/op.h
obj/tools.o: include/asm.h include/libft.h include/printf.h include/op.h
obj/tools2.o: include/libft.h include/printf.h
obj/check_instr.o: include/asm.h include/libft.h include/printf.h
obj/check_instr.o: include/op.h
obj/replace_cod_oct.o: include/op.h
obj/check_arg.o: include/asm.h include/libft.h include/printf.h
obj/check_arg.o: include/op.h
obj/fill_cost_line.o: include/asm.h include/libft.h include/printf.h
obj/fill_cost_line.o: include/op.h
obj/write_instr.o: include/asm.h include/libft.h include/printf.h
obj/write_instr.o: include/op.h
obj/tools3.o: include/asm.h include/libft.h include/printf.h include/op.h
obj/main.o: include/libft.h include/printf.h include/vm.h
obj/main.o: include/op.h
obj/instr.o: include/op.h include/vm.h include/libft.h
obj/instr.o: include/printf.h
obj/op.o: include/op.h include/vm.h
obj/print_usage.o: include/libft.h include/printf.h
obj/print_usage.o: include/vm.h include/op.h
obj/print_error_and_exit.o: include/libft.h include/printf.h
obj/print_error_and_exit.o: include/vm.h include/op.h
obj/ft_isdigitstr.o: include/libft.h include/printf.h
obj/load_champion.o: include/libft.h include/printf.h
obj/load_champion.o: include/vm.h include/op.h
obj/parse_argv.o: include/libft.h include/printf.h
obj/parse_argv.o: include/vm.h include/op.h
obj/print_mem.o: include/vm.h include/op.h include/libft.h
obj/print_mem.o: include/printf.h
obj/switch_endianness.o: include/vm.h include/op.h
obj/clear_data.o: include/vm.h include/op.h
obj/print_players.o: include/vm.h include/op.h
obj/dump_arena.o: include/vm.h include/op.h
obj/engine.o: include/libft.h include/printf.h include/vm.h
obj/engine.o: include/op.h
obj/process.o: include/libft.h include/printf.h include/vm.h
obj/process.o: include/op.h
obj/priority_queue.o: include/libft.h include/printf.h
obj/priority_queue.o: include/vm.h include/op.h
obj/print_ncurses.o: include/libft.h include/printf.h
obj/print_ncurses.o: include/vm.h include/op.h
obj/print_breakdown.o: include/libft.h include/printf.h
obj/print_breakdown.o: include/vm.h include/op.h
obj/check_live.o: include/vm.h include/op.h
obj/get_instr_data.o: include/vm.h include/op.h
obj/get_instr_data.o: include/libft.h include/printf.h
obj/init_instr.o: include/op.h include/vm.h
obj/reset_pc.o: include/op.h
